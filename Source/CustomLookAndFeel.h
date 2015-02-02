/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 24 Jan 2014 12:00:24am
    Author:  Marc Wilhite

  ==============================================================================
*/

#ifndef CUSTOMLOOKANDFEEL_H_INCLUDED
#define CUSTOMLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class CustomLookAndFeel   : public LookAndFeel_V1
{
public:
    //==============================================================================
    /** Creates the default JUCE look and feel. */
    CustomLookAndFeel();
    
	virtual void drawRotarySlider	(	Graphics & 	g,
									 int 	x,
									 int 	y,
									 int 	width,
									 int 	height,
									 float 	sliderPosProportional,
									 float 	rotaryStartAngle,
									 float 	rotaryEndAngle,
									 Slider & 	slider );
};

#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
