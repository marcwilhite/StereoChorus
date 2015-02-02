/*
  ==============================================================================

    Oscillator.cpp
    Created: 24 Jan 2014 12:38:07pm
    Author:  Marc Wilhite

  ==============================================================================
*/

#include "Oscillator.h"


void Oscillator::setFrequency(double frequency) {
    mFrequency = frequency;
    updateIncrement();
}

void Oscillator::setSampleRate(double sampleRate) {
    mSampleRate = sampleRate;
    updateIncrement();
}

void Oscillator::updateIncrement() {
    mPhaseIncrement = mFrequency * twoPI / mSampleRate;
}

void Oscillator::generate(double* buffer, int nFrames) {
    for (int i = 0; i < nFrames; i++) {
        buffer[i] = sin(mPhase);
        mPhase += mPhaseIncrement;
        while (mPhase >= twoPI) {
            mPhase -= twoPI;
        }
    }
}

float Oscillator::nextSample() {
    float value = 0.0;
    if(isMuted) return value;
   
    value = sin(mPhase);
    
    mPhase += mPhaseIncrement;
    while (mPhase >= twoPI) {
        mPhase -= twoPI;
    }
    return value;
}