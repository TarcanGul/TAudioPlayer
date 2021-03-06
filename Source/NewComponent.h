/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class NewComponent  : public AudioAppComponent,
                      public ChangeListener,
                      public Timer,
                      public Button::Listener,
                      public Slider::Listener
{
public:
    //==============================================================================
    NewComponent ();
    ~NewComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.


	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	void changeListenerCallback(ChangeBroadcaster* source);
	void timerCallback() override;

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* _6000x4000_jpeg_3f9ff68960114beb8e20d969d6c6388b_jpg;
    static const int _6000x4000_jpeg_3f9ff68960114beb8e20d969d6c6388b_jpgSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	enum  AudioState
	{
		STOPPING, PLAYING, STARTING, STOPPED, PAUSED, PAUSING
	};
	AudioState state;
	void changeState(AudioState newState);
	AudioFormatManager formatManager;
	std::unique_ptr<AudioFormatReaderSource> readerSource;
	AudioTransportSource transportSource;
	bool fileUploaded;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> startButton;
    std::unique_ptr<TextButton> stopButton;
    std::unique_ptr<Label> label;
    std::unique_ptr<TextButton> chooseButton;
    std::unique_ptr<Label> filePrinter;
    std::unique_ptr<Slider> timeSlider;
    Image cachedImage__6000x4000_jpeg_3f9ff68960114beb8e20d969d6c6388b_jpg_1;
    Image cachedImage__6000x4000_jpeg_3f9ff68960114beb8e20d969d6c6388b_jpg_2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
