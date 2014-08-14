/*
  ==============================================================================

    SpectroscopeViewer.cpp
    Created: 27 Jul 2014 2:34:48pm
    Author:  Samuel Gaehwiler

    Heavily based on the dRowAudio Spectroscope class by David Rowland.
 
  ==============================================================================
*/

#include "SpectrumViewer.h"

#if JUCE_MAC || JUCE_IOS || DROWAUDIO_USE_FFTREAL


// static member initialisation
// ============================

const int SpectrumViewer::frequenciesToPlot[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000};
const int SpectrumViewer::numberOfFrequenciesToPlot = 29;


//==============================================================================
SpectrumViewer::SpectrumViewer (Value& repaintViewerValue,
                                drow::Buffer& magnitudeBuffer,
                                Value& detectedFrequencyValue)
  : sampleRate                {44100.0},
    repaintViewer             (var(false)),
    fftMagnitudeBuffer        {magnitudeBuffer},
    detectedFrequency         {var(0)},
    frequencyToDisplay        {var(0)},
    mouseMode                 {false},
    mouseXPosition            {0},
    heightForFrequencyCaption {20},
    gradientImage             (Image::RGB, 100, 100, false)
{
// TODO: Is this ok?
	setOpaque (true);
    
    repaintViewer.referTo (repaintViewerValue);
    
    detectedFrequency.referTo (detectedFrequencyValue);
    detectedFrequency.addListener(this);

    gradientImage.clear (gradientImage.getBounds(), Colours::black);
    
//    ScopedPointer<Drawable> logo571 = Drawable::createFromSVG(const juce::XmlElement &svgDocument);
    
//    XmlDocument xml571 (String::fromUTF8 (BinaryData::_571_svg, BinaryData::_571_svgSize));
//    
//    XmlElement* xmlElement571 = XmlDocument::parse (String::fromUTF8 (BinaryData::_571_svg, BinaryData::_571_svgSize));
    
    path571.addPath (Drawable::parseSVGPath ("M32.344,50.159c-1.846-0.053-5.02,0.628-5.695-0.542c-0.447-0.775,0.049-2.769,0.135-3.796		c0.594-6.987,1.07-12.29,1.898-19.119c0.248-2.04,0.312-6.502,1.355-7.187c0.672-0.44,1.975-0.271,3.391-0.271		c6.305,0,12.123,0,18.441,0c2.361,0,6.029,0.338,6.914-0.542c0.641-0.637,0.486-2,0.543-3.525c0.123-3.277,0.064-5.042,0-7.729		c-0.037-1.53,0.117-3.021-0.543-3.661c-1.023-0.995-5.918-0.482-8.406-0.542c-8.32-0.2-19.002-0.062-26.982,0		c-1.27,0.01-7.033-0.601-8.271,0.542c-0.621,0.573-0.615,1.899-0.814,3.525c-0.164,1.341-0.434,2.709-0.541,3.797		c-0.504,5.083-0.93,10.542-1.627,15.458c-0.365,2.572-0.689,5.091-0.949,7.729c-0.836,8.452-1.799,18.998-2.848,27.525		c-0.207,1.672-0.377,3.062,0.271,3.661c0.582,0.54,2.881,0.407,4.203,0.407c4.768,0,9.34,0,13.83,0c3.23,0,6.018,0.244,8.678,0.678		c3.033,0.495,6.01,1.694,8,2.983c1.123,0.727,2.473,1.638,3.391,2.441c0.6,0.527,1.051,1.26,1.49,1.763		c0.133,0.15,0.281,0.265,0.408,0.407c1.711,1.935,3.143,4.964,3.66,8.136c0.803,4.919-0.727,10.845-2.576,14.102		c-0.648,1.143-1.799,2.378-2.713,3.39c-3.242,3.59-8.703,5.65-15.32,5.288c-1.396-0.076-2.922-0.03-4.34-0.406		c-1.123-0.298-2.184-0.955-3.254-1.492c-2.023-1.014-3.404-1.831-4.881-3.254c-0.867-0.834-1.93-1.694-2.713-2.576		c-0.801-0.902-1.508-2.491-2.848-2.441c-0.809,0.031-1.664,1.027-2.17,1.492c-0.359,0.332-0.609,0.689-0.812,0.949		c-0.725,0.929-1.741,1.843-2.441,2.576c-0.856,0.896-1.539,1.403-2.305,2.169c-0.613,0.614-2.02,1.936-2.033,2.983		c-0.016,1.154,1.494,2.761,2.168,3.526c0.305,0.343,0.615,0.721,0.949,1.084c3.895,4.241,8.547,7.396,14.104,9.356		c2.021,0.713,4.039,1.346,6.102,1.627c10.092,1.375,18.793-0.952,24.678-4.882c1.564-1.045,3.334-2.257,4.609-3.39		c0.16-0.143,0.248-0.397,0.406-0.542c0.832-0.763,1.924-1.603,2.576-2.305c0.094-0.1,0.485-0.775,0.579-0.881		c0.576-0.66,0.804-0.736,1.319-1.424c0.256-0.34,0.414-0.742,0.678-1.085c0.293-0.376,0.549-0.698,0.814-1.085		c3.656-5.312,5.85-12.394,5.695-20.203c-0.15-7.627-2.629-14.665-6.373-19.525c-0.918-1.192-1.832-2.401-2.848-3.525		c-1.004-1.112-2.068-2.208-3.254-3.254c-1.256-1.109-2.547-1.883-3.797-2.712c-2.641-1.751-6.102-3.362-9.355-4.339		c-1.057-0.316-2.422-0.687-3.254-0.813"));
    path571.addPath (Drawable::parseSVGPath ("M72.616,119.176c3.352,0.093,5.652,0,8.678,0c1.357,0,3.121,0.154,4.066-0.271		c1.334-0.599,2.404-3.63,3.525-5.831c3.279-6.433,6.328-12.966,9.357-18.847c0.523-1.018,0.984-2.071,1.49-3.119		c0.51-1.053,1.104-2.076,1.627-3.119c1.078-2.142,1.959-4.286,2.984-6.373c1.039-2.114,2.141-4.103,3.119-6.237		c0.979-2.137,2.195-4.18,3.254-6.237c1.094-2.127,1.92-4.376,2.982-6.373c1.133-2.13,2.131-4.217,3.119-6.237		c3.094-6.325,6.314-12.613,9.355-18.848c0.502-1.027,0.967-2.085,1.492-3.119c0.561-1.105,1.217-2.582,1.762-3.525		c0.559-0.965,0.941-1.835,1.357-2.712c0.562-1.194,1.236-2.616,1.762-3.525c0.273-0.471,0.334-0.794,0.543-1.22		c0.754-1.548,2.002-3.389,2.305-4.881c0.406-2.003,0.135-4.829,0.135-7.729c0-2.527,0.441-6.203-0.541-7.187		c-0.779-0.778-5.098-0.577-6.781-0.542c-8.043,0.167-16.141,0-23.592,0c-10.396,0-22.26-0.275-31.459,0		c-1.336,0.04-2.633,0-3.254,0.949c-0.676,1.032-0.271,5.372-0.271,7.186c0,2.135-0.48,6.103,0.543,7.187		c0.762,0.807,3.029,0.678,5.152,0.678c12.533,0,23.344,0,35.662,0c1.826,0,5.09-0.175,5.559,0.407		c0.268,0.333-0.477,2.045-0.949,2.983c-1.629,3.24-3.26,6.369-4.609,9.22c-2.146,4.527-4.748,9.592-6.781,13.695		c-0.533,1.079-1.029,2.178-1.49,3.119c-2.029,4.146-4.166,8.374-6.102,12.339c-0.756,1.544-1.648,3.648-2.441,5.017		c-0.555,0.959-0.943,1.846-1.355,2.712c-1.447,3.038-3.002,6.29-4.475,9.221c-2.098,4.17-4.178,8.279-6.102,12.339		c-0.41,0.863-1.051,1.838-1.357,2.576c-0.092,0.224-0.197,0.267-0.27,0.407c-1.123,2.155-2.021,4.612-3.119,6.508		c-0.082,0.141-0.057,0.242-0.137,0.407c-0.416,0.86-0.805,1.542-1.219,2.305c-1.691,3.113-3.057,6.709-4.746,9.627		c-0.369,0.636-0.705,1.386-0.949,1.898c-0.137,0.284-0.135,0.662-0.271,0.949c-0.264,0.55-0.654,1.005-0.814,1.492		C68.536,118.985,69.901,119.101,72.616,119.176z"));
    path571.addPath (Drawable::parseSVGPath ("M142.852,21.956c0.494,1.583,1.24,5.581,2.441,6.237c0.828,0.453,2.166,0.212,3.525,0		c2.107-0.33,3.4-0.792,4.881-1.221c1.293-0.374,4.182-1.611,4.746-1.22c0.691,0.479,0.406,3.861,0.406,5.424		c0,17.959-0.135,35.103-0.135,52.61c0,8.433,0,14.985,0,23.458c0,2.238-0.578,10.062,0.543,11.254		c0.975,1.039,5.24,0.678,7.592,0.678c2.168,0,6.52,0.495,7.594-0.678c0.699-0.764,0.543-4.293,0.543-6.644		c0-17.244,0-34.107,0-50.576c0-17.057,0-33.642,0-50.576c0-2.397,0.201-5.922-0.543-6.78c-1-1.152-8.305-0.681-9.627-0.678		c-1.34,0.003-3.771-0.23-5.018,0.135c-1.521,0.447-2.441,2.203-3.525,3.119c-0.168,0.142-0.24,0.263-0.406,0.407		c-3.139,2.733-7.129,5.242-11.662,6.644c-0.584,0.181-1.23,0.28-1.762,0.542c-1.369,0.679-1.441,1.252-1.084,2.848		C141.793,18.87,142.374,20.422,142.852,21.956z"));
    
    
    //Path path571 =  Drawable::parseSVGPath (String::fromUTF8 (BinaryData::_571_svg, BinaryData::_571_svgSize));
    
    addAndMakeVisible (&frequencyCaption);
    
    startTimer (30);
}


SpectrumViewer::~SpectrumViewer()
{
}


void SpectrumViewer::resized()
{
    gradientImage = Image (Image::RGB, jmax (1, getWidth()), jmax (1, getHeight() - heightForFrequencyCaption), false);
    createGradientImage();

    frequencyCaption.setBounds (0, getHeight() - heightForFrequencyCaption,
                                 getWidth(), heightForFrequencyCaption);
}


void SpectrumViewer::paint(Graphics& g)
{
    const int w = getWidth();
    const int h = getHeight() - heightForFrequencyCaption;
    
    g.setColour (Colours::black);
    g.fillRect(0, 0, w, h);
    
    // TEMP
    g.setColour (Colours::black.brighter(0.125));
    g.fillPath (path571, RectanglePlacement (RectanglePlacement::centred)
                .getTransformToFit (path571.getBounds(), getLocalBounds().toFloat()));
//    g.setColour (Colours::green);
//    float lineThickness2 = 2.0f;
//    g.strokePath (path571, PathStrokeType(lineThickness2), RectanglePlacement (RectanglePlacement::centred)
//                  .getTransformToFit (path571.getBounds(), getLocalBounds().toFloat()));
    
    
    // Draw the vertical lines
    // -----------------------
    g.setColour (Colours::darkgreen.darker().darker());
    
    for (int i = 0; i < numberOfFrequenciesToPlot; ++i)
    {
        const double proportion = frequenciesToPlot[i] / (sampleRate * 0.5);
        int xPos = logTransformInRange0to1 (proportion) * getWidth();
        g.drawVerticalLine(xPos, 0.0f, getHeight());
    }
    
    
    // Draw the actual result from the FFT
    // -----------------------------------
    const int numBins = fftMagnitudeBuffer.getSize();
    const float* data = fftMagnitudeBuffer.getData();
    
    // NOTE TO DAVE96: The jlimit is not needed. Puts the load off the CPU by 1-2%.
    // Original line:      float y2, y1 = jlimit (0.0f, 1.0f, float (1 + (drow::toDecibels (data[0]) / 100.0f)));
    float x = 0;
    float y = 0;
    
    // The path which will be the border of the filled area.
    Path spectrumPath;
    // Add the top left point.
    // Only values > 0 are passed to drow::toDecibels().
    const float yInPercent = data[0]>0 ? float (1 + (drow::toDecibels (data[0]) / 100.0f)) : -0.01;
    y = h - h * yInPercent;
    // No coordinate should be NaN
    jassert (x == x && y == y);
    spectrumPath.startNewSubPath(x, y);
    
    for (int i = 1; i < numBins; ++i)
    {
        x = logTransformInRange0to1 ((float)i / numBins) * w;
        // Only values > 0 are passed to drow::toDecibels().
        const float yInPercent = data[i]>0 ? float (1 + (drow::toDecibels (data[i]) / 100.0f)) : -0.01;
        y = h - h * yInPercent;
        
        spectrumPath.lineTo(x, y);
    }
    
    g.setColour (Colours::green);
    float lineThickness = 0.75f;
    g.strokePath (spectrumPath, PathStrokeType(lineThickness));
    
    // Remark: Using g.drawVerticalLine - which is told to be much more efficient for the renderer -
    // on every bin position instead of using a Path improved the overall performance of this
    // spectrum analyser by only 5%. (I profiled it)
    
    // Bottom right point.
    spectrumPath.lineTo(x, getHeight());
    // Bottom left point.
    spectrumPath.lineTo(0, getHeight());
    spectrumPath.closeSubPath();
    
    // Fill the graph.
    const float opacity = 0.8f;
    g.setTiledImageFill(gradientImage, 0, 0, opacity);
    g.fillPath(spectrumPath);
    
    
    // Draw a vertical line at the mouse position
    // ------------------------------------------
    if (mouseMode)
    {
        g.setColour (Colours::lightgoldenrodyellow);
        g.drawVerticalLine(mouseXPosition -1, 0, getHeight());
        // Don't know why the -1 offset for the x position
        // is needed. (It is also needed if the drawing
        // would be placed directly on the component, i.e.
        // in the paint() function.)
        // Maybe because of rounding in the mouseMove function.
    }
    else
    {
        const double proportion = (double)detectedFrequency.getValue() / (sampleRate / 2.0);
        const int pitchXCoord = roundToInt (logTransformInRange0to1 (proportion) * getWidth());
        
        g.setColour (Colours::green);
        g.drawVerticalLine (pitchXCoord, 0.0f, (float) getHeight());
    }

}


//==============================================================================
void SpectrumViewer::setSampleRate (double newSampleRate)
{
    sampleRate = newSampleRate;
    frequencyCaption.setSampleRate (newSampleRate);
}


int SpectrumViewer::getHeightOfFrequencyCaption()
{
    return heightForFrequencyCaption;
}


Value & SpectrumViewer::getFrequencyToDisplay()
{
    return frequencyToDisplay;
}


void SpectrumViewer::timerCallback()
{
    // TODO: How compares the CPU usage if we listen to repaintViewer
    //   instead of doing it here in the timerCallback?
    if (repaintViewer == true)
	{
        repaint(0, 0, getWidth(), getHeight() - heightForFrequencyCaption);
            // - heightForFrequencyCaption: We don't need to repaint the frequency caption.
        
        repaintViewer = false;
    }

	// Make the FFT levels fall.
    const int magnitudeBufferSize = fftMagnitudeBuffer.getSize();
	float* magnitudeBuffer = fftMagnitudeBuffer.getData();
    
	for (int i = 0; i < magnitudeBufferSize; i++)
		magnitudeBuffer[i] *= JUCE_LIVE_CONSTANT (0.707f);
}


void SpectrumViewer::valueChanged (Value &value)
{
    if (!mouseMode && value.refersToSameSourceAs(detectedFrequency))
    {
        frequencyToDisplay = detectedFrequency.getValue();
    }
}


void SpectrumViewer::createGradientImage()
{
    Graphics g (gradientImage);
    ColourGradient gradient (Colours::darkgreen.darker(), 0.0f, 0.8f * gradientImage.getHeight(), Colours::black, 0.0f, gradientImage.getHeight(), false);
    g.setGradientFill(gradient);
    g.fillAll();
}


void SpectrumViewer::mouseEnter (const MouseEvent &event)
{
    mouseMode = true;
}


void SpectrumViewer::mouseMove (const MouseEvent &event)
{
    mouseXPosition = event.getPosition().getX();
    
    const float normalizedXPosition = (mouseXPosition) / (float)getWidth();
    const float frequency = sampleRate / 2.0f * expTransformInRange0to1 (normalizedXPosition);
    frequencyToDisplay = (int)frequency;
}


void SpectrumViewer::mouseExit (const MouseEvent &event)
{
    mouseMode = false;
}



//==============================================================================
//==============================================================================
SpectrumViewer::FrequencyCaption::FrequencyCaption()
: sampleRate {44100.0}
{
    for (int i = 0; i < numberOfFrequenciesToPlot; ++i)
    {
        // Generate the frequencyString...
        const int frequency = frequenciesToPlot[i];
        String frequencyString;
        if (frequency % 1000 == 0)
        {
            frequencyString = String (frequency/1000) + "K";
        }
        else
        {
            frequencyString = String (frequency);
        }
        
        // ... and put it into a new Label.
        Label* frequencyLabel = new Label();
        frequencyLabel->setText(frequencyString, dontSendNotification);
        
        // Figuring out the width and height of the text and setting the Label accordingly.
        Font labelFont = Font(12.0f);
        frequencyLabel->setFont(labelFont);
        frequencyLabel->setColour (Label::textColourId, Colours::lightgoldenrodyellow);
        const int textWidth = labelFont.getStringWidth (frequencyLabel->getText());
        const int textHeight = labelFont.getHeight();
        frequencyLabel->setBorderSize (BorderSize<int>(0,1,0,1));
        frequencyLabel->setSize(textWidth + 2, textHeight);
        
        frequencyLabels.add(frequencyLabel);
        addAndMakeVisible(frequencyLabel);
    }
}

SpectrumViewer::FrequencyCaption::~FrequencyCaption()
{
}

void SpectrumViewer::FrequencyCaption::paint (Graphics& g)
{
    // Background
    // ----------
    g.fillAll (Colours::black); // Clear the background
    
    // Labels and lines
    // ----------------
    static float lineLength = 5.0f;
    g.setColour (Colours::lightgoldenrodyellow);
    
    for (int i = numberOfFrequenciesToPlot - 1; i >= 0; --i)
    {
        // Figure out the line position...
        const double proportion = frequenciesToPlot[i] / (sampleRate * 0.5);
        int xPosOfLine = logTransformInRange0to1 (proportion) * getWidth();
        
        // ...and the label position.
        const int widthOfLabel = frequencyLabels[i]->getWidth();
        frequencyLabels[i]->setTopLeftPosition(xPosOfLine - widthOfLabel / 2, lineLength);
        
        // Do labels overlap? Hide if neccessary
        frequencyLabels[i]->setVisible (true);
        for (int j = i+1; j < numberOfFrequenciesToPlot; ++j)
        {
            if (frequencyLabels[j]->isVisible()
                && frequencyLabels[j]->getX() <= frequencyLabels[i]->getX() + frequencyLabels[i]->getWidth())
            {
                frequencyLabels[i]->setVisible(false);
                break;
            }
        }
        // Only show the 20K label if it isn't truncated by the border of the whole component.
        if (i == numberOfFrequenciesToPlot - 1)
        {
            if (frequencyLabels[i]->getX() + frequencyLabels[i]->getWidth() > getWidth())
            {
                frequencyLabels[i]->setVisible(false);
            }
        }
        
        if (frequencyLabels[i]->isVisible())
        {
            g.drawVerticalLine(xPosOfLine, 0.0f, lineLength);
        }
    }
}

void SpectrumViewer::FrequencyCaption::resized()
{
}

void SpectrumViewer::FrequencyCaption::setSampleRate (double newSampleRate)
{
    sampleRate = newSampleRate;
}

#endif // JUCE_MAC || JUCE_IOS || DROWAUDIO_USE_FFTREAL
