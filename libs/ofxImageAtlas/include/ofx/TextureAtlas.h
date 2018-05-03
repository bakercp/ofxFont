//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofx/PixelsAtlas.h"
#include "ofBaseTypes.h"
#include "ofTexture.h"


namespace ofx {


template <typename PixelType>
class TextureAtlas_:
    public PixelsAtlas_<PixelType>,
    public ofBaseHasTexture,
    public ofBaseUpdates
{
public:
    /// \brief Create a default texture atlas.
	TextureAtlas_();

    /// \brief Destroy the texture atlas.
	virtual ~TextureAtlas_();

    virtual void update() override;

    virtual ofTexture& getTexture() override;
    
    virtual const ofTexture& getTexture() const override;

    virtual void setUseTexture(bool useTexture) override;

    virtual bool isUsingTexture() const override;

protected:
    /// \brief The internal texture.
    ofTexture _texture;

    /// \brief True if it should use the internal texture.
    bool _useTexture;

};


typedef TextureAtlas_<unsigned char> TextureAtlas;


template<typename PixelType>
TextureAtlas_<PixelType>::TextureAtlas_():
    _useTexture(true)
{
}


template<typename PixelType>
TextureAtlas_<PixelType>::~TextureAtlas_()
{
}


template<typename PixelType>
void TextureAtlas_<PixelType>::update()
{
////    cout << "<<1>> > ut=" << _useTexture << " pa=" << this->_pixels.isAllocated() << " hnp=" <<  ofPixelsAtlas_<PixelType>::_hasNewPixels << endl;
//
//    if (_useTexture && this->_pixels.isAllocated() && PixelsAtlas_<PixelType>::_hasNewPixels)
//    {
////        cout << "<<2>>" << endl;
//		int glTypeInternal = ofGetGlInternalFormat(this->_pixels);
//
////        cout << "<<ta=>>" << _texture.isAllocated()  << endl;
////        cout << "==" << (_texture.getWidth()  != this->_pixels.getWidth()) << endl;
////        cout << "==" << (_texture.getHeight() != this->_pixels.getHeight()) << endl;
////        cout << "==" << (_texture.getTextureData().glTypeInternal != glTypeInternal) << endl;
//
//		if(!_texture.isAllocated() ||
//           _texture.getWidth()  != this->_pixels.getWidth()  ||
//           _texture.getHeight() != this->_pixels.getHeight() ||
//           _texture.getTextureData().glTypeInternal != glTypeInternal)
//        {
////            cout << "<<3>>" << endl;
//
//            _texture.allocate(this->_pixels.getWidth(),
//                              this->_pixels.getHeight(),
//                              glTypeInternal);
//			if(ofGetGLProgrammableRenderer() &&
//               (this->_pixels.getNumChannels() == 1 ||
//                this->_pixels.getNumChannels() == 2))
//            {
////                cout << "<<4>>" << endl;
//				_texture.setRGToRGBASwizzles(true);
//			}
//		}
////        cout << "<<5>>" << endl;
//
//		_texture.loadData(this->_pixels);
//    }
//
}


template<typename PixelType>
ofTexture& TextureAtlas_<PixelType>::getTexture()
{
    return _texture;
}


template<typename PixelType>
const ofTexture& TextureAtlas_<PixelType>::getTexture() const
{
    return _texture;
}


template<typename PixelType>
void TextureAtlas_<PixelType>::setUseTexture(bool useTexture)
{
    _useTexture = useTexture;

    if (_useTexture)
    {
        update();
    }
}


template<typename PixelType>
bool TextureAtlas_<PixelType>::isUsingTexture() const
{
    return _useTexture;
}


} // namespace ofx
