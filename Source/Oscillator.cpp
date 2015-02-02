/*
  ==============================================================================

    Oscillator.cpp
    Created: 24 Jan 2014 12:38:07pm
    Author:  Marc Wilhite

  ==============================================================================
*/

#include "Oscillator.h"

void Oscillator::setMode(OscillatorMode mode) {
    mOscillatorMode = mode;
}

void Oscillator::setFrequency(double frequency) {
    mFrequency = frequency;
    mOvertoneLimit = (mSampleRate / 2) / mFrequency;
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
    switch (mOscillatorMode) {
        case OSCILLATOR_MODE_SINE:
            for (int i = 0; i < nFrames; i++) {
                buffer[i] = sin(mPhase);
                mPhase += mPhaseIncrement;
                while (mPhase >= twoPI) {
                    mPhase -= twoPI;
                }
            }
            break;
        case OSCILLATOR_MODE_SAW:
            for (int i = 0; i < nFrames; i++) {
                buffer[i] = 1.0 - (2.0 * mPhase / twoPI);
                mPhase += mPhaseIncrement;
                while (mPhase >= twoPI) {
                    mPhase -= twoPI;
                }
            }
            break;
        case OSCILLATOR_MODE_SQUARE:
            for (int i = 0; i < nFrames; i++) {
                if (mPhase <= mPI) {
                    buffer[i] = 1.0;
                } else {
                    buffer[i] = -1.0;
                }
                mPhase += mPhaseIncrement;
                while (mPhase >= twoPI) {
                    mPhase -= twoPI;
                }
            }
            break;
        case OSCILLATOR_MODE_TRIANGLE:
            for (int i = 0; i < nFrames; i++) {
                double value = -1.0 + (2.0 * mPhase / twoPI);
                buffer[i] = 2.0 * (fabs(value) - 0.5);
                mPhase += mPhaseIncrement;
                while (mPhase >= twoPI) {
                    mPhase -= twoPI;
                }
            }
            break;
    }
}

float Oscillator::nextSample() {
    float value = 0.0;
    if(isMuted) return value;
    
    switch (mOscillatorMode) {
        case OSCILLATOR_MODE_SINE:
            value = sin(mPhase);
            break;
        case OSCILLATOR_MODE_SAW:
            value = 0;
            for (int k = 1; k <= mOvertoneLimit; k++) {
                value += (1.0/k) * sin(k * mPhase);
            }
            break;
        case OSCILLATOR_MODE_SQUARE:
            value = 0;
            for (int k = 1; k <= mOvertoneLimit; k++, k++) {
                value += (1.0/k) * sin(k * mPhase);
            }
            
            break;
        case OSCILLATOR_MODE_TRIANGLE:
            value = 0;
            for (int k = 1; k < mOvertoneLimit; k++,k++) {
                value += pow(-1.0,(k-1)/2) * (1/pow(k,2)) * sin(k * mPhase);
            }
            
            break;
    }
    mPhase += mPhaseIncrement;
    while (mPhase >= twoPI) {
        mPhase -= twoPI;
    }
    return value;
}