/*
  ==============================================================================

    Oscillator.h
    Created: 24 Jan 2014 12:38:07pm
    Author:  Marc Wilhite

  ==============================================================================
*/

#ifndef OSCILLATOR_H_INCLUDED
#define OSCILLATOR_H_INCLUDED

#include <iostream>
#include <math.h>

class Oscillator {
private:
    const double mPI;
    const double twoPI;
    bool isMuted;
    double mFrequency;
    double mPhase;
    double mSampleRate;
    int mOvertoneLimit;
    double mPhaseIncrement;
    void updateIncrement();
    
public:
    void setFrequency(double frequency);
    void setSampleRate(double sampleRate);
    void generate(double* buffer, int nFrames);
    inline void setMuted(bool muted) { isMuted = muted; }
    float nextSample();
    Oscillator() :
    mPI(2*acos(0.0)),
    twoPI(2 * mPI),
    isMuted(false), 
    mFrequency(440.0),
    mPhase(0.0),
    mSampleRate(44100.0) { updateIncrement(); };
};

#endif  // OSCILLATOR_H_INCLUDED
