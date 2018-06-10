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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "NewComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
NewComponent::NewComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..

    //[/Constructor_pre]

    startButton.reset (new TextButton ("startButton"));
    addAndMakeVisible (startButton.get());
    startButton->setTooltip (TRANS("Start"));
    startButton->setButtonText (TRANS("Start"));
    startButton->addListener (this);
    startButton->setColour (TextButton::buttonColourId, Colour (0xff540000));

    startButton->setBounds (8, 112, 80, 24);

    stopButton.reset (new TextButton ("stopButton"));
    addAndMakeVisible (stopButton.get());
    stopButton->setButtonText (TRANS("Reset"));
    stopButton->addListener (this);
    stopButton->setColour (TextButton::buttonColourId, Colour (0xff540000));

    stopButton->setBounds (8, 144, 80, 24);

    label.reset (new Label ("infoView",
                            CharPointer_UTF8 ("TAudioPlayer by Tarcan G\xc3\xbcl")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.50f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (0, 8, 152, 24);

    chooseButton.reset (new TextButton ("chooseButton"));
    addAndMakeVisible (chooseButton.get());
    chooseButton->setButtonText (TRANS("Pick"));
    chooseButton->addListener (this);
    chooseButton->setColour (TextButton::buttonColourId, Colour (0xff540000));

    chooseButton->setBounds (8, 80, 80, 24);

    filePrinter.reset (new Label ("filePrinter",
                                  TRANS("No file chosen")));
    addAndMakeVisible (filePrinter.get());
    filePrinter->setFont (Font ("DokChampa", 15.50f, Font::plain).withTypefaceStyle ("Regular"));
    filePrinter->setJustificationType (Justification::centredLeft);
    filePrinter->setEditable (false, false, false);
    filePrinter->setColour (TextEditor::textColourId, Colours::black);
    filePrinter->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    filePrinter->setBounds (8, 48, 280, 24);

    timeSlider.reset (new Slider ("new slider"));
    addAndMakeVisible (timeSlider.get());
    timeSlider->setRange (0, 1, 0);
    timeSlider->setSliderStyle (Slider::LinearHorizontal);
    timeSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    timeSlider->setColour (Slider::backgroundColourId, Colour (0xff723131));
    timeSlider->setColour (Slider::thumbColourId, Colour (0xff540000));
    timeSlider->addListener (this);

    timeSlider->setBounds (8, 168, 280, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (300, 200);


    //[Constructor] You can add your own custom stuff here..

	state = STOPPED;
	fileUploaded = false;
	formatManager.registerBasicFormats();
	setAudioChannels(0, 2);
	transportSource.addChangeListener(this);
	startButton->setEnabled(false);
	stopButton->setEnabled(false);
	startTimer(50);
    //[/Constructor]
}

NewComponent::~NewComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    startButton = nullptr;
    stopButton = nullptr;
    label = nullptr;
    chooseButton = nullptr;
    filePrinter = nullptr;
    timeSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void NewComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffe0441e));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void NewComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..

    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void NewComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == startButton.get())
    {
        //[UserButtonCode_startButton] -- add your button handler code here..
		if (state == PAUSED || state == STOPPED)
		{
			changeState(STARTING);
		}
		else if (state == PLAYING)
		{
			changeState(PAUSING);
		}
        //[/UserButtonCode_startButton]
    }
    else if (buttonThatWasClicked == stopButton.get())
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
		if (state == PAUSED)
			changeState(STOPPED);
		else
			changeState(STOPPING);

		timeSlider->setValue(0.0);
        //[/UserButtonCode_stopButton]
    }
    else if (buttonThatWasClicked == chooseButton.get())
    {
        //[UserButtonCode_chooseButton] -- add your button handler code here..
		FileChooser chooser("Choose one for me",
			File::nonexistent,
			"*.wav; *.mp3");                                        // [7]
		if (chooser.browseForFileToOpen())                                    // [8]
		{
			File file = chooser.getResult();                                  // [9]
			AudioFormatReader* reader = formatManager.createReaderFor(file);
			fileUploaded = true;
			filePrinter->setText(file.getFileName().substring(0,file.getFileName().length() - 4), dontSendNotification);
			// [10]
			if (reader != nullptr) {
				std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true)); // [11]
				transportSource.setSource(newSource.get(),0, nullptr, reader->sampleRate);
				changeState(STARTING);// [12]
				startButton->setEnabled(true);                                                      // [13]
				readerSource.reset(newSource.release());
			}
		}
        //[/UserButtonCode_chooseButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void NewComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == timeSlider.get())
    {
        //[UserSliderCode_timeSlider] -- add your slider handling code here..
		transportSource.setPosition(transportSource.getLengthInSeconds()*timeSlider->getValue());
        //[/UserSliderCode_timeSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void NewComponent::changeState(AudioState newState)
{

	if (state != newState)
	{
		state = newState;
		switch (state)
		{
		case STOPPED:
			startButton->setButtonText("Start");
			startButton->setEnabled(true);
			stopButton->setEnabled(false);
			transportSource.setPosition(0.0);
			break;
		case PLAYING:
			startButton->setButtonText("Pause");
			startButton->setEnabled(true);
			stopButton->setEnabled(true);
			break;
		case STARTING:
			startButton->setEnabled(false);
			stopButton->setEnabled(true);
			transportSource.start();// [4]
			break;
		case PAUSED:
			startButton->setButtonText("Resume");
			break;
		case PAUSING:

			transportSource.stop();
			break;
		case STOPPING:                          // [6]
			transportSource.stop();
			break;
		}
	}
}

void NewComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &transportSource)
	{
		if (transportSource.isPlaying())
			changeState(PLAYING);
		else if (state == STOPPING)
			changeState(STOPPED);
		else if (state == PAUSING)
			changeState(PAUSED);
		else if (transportSource.hasStreamFinished())
			changeState(STOPPED);
	}
}
void NewComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void NewComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{

	//bufferToFill.clearActiveBufferRegion();
	if (readerSource.get() == nullptr)
	{
		bufferToFill.clearActiveBufferRegion();
		return;
	}
	transportSource.getNextAudioBlock(bufferToFill);

	//bufferToFill.clearActiveBufferRegion();
}

void NewComponent::releaseResources()
{
	// This will be called when the audio device stops, or when it is being
	// restarted due to a setting change.
	//transportSource.releaseResources();

	// For more details, see the help for AudioProcessor::releaseResources()
}

void NewComponent::timerCallback() 
{
	if (transportSource.isPlaying()) 
	{	
		timeSlider->setValue(transportSource.getCurrentPosition() / transportSource.getLengthInSeconds());
	}
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="NewComponent" componentName=""
                 parentClasses="public AudioAppComponent, public ChangeListener, public Timer"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="300"
                 initialHeight="200">
  <BACKGROUND backgroundColour="ffe0441e"/>
  <TEXTBUTTON name="startButton" id="f5dc5fb222139b7b" memberName="startButton"
              virtualName="" explicitFocusOrder="0" pos="8 112 80 24" tooltip="Start"
              bgColOff="ff540000" buttonText="Start" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="stopButton" id="ec7646f125d52077" memberName="stopButton"
              virtualName="" explicitFocusOrder="0" pos="8 144 80 24" bgColOff="ff540000"
              buttonText="Reset" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="infoView" id="5a59b49b504f3d14" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 8 152 24" edTextCol="ff000000"
         edBkgCol="0" labelText="TAudioPlayer by Tarcan G&#252;l" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.50000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="chooseButton" id="6483c6aa29204653" memberName="chooseButton"
              virtualName="" explicitFocusOrder="0" pos="8 80 80 24" bgColOff="ff540000"
              buttonText="Pick" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="filePrinter" id="7c9d4da9870d2181" memberName="filePrinter"
         virtualName="" explicitFocusOrder="0" pos="8 48 280 24" edTextCol="ff000000"
         edBkgCol="0" labelText="No file chosen" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="DokChampa"
         fontsize="15.50000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="688bb890cebdfa5b" memberName="timeSlider"
          virtualName="" explicitFocusOrder="0" pos="8 168 280 24" bkgcol="ff723131"
          thumbcol="ff540000" min="0.00000000000000000000" max="1.00000000000000000000"
          int="0.00000000000000000000" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
