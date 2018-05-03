//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofBaseTypes.h"
#include "ofPixels.h"
#include "ofBaseOnlineRectanglePacker.h"


namespace ofx {


struct RotatedRectangle
{
    ofRectangle rectangle;
    ofOrientation orientation = OF_ORIENTATION_DEFAULT;
};


template <typename PixelType>
class PixelsAtlas_:
    public ofBaseOnlineRectanglePacker_<int>,
    public ofBaseHasPixels_<PixelType>
{
public:
	PixelsAtlas_();

	virtual ~PixelsAtlas_();

    //virtual void update();

	virtual void allocate(int w, int h, int channels);
	virtual void allocate(int w, int h, ofPixelFormat type);
	virtual void allocate(int w, int h, ofImageType type);

    ofPixels_<PixelType>& getPixels() override;

    const ofPixels_<PixelType>& getPixels() const override;
    int getWidth() const override;
    int getHeight() const override;

    /// \brief 
    virtual bool pack(ofPixels_<PixelType>& pixels,
                      ofRectangle& packedRectangle,
                      ofOrientation& packedOrientation);

    /// \returns true if pixels have changed since the last update.
    bool hasNewPixels() const;
    
protected:
    enum
    {
        DEFAULT_ATLAS_PADDING = 1
    };

    ofPixels_<PixelType> _pixels;

    bool _hasNewPixels;

};


template<typename PixelType>
PixelsAtlas_<PixelType>::PixelsAtlas_():
    ofBaseOnlineRectanglePacker_<int>(DEFAULT_ATLAS_PADDING),
    _hasNewPixels(false)
{
}


template<typename PixelType>
PixelsAtlas_<PixelType>::~PixelsAtlas_()
{
    _pixels.clear();
}


template<typename PixelType>
bool PixelsAtlas_<PixelType>::pack(ofPixels_<PixelType>& pixels,
                                   ofRectangle& packedRectangle,
                                   ofOrientation& packedOrientation)
{
    _hasNewPixels = false;

    int packedX = 0;
    int packedY = 0;
    int packedWidth = 0;
    int packedHeight = 0;

    if (ofBaseOnlineRectanglePacker_<int>::pack(pixels.getWidth(),
                                                pixels.getHeight(),
                                                packedX,
                                                packedY,
                                                packedWidth,
                                                packedHeight,
                                                packedOrientation)
    &&  pixels.pasteInto(_pixels,
                         packedRectangle.x,
                         packedRectangle.y))
    {
        _hasNewPixels = true;
        packedRectangle.set(packedX, packedY, packedWidth, packedHeight);
    }
    else
    {
        packedRectangle.set(0, 0, 0, 0);
        packedOrientation = OF_ORIENTATION_DEFAULT;
    }

    return _hasNewPixels;
}


template<typename PixelType>
void PixelsAtlas_<PixelType>::allocate(int w, int h, int channels)
{
    _pixels.allocate(w, h, channels);
}


template<typename PixelType>
void PixelsAtlas_<PixelType>::allocate(int w, int h, ofPixelFormat type)
{
    _pixels.allocate(w, h, type);
}


template<typename PixelType>
void PixelsAtlas_<PixelType>::allocate(int w, int h, ofImageType type)
{
    _pixels.allocate(w, h, type);
}


template <typename PixelType>
ofPixels_<PixelType>& PixelsAtlas_<PixelType>::getPixels()
{
    return _pixels;
}


template <typename PixelType>
const ofPixels_<PixelType>& PixelsAtlas_<PixelType>::getPixels() const
{
    return _pixels;
}


template <typename PixelType>
int PixelsAtlas_<PixelType>::getWidth() const
{
    return _pixels.getWidth();
}


template <typename PixelType>
int PixelsAtlas_<PixelType>::getHeight() const
{
    return _pixels.getHeight();
}


template <typename PixelType>
bool PixelsAtlas_<PixelType>::hasNewPixels() const
{
    return _hasNewPixels;
}


} // namespace ofx
