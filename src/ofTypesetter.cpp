
#include "ofTypesetter.h"

//------------------------------------------------------------------
string ofTypsetterLangaugeToString(ofTypesetterLanguage lang) {
    switch (lang) {
        case OF_TYPESETTER_LANG_DE:
            return "de";
            break;
        case OF_TYPESETTER_LANG_ES:
            return "es";
            break;
        case OF_TYPESETTER_LANG_FR:
            return "fr";
            break;
        case OF_TYPESETTER_LANG_RU:
            return "ru";
            break;
        case OF_TYPESETTER_LANG_ZH:
            return "zh";
            break;
        case OF_TYPESETTER_LANG_EN:
        default:
            return "en";
            break;
    }
}


//------------------------------------------------------------------
ofTypesetter::ofTypesetter() {
    font = NULL;
    lang = OF_TYPESETTER_LANG_EN;
}

//------------------------------------------------------------------
ofTypesetter::~ofTypesetter() {}

//------------------------------------------------------------------
void ofTypesetter::setFont(ofFont* _font) {
    if(_font != NULL) {
        font = _font;
    }
}

//------------------------------------------------------------------
ofFont* ofTypesetter::getFont() {
    return font;
}

//------------------------------------------------------------------
bool ofTypesetter::isFontLoaded() {
    return font != NULL;
}

//------------------------------------------------------------------
string ofTypesetter::hyphenate(string utf8String) {
    // TODO: implement this with ofxHyphenate
    return utf8String;
}

//------------------------------------------------------------------
vector<ofUniCharBreak> ofTypesetter::breakLines(string utf8String) {
   
    /*
    string language = ofTextLangaugeToString(lang);

    const ofUTF8Char* buffer = reinterpret_cast<const ofUTF8Char*>(utf8String.c_str());
    size_t count = utf8String.length();
    
    char breakData[count];

    // set breakpoints
    set_linebreaks_utf8(buffer,count,language.c_str(),breakData);
    
    vector<ofUniCharBreak> breaks; // the array of chars and their breaks
    
    // multibyte character iteration
    Poco::UTF8Encoding utf8;
    Poco::TextIterator iter(utf8String, utf8);
    Poco::TextIterator end(utf8String);
    
    for(int i = 0; i < count; i++) {
        if(breakData[i] != LINEBREAK_INSIDEACHAR) {
            if(iter != end) {
                breaks.push_back(ofUniCharBreak(*(iter++),breakData[i]));
            } else {
                ofLog(OF_LOG_ERROR,"Error calculating line breaks.");
            }
        }
    }
    
    for(int i = 0; i < breaks.size(); i++) {
        if(breaks[i].breakStatus == LINEBREAK_MUSTBREAK) {
            cout << "LINEBREAK_MUSTBREAK" << endl;
        } else if(breaks[i].breakStatus == LINEBREAK_ALLOWBREAK) {
            cout << "LINEBREAK_ALLOWBREAK" << endl;
        } else if(breaks[i].breakStatus == LINEBREAK_NOBREAK) {
            cout << "LINEBREAK_NOBREAK" << endl;
        } else if(breaks[i].breakStatus == LINEBREAK_INSIDEACHAR) {
            cout << "LINEBREAK_INSIDEACHAR" << endl;
        }
    }
     */
}

//------------------------------------------------------------------
void ofTypesetter::setLanguage(ofTypesetterLanguage _lang) {
    lang = lang;
}

//------------------------------------------------------------------
ofTypesetterLanguage ofTypesetter::getLanguage() {
    return lang;
}
