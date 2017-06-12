//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
// Copyright (c) 2014-2017 Devon Govett <https://github.com/devongovett/font-manager>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/Text/FontManager.h"


#if defined(TARGET_WIN32)
#pragma comment(lib, "Dwrite")

#define WINVER 0x0600
#include <dwrite.h>
#include <dwrite_1.h>
#include <unordered_set>

// throws a JS error when there is some exception in DirectWrite
#define HR(hr) \
  if (FAILED(hr)) throw "Font loading error";


namespace ofx {
namespace Text {


WCHAR *utf8ToUtf16(const char *input) {
  unsigned int len = MultiByteToWideChar(CP_UTF8, 0, input, -1, NULL, 0);
  WCHAR *output = new WCHAR[len];
  MultiByteToWideChar(CP_UTF8, 0, input, -1, output, len);
  return output;
}

char *utf16ToUtf8(const WCHAR *input) {
  unsigned int len = WideCharToMultiByte(CP_UTF8, 0, input, -1, NULL, 0, NULL, NULL);
  char *output = new char[len];
  WideCharToMultiByte(CP_UTF8, 0, input, -1, output, len, NULL, NULL);
  return output;
}

// returns the index of the user's locale in the set of localized strings
unsigned int getLocaleIndex(IDWriteLocalizedStrings *strings) {
  unsigned int index = 0;
  BOOL exists = false;
  wchar_t localeName[LOCALE_NAME_MAX_LENGTH];

  // Get the default locale for this user.
  int success = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);

  // If the default locale is returned, find that locale name, otherwise use "en-us".
  if (success) {
    HR(strings->FindLocaleName(localeName, &index, &exists));
  }

  // if the above find did not find a match, retry with US English
  if (!exists) {
    HR(strings->FindLocaleName(L"en-us", &index, &exists));
  }

  if (!exists)
    index = 0;

  return index;
}

// gets a localized string for a font
char *getString(IDWriteFont *font, DWRITE_INFORMATIONAL_STRING_ID string_id) {
  char *res = NULL;
  IDWriteLocalizedStrings *strings = NULL;

  BOOL exists = false;
  HR(font->GetInformationalStrings(
    string_id,
    &strings,
    &exists
  ));

  if (exists) {
    unsigned int index = getLocaleIndex(strings);
    unsigned int len = 0;
    WCHAR *str = NULL;

    HR(strings->GetStringLength(index, &len));
    str = new WCHAR[len + 1];

    HR(strings->GetString(index, str, len + 1));

    // convert to utf8
    res = utf16ToUtf8(str);
    delete str;
    
    strings->Release();
  }
  
  if (!res) {
    res = new char[1];
    res[0] = '\0';
  }
  
  return res;
}

FontDescriptor resultFromFont(IDWriteFont *font) {
  FontDescriptor res;
  IDWriteFontFace *face = NULL;
  unsigned int numFiles = 0;

  HR(font->CreateFontFace(&face));

  // get the font files from this font face
  IDWriteFontFile *files = NULL;
  HR(face->GetFiles(&numFiles, NULL));
  HR(face->GetFiles(&numFiles, &files));

  // return the first one
  if (numFiles > 0) {
    IDWriteFontFileLoader *loader = NULL;
    IDWriteLocalFontFileLoader *fileLoader = NULL;
    unsigned int nameLength = 0;
    const void *referenceKey = NULL;
    unsigned int referenceKeySize = 0;
    WCHAR *name = NULL;

    HR(files[0].GetLoader(&loader));

    // check if this is a local font file
    HRESULT hr = loader->QueryInterface(__uuidof(IDWriteLocalFontFileLoader), (void **)&fileLoader);
    if (SUCCEEDED(hr)) {
      // get the file path
      HR(files[0].GetReferenceKey(&referenceKey, &referenceKeySize));
      HR(fileLoader->GetFilePathLengthFromKey(referenceKey, referenceKeySize, &nameLength));

      name = new WCHAR[nameLength + 1];
      HR(fileLoader->GetFilePathFromKey(referenceKey, referenceKeySize, name, nameLength + 1));

      char *psName = utf16ToUtf8(name);
      char *postscriptName = getString(font, DWRITE_INFORMATIONAL_STRING_POSTSCRIPT_NAME);
      char *family = getString(font, DWRITE_INFORMATIONAL_STRING_WIN32_FAMILY_NAMES);
      char *style = getString(font, DWRITE_INFORMATIONAL_STRING_WIN32_SUBFAMILY_NAMES);

      // this method requires windows 7, so we need to cast to an IDWriteFontFace1
      IDWriteFontFace1 *face1 = static_cast<IDWriteFontFace1 *>(face);
      bool monospace = face1->IsMonospacedFont() == TRUE;

	  res.path = psName;
	  res.postscriptName = postscriptName;
	  res.family = family;
	  res.style = style;
	  res.weight = (FontWeight)font->GetWeight();
	res.width = (FontWidth)font->GetStretch();
	res.italic = font->GetStyle() == DWRITE_FONT_STYLE_ITALIC;
		res.monospace = monospace;

      delete psName;
      delete name;
      delete postscriptName;
      delete family;
      delete style;
      fileLoader->Release();
    }

    loader->Release();
  }

  face->Release();
  files->Release();

  return res;
}

std::vector<FontDescriptor> FontManager::getAvailableFonts() {
	std::vector<FontDescriptor> res;
  int count = 0;

  IDWriteFactory *factory = NULL;
  HR(DWriteCreateFactory(
    DWRITE_FACTORY_TYPE_SHARED,
    __uuidof(IDWriteFactory),
    reinterpret_cast<IUnknown**>(&factory)
  ));

  // Get the system font collection.
  IDWriteFontCollection *collection = NULL;
  HR(factory->GetSystemFontCollection(&collection));

  // Get the number of font families in the collection.
  int familyCount = collection->GetFontFamilyCount();

  // track postscript names we've already added
  // using a set so we don't get any duplicates.
  std::unordered_set<std::string> psNames;

  for (int i = 0; i < familyCount; i++) {
    IDWriteFontFamily *family = NULL;

    // Get the font family.
    HR(collection->GetFontFamily(i, &family));
    int fontCount = family->GetFontCount();

    for (int j = 0; j < fontCount; j++) {
      IDWriteFont *font = NULL;
      HR(family->GetFont(j, &font));

      FontDescriptor result = resultFromFont(font);
      if (psNames.count(result.postscriptName) == 0) {
        res.push_back(resultFromFont(font));
        psNames.insert(result.postscriptName);
      }
    }

    family->Release();
  }

  collection->Release();
  factory->Release();

  return res;
}

bool resultMatches(const FontDescriptor& result, const FontDescriptor& desc) {
  if (!desc.postscriptName.empty() && desc.postscriptName.compare(result.postscriptName) != 0)
    return false;

  if (!desc.family.empty() && desc.family.compare(result.family) != 0)
    return false;

  if (!desc.style.empty() && desc.style.compare(result.style) != 0)
    return false;

  if (desc.weight != 0 && desc.weight != result.weight)
    return false;

  if (desc.width != 0 && desc.width != result.width)
    return false;

  if (desc.italic != result.italic)
    return false;

  if (desc.monospace != result.monospace)
    return false;

  return true;
}

std::vector<FontDescriptor> FontManager::findFonts(const FontDescriptor& desc) {
  auto fonts = getAvailableFonts();

  for (std::vector<FontDescriptor>::iterator it = fonts.begin(); it != fonts.end();) {
    if (!resultMatches(*it, desc)) {
      it = fonts.erase(it);
    } else {
      it++;
    }
  }

  return fonts;
}

FontDescriptor FontManager::findFont(const FontDescriptor& desc) {
  auto fonts = findFonts(desc);

  // if we didn't find anything, try again with only the font traits, no string names
  if (fonts.size() == 0) {

	  FontDescriptor fallback;
	  fallback.weight = desc.weight;
	  fallback.width = desc.width;
	  fallback.italic = desc.italic;
	  fallback.monospace = false;

    fonts = findFonts(fallback);
  }

  // ok, nothing. shouldn't happen often. 
  // just return the first available font
  if (fonts.size() == 0) {
    fonts = getAvailableFonts();
  }

  // hopefully we found something now.
  // copy and return the first result
  if (fonts.size() > 0) {
	  return fonts.front();
  }

  std::cerr << "No fonts found on system. Catastrophic error." << std::endl;
  return FontDescriptor();
}

// custom text renderer used to determine the fallback font for a given char
class FontFallbackRenderer : public IDWriteTextRenderer {
public:
  IDWriteFontCollection *systemFonts;
  IDWriteFont *font;
  unsigned long refCount;

  FontFallbackRenderer(IDWriteFontCollection *collection) {
    refCount = 0;
    collection->AddRef();
    systemFonts = collection;
    font = NULL;
  }

  ~FontFallbackRenderer() {
    if (systemFonts)
      systemFonts->Release();

    if (font)
      font->Release();
  }

  // IDWriteTextRenderer methods
  IFACEMETHOD(DrawGlyphRun)(
      void *clientDrawingContext,
      FLOAT baselineOriginX,
      FLOAT baselineOriginY,
      DWRITE_MEASURING_MODE measuringMode,
      DWRITE_GLYPH_RUN const *glyphRun,
      DWRITE_GLYPH_RUN_DESCRIPTION const *glyphRunDescription,
      IUnknown *clientDrawingEffect) {

    // save the font that was actually rendered
    return systemFonts->GetFontFromFontFace(glyphRun->fontFace, &font);
  }

  IFACEMETHOD(DrawUnderline)(
      void *clientDrawingContext,
      FLOAT baselineOriginX,
      FLOAT baselineOriginY,
      DWRITE_UNDERLINE const *underline,
      IUnknown *clientDrawingEffect) {
    return E_NOTIMPL;
  }


  IFACEMETHOD(DrawStrikethrough)(
      void *clientDrawingContext,
      FLOAT baselineOriginX,
      FLOAT baselineOriginY,
      DWRITE_STRIKETHROUGH const *strikethrough,
      IUnknown *clientDrawingEffect) {
    return E_NOTIMPL;
  }


  IFACEMETHOD(DrawInlineObject)(
      void *clientDrawingContext,
      FLOAT originX,
      FLOAT originY,
      IDWriteInlineObject *inlineObject,
      BOOL isSideways,
      BOOL isRightToLeft,
      IUnknown *clientDrawingEffect) {
    return E_NOTIMPL;
  }

  // IDWritePixelSnapping methods
  IFACEMETHOD(IsPixelSnappingDisabled)(void *clientDrawingContext, BOOL *isDisabled) {
    *isDisabled = FALSE;
    return S_OK;
  }

  IFACEMETHOD(GetCurrentTransform)(void *clientDrawingContext, DWRITE_MATRIX *transform) {
    const DWRITE_MATRIX ident = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    *transform = ident;
    return S_OK;
  }

  IFACEMETHOD(GetPixelsPerDip)(void *clientDrawingContext, FLOAT *pixelsPerDip) {
    *pixelsPerDip = 1.0f;
    return S_OK;
  }

  // IUnknown methods
  IFACEMETHOD_(unsigned long, AddRef)() {
    return InterlockedIncrement(&refCount);
  }

  IFACEMETHOD_(unsigned long,  Release)() {
    unsigned long newCount = InterlockedDecrement(&refCount);
    if (newCount == 0) {
      delete this;
      return 0;
    }

    return newCount;
  }

  IFACEMETHOD(QueryInterface)(IID const& riid, void **ppvObject) {
    if (__uuidof(IDWriteTextRenderer) == riid) {
      *ppvObject = this;
    } else if (__uuidof(IDWritePixelSnapping) == riid) {
      *ppvObject = this;
    } else if (__uuidof(IUnknown) == riid) {
      *ppvObject = this;
    } else {
      *ppvObject = nullptr;
      return E_FAIL;
    }

    this->AddRef();
    return S_OK;
  }
};

FontDescriptor FontManager::substituteFont(const std::string& postscriptName, const std::string& utf8Text) {
  FontDescriptor res;

  IDWriteFactory *factory = NULL;
  HR(DWriteCreateFactory(
    DWRITE_FACTORY_TYPE_SHARED,
    __uuidof(IDWriteFactory),
    reinterpret_cast<IUnknown**>(&factory)
  ));

  // Get the system font collection.
  IDWriteFontCollection *collection = NULL;
  HR(factory->GetSystemFontCollection(&collection));

  // find the font for the given postscript name
  FontDescriptor desc;
  desc.postscriptName = postscriptName;
  FontDescriptor font = findFont(desc);

  // create a text format object for this font
  IDWriteTextFormat *format = NULL;

 // if (font) {
    WCHAR *familyName = utf8ToUtf16(font.family.data());

    // create a text format
    HR(factory->CreateTextFormat(
      familyName,
      collection,
      (DWRITE_FONT_WEIGHT) font.weight,
      font.italic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
      (DWRITE_FONT_STRETCH) font.width,
      12.0,
      L"en-us",
      &format
    ));

    delete familyName;
    //delete font;
  //}
  /*else {
	// this should never happen, but just in case, let the system
	// decide the default font in case findFont returned nothing.
	HR(factory->CreateTextFormat(
	  L"",
	  collection,
	  DWRITE_FONT_WEIGHT_REGULAR,
	  DWRITE_FONT_STYLE_NORMAL,
	  DWRITE_FONT_STRETCH_NORMAL,
	  12.0,
	  L"en-us",
	  &format
	));
  }
  */

  // convert utf8 string for substitution to utf16
  WCHAR *str = utf8ToUtf16(utf8Text.data());

  // create a text layout for the substitution string
  IDWriteTextLayout *layout = NULL;
  HR(factory->CreateTextLayout(
    str,
    wcslen(str),
    format,
    100.0,
    100.0,
    &layout
  ));

  // render it using a custom renderer that saves the physical font being used
  FontFallbackRenderer *renderer = new FontFallbackRenderer(collection);
  HR(layout->Draw(NULL, renderer, 100.0, 100.0));

  // if we found something, create a result object
  if (renderer->font) {
    res = resultFromFont(renderer->font);
  }

  // free all the things
  delete renderer;
  layout->Release();
  format->Release();

//  desc->postscriptName = NULL;
//  delete desc;
  delete str;
  collection->Release();
  factory->Release();

  return res;
}


} } // namespace ofx::Text


#endif
