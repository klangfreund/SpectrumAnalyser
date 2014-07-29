/*
  ==============================================================================

    SpectroscopeProcessor.cpp
    Created: 27 Jul 2014 2:34:48pm
    Author:  Samuel Gaehwiler

  ==============================================================================
*/

#include "SpectrumProcessor.h"

SpectrumProcessor::SpectrumProcessor (int fftSizeLog2)
  : fftEngine       {fftSizeLog2},
    tempBlock       (fftEngine.getFFTSize()),
    circularBuffer  (fftEngine.getMagnitudesBuffer().getSize() * 4),
    needToProcess   {false},
    pitch           {var(0)},
    repaintViewer   (var(false))
{
    fftEngine.setWindowType (drow::Window::Hann);
    
    circularBuffer.reset();
    
    pitchDetector.setMinMaxFrequency (20, 20000);
}

SpectrumProcessor::~SpectrumProcessor()
{
}

void SpectrumProcessor::setSampleRate (double sampleRate)
{
    pitchDetector.setSampleRate (sampleRate);
}

void SpectrumProcessor::copySamples (const float* samples, int numSamples)
{
	circularBuffer.writeSamples (samples, numSamples);
	needToProcess = true;
}

int SpectrumProcessor::useTimeSlice()
{
    const int sleepTime = 5; // [ms]
    
//	if (paused)
//    {
//		return sleepTime;
//	}
//	else
//	{
		if (needToProcess)
        {
			process();
            needToProcess = false;
        }
        
		return sleepTime;
//	}
}

void SpectrumProcessor::process()
{
    jassert (circularBuffer.getNumFree() != 0); // buffer is too small!
    
    while (circularBuffer.getNumAvailable() > fftEngine.getFFTSize())
	{
		circularBuffer.readSamples (tempBlock.getData(), fftEngine.getFFTSize());
		fftEngine.performFFT (tempBlock);
		fftEngine.updateMagnitudesIfBigger();
        
        pitchDetector.processSamples(tempBlock.getData(), fftEngine.getFFTSize());
        pitch = pitchDetector.getPitch();
		
		repaintViewer = true;
	}
}

Value& SpectrumProcessor::getRepaintViewerValue()
{
    return repaintViewer;
}


drow::Buffer& SpectrumProcessor::getMagnitudesBuffer()
{
    return fftEngine.getMagnitudesBuffer();
}

Value& SpectrumProcessor::getPitchValue()
{
    return pitch;
}
