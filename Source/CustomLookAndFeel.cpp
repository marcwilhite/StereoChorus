/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 24 Jan 2014 12:00:24am
    Author:  Marc Wilhite

  ==============================================================================
*/



#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    
}
void CustomLookAndFeel::drawRotarySlider	(	Graphics & 	g,
                                         int 	x,
                                         int 	y,
                                         int 	width,
                                         int 	height,
                                         float 	sliderPosProportional,
                                         float 	rotaryStartAngle,
                                         float 	rotaryEndAngle,
                                         Slider & 	slider )
{
	// This is the binary image data that uses very little CPU when rotating
	Image myStrip = ImageCache::getFromMemory (BinaryData::knob_png, BinaryData::knob_pngSize);
    
	const double fractRotation = (slider.getValue() - slider.getMinimum())  /   (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
	const int nFrames = myStrip.getHeight()/myStrip.getWidth(); // number of frames for vertical film strip
	const int frameIdx = (int)ceil(fractRotation * ((double)nFrames-1.0) ); // current index from 0 --> nFrames-1
    
	const float radius = jmin (width / 2.0f, height / 2.0f) ;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius - 1.0f;
    const float ry = centreY - radius - 1.0f;
    
	g.drawImage(myStrip,
				(int)rx,
                (int)ry,
                2*(int)radius,
                2*(int)radius,   //Dest
				0,
                frameIdx*myStrip.getWidth(),
                myStrip.getWidth(),
                myStrip.getWidth()); //Source
    
}
