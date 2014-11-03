#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "portaudio.h"
#include "sndfile.h"
#include <time.h>

#include <QMouseEvent>

const QString MainWindow::Mute(tr("Mute"));
const QString MainWindow::Play(tr("Play"));
const QString MainWindow::Pause(tr("Pause"));
const QString MainWindow::Metronome(tr("Metronome"));

Audio_file click;
Audio_file piano_sound;




/*********************************************************/
int audio_callback(const void *inputBuffer, void *outputBuffer,
 		unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo,
 		PaStreamCallbackFlags statusFlags,
 		void *userData){

	MainWindow *wdg = (MainWindow*)userData;
 	float *in = (float*) inputBuffer;
 	float	*out = (float*) outputBuffer;
 	//float* metronome_sample = (float*)userData;
 	unsigned long i;
 	//float max = 0;
 	wdg->processAudio(in, framesPerBuffer);

 	if (wdg->isPlay()){
 		if(wdg->isMetronome()){
 			if (wdg->isMute()){		//metronome sound only
 				for( i = 0; i< framesPerBuffer; i++){
 					if(wdg->isPress()){
 						if(click.data_frame != click.end_frame && wdg->isWait() == false){
 							*out++ = (*click.data_frame++)+(*piano_sound.data_frame++)  ;/* sine;  left channel*/
 							if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 							*out++ = (*click.data_frame++)+(*piano_sound.data_frame++) ;/* sine;  right channel*/
 							if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 							if(click.data_frame == click.end_frame){
 								wdg->setEndtime((double)(clock()+ 60./wdg->getTempo()* CLOCKS_PER_SEC)-(click.num_frame*(CLOCKS_PER_SEC/44100.)));
 							}
 						}else{
                            //BPM = ui->doubleSpinBox_set_tempo->value();
 							wdg->setWait(true);
 							if(clock()<wdg->getEndtime()){
 								*out++ = (*piano_sound.data_frame++);
 								if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 								*out++ = (*piano_sound.data_frame++);
 								if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 							}else{
 								wdg->setWait(false);
 								click.data_frame = click.start_frame;
 							}
 						}
 					}else{
 						if(click.data_frame != click.end_frame && wdg->isWait() == false){
 							*out++ = (*click.data_frame++)  ;/* sine;  left channel*/
 							*out++ = (*click.data_frame++) ;/* sine;  right channel*/
 							if(click.data_frame == click.end_frame){
 								wdg->setEndtime((double)(clock()+ 60./wdg->getTempo()* CLOCKS_PER_SEC)-(click.num_frame*(CLOCKS_PER_SEC/44100.)));
 							}
 						}else{
                            //BPM = ui->doubleSpinBox_set_tempo->value();
 							wdg->setWait(true);
 					 		if(clock()<wdg->getEndtime()){
 					 			*out++ = (float)NULL;
 					 			*out++ = (float)NULL;
 					 		}else{
 					 			wdg->setWait(false);
 					 			click.data_frame = click.start_frame;
 					 		}
 						}
 					}
 				}
 			}else{		//metronome and input
 				for( i = 0; i< framesPerBuffer; i++){
 					if(wdg->isPress()){
 						if(click.data_frame != click.end_frame && wdg->isWait() == false){
 							*out++ = (*in++)+(*click.data_frame++)+(*piano_sound.data_frame++)  ;/* sine;  left channel*/
 							if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 							*out++ = (*in++)+(*click.data_frame++)+(*piano_sound.data_frame++) ;/* sine;  right channel*/
 							if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 							if(click.data_frame == click.end_frame){
 								wdg->setEndtime((double)(clock()+ 60./wdg->getTempo()* CLOCKS_PER_SEC)-(click.num_frame*(CLOCKS_PER_SEC/44100.)));
 							}
 						}else{
                            //BPM = ui->doubleSpinBox_set_tempo->value();
 							wdg->setWait(true);
 							if(clock()<wdg->getEndtime()){
 								*out++ = (*in++)+(*piano_sound.data_frame++);
 								if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 								*out++ = (*in++)+(*piano_sound.data_frame++);
 								if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 							}else{
 								wdg->setWait(false);
 								click.data_frame = click.start_frame;
 							}
 						}

 					}else{
 					if(click.data_frame != click.end_frame && wdg->isWait() == false){
 						*out++ = (*in++)+(*click.data_frame++)  ;/* sine;  left channel*/
 						*out++ = (*in++)+(*click.data_frame++) ;/* sine;  right channel*/
 						if(click.data_frame == click.end_frame){
 							wdg->setEndtime((double)(clock()+ 60./wdg->getTempo()* CLOCKS_PER_SEC)-(click.num_frame*(CLOCKS_PER_SEC/44100.)));
 						}
 					}else{
                        //BPM = ui->doubleSpinBox_set_tempo->value();
 						wdg->setWait(true);
 						if(clock()<wdg->getEndtime()){
 							*out++ = *in++;
 							*out++ = *in++;

 						}else{
 							wdg->setWait(false);
 							click.data_frame = click.start_frame;
 						}
 					}
 					}
 				}
 			}
 		}else{
 			if (wdg->isMute()){
 				for( i = 0; i< framesPerBuffer; i++){
 					if(wdg->isPress()){
 						*out++ =  *piano_sound.data_frame++ ;/* sine;  left channel*/
 						if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 						*out++ =  *piano_sound.data_frame++ ;/* sine;  left channel*/
 						if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 					}else{
 						*out++ =  (float)NULL ;/* sine;  left channel*/
 						*out++ =  (float)NULL ;/* sine;  left channel*/
 					}
 				}
 			}else{
 				for( i = 0; i< framesPerBuffer; i++){
 					if(wdg->isPress()){
 						*out++ =  (*piano_sound.data_frame++)+(*in++) ;/* sine;  left channel*/
 						if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 						*out++ =  (*piano_sound.data_frame++)+(*in++) ;/* sine;  left channel*/
 						if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 					}else{
 						*out++ = *in++ ;/* sine;  left channel*/
 						*out++ = *in++ ;/* sine;  right channel*/
 					}
 				}
 			}
 		}
 	}else{
 		if (wdg->isMute()){
 			for( i = 0; i< framesPerBuffer; i++){
 				if(wdg->isPress()){

 						*out++ =  *piano_sound.data_frame++ ;/* sine;  left channel*/
 						if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 						*out++ =  *piano_sound.data_frame++ ;/* sine;  left channel*/
 						if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}

 				}else{
 					*out++ =  (float)NULL ;/* sine;  left channel*/
 					*out++ =  (float)NULL ;/* sine;  left channel*/
 				}
 			}

 		}else{
 			for( i = 0; i< framesPerBuffer; i++){
 				if(wdg->isPress()){
 						*out++ =  (*piano_sound.data_frame++)+(*in++) ;/* sine;  left channel*/
 						if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 						*out++ =  (*piano_sound.data_frame++)+(*in++) ;/* sine;  left channel*/
 						if(piano_sound.data_frame==piano_sound.end_frame){wdg->setRelease(false);}
 				}else{
 					*out++ =  *in++ ;/* sine;  left channel*/
 					*out++ =  *in++ ;/* sine;  left channel*/
 				}
 			}
 		}
 	}

 	//wdg->refreshFrequencyMonitor(in, framesPerBuffer);
 	return paContinue;
 }


Audio_file read_wav(char* filename)
{
    //filename should contain the path to the .wav file.
    //For now, let's assume that the file contains 1-channel, 16-bit audio data, sampled at 48000Hz.
    //This function allocates an array of shorts for the audio data, and then returns a pointer to it.

    SF_INFO sf_info;
    //my_sf_info.format = 0;
    SNDFILE* sndfile = sf_open(filename, SFM_READ, &sf_info);

    if (NULL == sndfile)
    {
        printf(sf_strerror(sndfile));
    }

    // Check channels - mono
//    if (sf_info.channels != 1) {
//        //fprintf(stderr, "Wrong number of channels\n");
//        //sf_close(metronome_sndfile);

//    }
    Audio_file data;
    data.data_frame = (float*)malloc(sf_info.frames * sf_info.channels * sizeof(float)); // TODO: is this correct?

    sf_count_t num_frames_read = sf_readf_float(sndfile, data.data_frame, sf_info.frames); // request all the frames
    data.num_frame = num_frames_read;
    data.start_frame = &data.data_frame[0];
    data.end_frame = &data.data_frame[data.num_frame];
    sf_close(sndfile);

    return data;
}

//######################### exernal include !! ######################///

BackgroundColorSetter::BackgroundColorSetter(QWidget *parent): QWidget(parent){
	this->setStyleSheet("background-color: rgb(0,0,0);");
}
void BackgroundColorSetter::paintEvent(QPaintEvent * /*event*/ )
{
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.drawRect(0,0,100,30);
    painter.fillRect(0,0,20,15,Qt::green);
    painter.fillRect(20,0,20,15,Qt::yellow);
    painter.fillRect(40,0,20,15,Qt::cyan);
    painter.fillRect(60,0,20,15,Qt::red);
    painter.fillRect(80,0,20,15,Qt::magenta);

    painter.fillRect(0,15,20,15,Qt::gray);
    painter.fillRect(20,15,20,15,Qt::yellow);
    painter.fillRect(40,15,20,15,Qt::blue);
    painter.fillRect(60,15,20,15,Qt::black);
    painter.fillRect(80,15,20,15,Qt::white);

}
void BackgroundColorSetter::mousePressEvent(QMouseEvent *event){

	QPoint point;
	point = event->pos();

}
//########################################################################33


//########################################################################33


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,m_num_channels(2)
	,m_frame_block(2048)
	,m_sampling_rate(44100)
	,m_mute(1)
	,m_play(0)
	,m_metronome(0)
	,m_metronomeWait(0)
	,m_pianoPress(0)
	,tempo(90)

	,ampMonitor(0)
	,frequencyMonitor(0)
	,inputPlotterMonitor(0)
	,pianoRoll(0)
	,history_dialog(0)
	,bgSetter(0)
	,ratio(0)
	,detectedFrequency(0)
	,freqCompare_dialog(0)


{
    ui->setupUi(this);
	//this->setStyleSheet("background-color: rgb(255,255,105);");

	QString myWindowTitle = "Masing";
	setWindowTitle(myWindowTitle);
	setFixedSize(740, 450);
	initializeProgram();
}

MainWindow::~MainWindow(){}

void MainWindow::initializeProgram(){
	pa_init();
	createUI();
	metronome_init();
	loadSoundFile();
	pa_start();


}

void MainWindow::closeEvent(QCloseEvent *event)
 {
	pa_stop();
	pa_term();
    QMainWindow::closeEvent(event);
 }


void MainWindow::createUI(){

	QFont fp( "Arial", 10, QFont::Bold);

	m_muteButton = new QPushButton();
	m_muteButton->setText(Mute);
	//m_muteButton->setStyleSheet("* { background-color: rgb(102,255,255) }");
	m_muteButton->setFont(fp);
	connect(m_muteButton, SIGNAL(clicked()), SLOT(toggleMute()));
    ui->muteLayout->addWidget(m_muteButton);

	m_playButton = new QPushButton();
	m_playButton->setText(Play);
	//m_playButton->setStyleSheet("* { background-color: rgb(102,255,255) }");
	m_playButton->setFont(fp);
	connect(m_playButton, SIGNAL(clicked()), SLOT(play()));
    ui->mainControllLayout->addWidget(m_playButton);

	m_pauseButton = new QPushButton();
	m_pauseButton->setText(Pause);
	//m_pauseButton->setStyleSheet("* { background-color: rgb(102,255,255) }");
	m_pauseButton->setFont(fp);
	connect(m_pauseButton, SIGNAL(clicked()), SLOT(pause()));
    ui->mainControllLayout->addWidget(m_pauseButton);

	m_metronomeButton = new QPushButton();
	m_metronomeButton->setText(Metronome);
	//m_metronomeButton->setStyleSheet("* { background-color: rgb(102,255,255) }");
	m_metronomeButton->setFont(fp);
	connect(m_metronomeButton, SIGNAL(clicked()), SLOT(metronome()));
    ui->mainControllLayout->addWidget(m_metronomeButton);

	m_tempoSpinbox = new QSpinBox();
	m_tempoSpinbox->setRange(60,150);
	m_tempoSpinbox->setValue(90);
	m_tempoSpinbox->setFont(fp);
    ui->mainControllLayout->addWidget(m_tempoSpinbox);


	//AmplitudeMonitor
    ampMonitor = new AmplitudeMonitor();
    ui->amplitudeLayout->addWidget(ampMonitor);

	//Frequency Monitor
	frequencyMonitor = new FrequencyMonitor();
    ui->frequencyLayout->addWidget(frequencyMonitor);

	//inputPlotter Monitor
	inputPlotterMonitor = new InputWavePlotter();
	//inputPlotterMonitor->setStyleSheet("background-color: orange;");
    ui->inputPlotLayout->addWidget(inputPlotterMonitor);

	//Piano Roll
    pianoRoll = new Piano();
    connect(pianoRoll->piano_ui.pushButton_24, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_24, SIGNAL(released()),SLOT(keyRelease()));
    connect(pianoRoll->piano_ui.pushButton_25, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_26, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_27, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_28, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_29, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_30, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_31, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_32, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_33, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_34, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_35, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_36, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_37, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_38, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_39, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_40, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_41, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_42, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_43, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_44, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_45, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_46, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_47, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_48, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_49, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_50, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_51, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_52, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_53, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_54, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_55, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_56, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_57, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_58, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_59, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_60, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_61, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_62, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_63, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_64, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_65, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_66, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_67, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_68, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_69, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_70, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_71, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_72, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_73, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_74, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_75, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_76, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_77, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_78, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_79, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_80, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_81, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_82, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_83, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_84, SIGNAL(pressed()),SLOT(keyPress()));
    connect(pianoRoll->piano_ui.pushButton_85, SIGNAL(pressed()),SLOT(keyPress()));

    ui->pianoRollLayout->addWidget(pianoRoll);
/*
	//test
	testButton = new QPushButton();
	connect(testButton, SIGNAL(pressed()),SLOT(pianoAction()));
    ui->testLayout->addWidget(testButton);*/
	m_frequencyLCDbox = new QLCDNumber(6,this);

    ui->frequencyLCDLayout->addWidget(m_frequencyLCDbox);

	m_pianoFrequencyLCDbox = new QLCDNumber(6,this);
    ui->autoLCDLayout->addWidget(m_pianoFrequencyLCDbox);

	m_noteNameLabel = new QLabel();
	QFont f( "Arial", 40, QFont::Bold);
	m_noteNameLabel->setFont(f);
	m_noteNameLabel->setText(" - ");
    ui->noteNameLayout->addWidget(m_noteNameLabel);

	history_button = new QPushButton();
	history_button->setText("History");
	history_button->setFont(fp);
	//history_button->setStyleSheet("* { background-color: rgb(102,255,255) }");
	connect(history_button, SIGNAL(clicked()), SLOT(openHistory()));
    ui->toolsLayout->addWidget(history_button);

	history_dialog = new History();

	my_freqLabel = new QLabel();
	my_freqLabel->setText("Your Frequency (Hz.)");
	my_freqLabel->setFont(fp);
    ui->yourFreqLabelLayout->addWidget(my_freqLabel);

	piano_freqLabel = new QLabel();
	piano_freqLabel->setText("Piano Freqeuncy (Hz.)");
	piano_freqLabel->setFont(fp);
    ui->pianoFreqLabelLayout->addWidget(piano_freqLabel);


	bgSetter = new BackgroundColorSetter();
    //ui->backgroundLayout->addWidget(bgSetter);

	freqCompare_dialog = new FrequencyCompare();

	m_noteCorrectPercentLabel = new QLabel();
	m_noteCorrectPercentLabel->setFont(f);
	m_noteCorrectPercentLabel->setNum(00.0);
    ui->noteCorrectPercentLabelLayout->addWidget(m_noteCorrectPercentLabel);

/*
	compare_button = new QPushButton();
	compare_button->setText("Compare Frequency");
	compare_button->setFont(fp);
	connect(compare_button, SIGNAL(clicked()), SLOT(openCompareFrequency()));
    ui->toolsLayout->addWidget(compare_button);


	freq_comareLCD = new QLCDNumber();
    ui->testLayout->addWidget(freq_comareLCD);*/
}


void MainWindow::pa_init(){
	// Initialize PortAudio

		PaError err = Pa_Initialize();
		if( err != paNoError ) {
			qFatal("PortAudio: Initialization error");
			//return 1;
		}

		/* set output */
	    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
		outputParameters.channelCount = m_num_channels; /*stereo output */
		outputParameters.sampleFormat = paFloat32; /*32 bit float output */
		outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
		outputParameters.hostApiSpecificStreamInfo = NULL; /*no specification info */


		/* set input */
	    inputParameters.device = Pa_GetDefaultInputDevice(); /* default output device */
        inputParameters.channelCount = m_num_channels; /*stereo output */
		inputParameters.sampleFormat = paFloat32; /*32 bit float output */
		inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
		inputParameters.hostApiSpecificStreamInfo = NULL; /*no specification info */

		err = Pa_OpenStream( /* open the PaStream object */
				&audioStream, 		/* portaudio stream object */
				&inputParameters, 	/*provide input parameter */
				//NULL,
				&outputParameters, 	/* provide output parameter*/
				m_sampling_rate, 		/* set sampling rate */
				m_frame_block, 	/* set frames per buffer */
				paClipOff, 			/* set no clip*/
				audio_callback, 	/* callback function address*/
				this	/* provide no data for callback */
		);
}

void MainWindow::pa_start(){
	Pa_StartStream(audioStream);  /* start the callback mechanism */
}

void MainWindow::pa_stop(){
	Pa_StopStream( audioStream );
}

void MainWindow::pa_term(){
	Pa_StopStream( audioStream );
	Pa_CloseStream( audioStream );
	Pa_Terminate();
}

void MainWindow::processAudio( float *data, int size)
{
        ampMonitor->setAmpLevel(data,size);
    	frequencyMonitor->setFrequency(data,size);
    	inputPlotterMonitor->setFrequency(data,size);
        /*autocorrelation->find_pitch_offset(data,size);
        detectedFrequency = autocorrelation->getDetectedFrequency();
        if(ampMonitor->getAmp() > 0.02 ){
    		freqCompare_dialog->setCurrentDetecetedFreq(detectedFrequency);
    		m_frequencyLCDbox->display(detectedFrequency);
    	}
    	ratio = freqCompare_dialog->getRatio();
        */refreshMonitor();
    	refreshCompareFrequencyMonitor();
    	doHistory();

}

void MainWindow::refreshMonitor(){
	ampMonitor->update();
	frequencyMonitor->update();
	inputPlotterMonitor->update();
	/*if(ampMonitor->getAmp() > 0.3){
		m_frequencyLCDbox->display((double)frequencyMonitor->getPitch());
	}*/

}


void MainWindow::refreshCompareFrequencyMonitor(){
	m_noteCorrectPercentLabel->setNum(history_dialog->getTotalPercent());
	/*detectedFrequency = autocorrelation->getDetectedFrequency();
	if(ampMonitor->getAmp() > 0.02 ){
		freqCompare_dialog->setCurrentDetecetedFreq(detectedFrequency);
		m_frequencyLCDbox->display(detectedFrequency);
	}
	ratio = freqCompare_dialog->getRatio();*/
	//freq_comareLCD->display(ratio);
}

void MainWindow::doHistory(){
	history_dialog->setRatio(ratio);
	history_dialog->keepHistory(ampMonitor->getAmp(),detectedFrequency);
}
//metronome

void MainWindow::metronome_init(){
	//metronome_clk = read_wav((char*)"Sound/CLK_LOGIC1.wav");
    click = read_wav((char*)"../Sound/CLK_LOGIC1.wav");
	//piano_sound = read_wav("PianoSample/A1.wav");
	tempo = m_tempoSpinbox->value();
	m_metronome = false;

}

void MainWindow::loadSoundFile(){
	sound_C1	= read_wav((char*)"PianoSample/C1.wav");
	sound_Db1 	= read_wav((char*)"PianoSample/C#1.wav");
	sound_D1	= read_wav((char*)"PianoSample/D1.wav");
	sound_Eb1 	= read_wav((char*)"PianoSample/D#1.wav");
    sound_E1 	= read_wav((char*)"PianoSample/E1.wav");
    sound_F1	= read_wav((char*)"PianoSample/F1.wav");
    sound_Gb1	= read_wav((char*)"PianoSample/F#1.wav");
    sound_G1	= read_wav((char*)"PianoSample/G1.wav");
    sound_Ab1	= read_wav((char*)"PianoSample/G#1.wav");
    sound_A1	= read_wav((char*)"PianoSample/A1.wav");
    sound_Bb1	= read_wav((char*)"PianoSample/A#1.wav");
    sound_B1	= read_wav((char*)"PianoSample/B1.wav");
    sound_C2	= read_wav((char*)"PianoSample/C2.wav");
    sound_Db2	= read_wav((char*)"PianoSample/C#2.wav");
    sound_D2	= read_wav((char*)"PianoSample/D2.wav");
    sound_Eb2	= read_wav((char*)"PianoSample/D#2.wav");
    sound_E2	= read_wav((char*)"PianoSample/E2.wav");
    sound_F2	= read_wav((char*)"PianoSample/F2.wav");
    sound_Gb2	= read_wav((char*)"PianoSample/F#2.wav");
    sound_G2	= read_wav((char*)"PianoSample/G2.wav");
    sound_Ab2	= read_wav((char*)"PianoSample/G#2.wav");
    sound_A2	= read_wav((char*)"PianoSample/A2.wav");
    sound_Bb2	= read_wav((char*)"PianoSample/A#2.wav");
    sound_B2	= read_wav((char*)"PianoSample/B2.wav");
    sound_C3	= read_wav((char*)"PianoSample/C3.wav");
    sound_Db3	= read_wav((char*)"PianoSample/C#3.wav");
    sound_D3	= read_wav((char*)"PianoSample/D3.wav");
    sound_Eb3	= read_wav((char*)"PianoSample/D#3.wav");
    sound_E3	= read_wav((char*)"PianoSample/E3.wav");
    sound_F3 	= read_wav((char*)"PianoSample/F3.wav");
    sound_Gb3	= read_wav((char*)"PianoSample/F#3.wav");
    sound_G3	= read_wav((char*)"PianoSample/G3.wav");
    sound_Ab3	= read_wav((char*)"PianoSample/G#3.wav");
    sound_A3	= read_wav((char*)"PianoSample/A3.wav");
    sound_Bb3	= read_wav((char*)"PianoSample/A#3.wav");
    sound_B3	= read_wav((char*)"PianoSample/B3.wav");
    sound_C4	= read_wav((char*)"PianoSample/C4.wav");
    sound_Db4	= read_wav((char*)"PianoSample/C#4.wav");
    sound_D4	= read_wav((char*)"PianoSample/D4.wav");
    sound_Eb4	= read_wav((char*)"PianoSample/D#4.wav");
    sound_E4	= read_wav((char*)"PianoSample/E4.wav");
    sound_F4	= read_wav((char*)"PianoSample/F4.wav");
    sound_Gb4	= read_wav((char*)"PianoSample/F#4.wav");
    sound_G4	= read_wav((char*)"PianoSample/G4.wav");
    sound_Ab4	= read_wav((char*)"PianoSample/G#4.wav");
    sound_A4	= read_wav((char*)"PianoSample/A4.wav");
    sound_Bb4	= read_wav((char*)"PianoSample/A#4.wav");
    sound_B4	= read_wav((char*)"PianoSample/B4.wav");
    sound_C5	= read_wav((char*)"PianoSample/C5.wav");
    sound_Db5	= read_wav((char*)"PianoSample/C#5.wav");
    sound_D5	= read_wav((char*)"PianoSample/D5.wav");
    sound_Eb5	= read_wav((char*)"PianoSample/D#5.wav");
    sound_E5	= read_wav((char*)"PianoSample/E5.wav");
    sound_F5	= read_wav((char*)"PianoSample/F5.wav");
    sound_Gb5	= read_wav((char*)"PianoSample/F#5.wav");
    sound_G5	= read_wav((char*)"PianoSample/G5.wav");
    sound_Ab5	= read_wav((char*)"PianoSample/G#5.wav");
    sound_A5	= read_wav((char*)"PianoSample/A5.wav");
    sound_Bb5	= read_wav((char*)"PianoSample/A#5.wav");
    sound_B5	= read_wav((char*)"PianoSample/B#5.wav");
}



//slots#################################################
void MainWindow::toggleMute(){
	if(m_mute != true){
		m_mute = true;
	}else{
		m_mute = false;
	}

}

void MainWindow::play(){
	if(m_play != true){
		m_play = true;
	}
}

void MainWindow::pause(){
	if(m_play != false){
		m_play = false;
	}
}

void MainWindow::metronome(){
	if(m_metronome != true){
		m_metronome = true;
	}else{
		m_metronome = false;
	}
}


void MainWindow::keyPress(){
	m_pianoPress = false;
    if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_24){
		piano_sound = sound_C1;
		m_noteNameLabel->setText("C1");
		history_dialog->note_recieve(24,3087,C1,Db1);
		m_pianoFrequencyLCDbox->display(C1/100.);
		freqCompare_dialog->setCurrentNoteFreq(3087,C1,Db1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_25){
		piano_sound = sound_Db1;
		m_noteNameLabel->setText("C#1");
		history_dialog->note_recieve(25,C1,Db1,D1);
		m_pianoFrequencyLCDbox->display(Db1/100.);
		freqCompare_dialog->setCurrentNoteFreq(C1,Db1,D1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_26){
		m_noteNameLabel->setText("D1");
		piano_sound = sound_D1;
		history_dialog->note_recieve(26,Db1,D1,Eb1);
		m_pianoFrequencyLCDbox->display(D1/100.);
		freqCompare_dialog->setCurrentNoteFreq(Db1,D1,Eb1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_27){
		piano_sound = sound_Eb1;
		m_noteNameLabel->setText("D#1");
		history_dialog->note_recieve(27,D1,Eb1,E1);
		m_pianoFrequencyLCDbox->display(Eb1/100.);
		freqCompare_dialog->setCurrentNoteFreq(D1,Eb1,E1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_28){
		piano_sound = sound_E1;
		m_noteNameLabel->setText("E1");
		history_dialog->note_recieve(28,Eb1,E1,F1);
		m_pianoFrequencyLCDbox->display(E1/100.);
		freqCompare_dialog->setCurrentNoteFreq(Eb1,E1,F1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_29){
		piano_sound = sound_F1;
		m_noteNameLabel->setText("F1");
		history_dialog->note_recieve(29,E1,F1,Gb1);
		m_pianoFrequencyLCDbox->display(F1/100.);
		freqCompare_dialog->setCurrentNoteFreq(E1,F1,Gb1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_30){
		m_noteNameLabel->setText("F#1");
		piano_sound = sound_Gb1;
		history_dialog->note_recieve(30,F1,Gb1,G1);
		m_pianoFrequencyLCDbox->display(Gb1/100.);
		freqCompare_dialog->setCurrentNoteFreq(F1,Gb1,G1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_31){
		m_noteNameLabel->setText("G1");
		piano_sound = sound_G1;
		history_dialog->note_recieve(31,Gb1,G1,Ab1);
		m_pianoFrequencyLCDbox->display(G1/100.);
		freqCompare_dialog->setCurrentNoteFreq(Gb1,G1,Ab1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_32){
		m_noteNameLabel->setText("G#1");
		piano_sound = sound_Ab1;
		history_dialog->note_recieve(32,G1,Ab1,A1);
		m_pianoFrequencyLCDbox->display(Ab1/100.);
		freqCompare_dialog->setCurrentNoteFreq(G1,Ab1,A1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_33){
		m_noteNameLabel->setText("A1");
		piano_sound = sound_A1;
		history_dialog->note_recieve(33,Ab1,A1,Bb1);
		m_pianoFrequencyLCDbox->display(A1/100.);
		freqCompare_dialog->setCurrentNoteFreq(Ab1,A1,Bb1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_34){
		m_noteNameLabel->setText("A#1");
		piano_sound = sound_Bb1;
		history_dialog->note_recieve(34,A1,Bb1,B1);
		m_pianoFrequencyLCDbox->display(Bb1/100.);
		freqCompare_dialog->setCurrentNoteFreq(A1,Bb1,B1);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_35){
		m_noteNameLabel->setText("B1");
		piano_sound = sound_B1;
		history_dialog->note_recieve(35,Bb1,B1,C2);
		m_pianoFrequencyLCDbox->display(B1/100.);
		freqCompare_dialog->setCurrentNoteFreq(Bb1,B1,C2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_36){
		m_noteNameLabel->setText("C2");
		piano_sound = sound_C2;
		history_dialog->note_recieve(36,B1,C2,Db2);
		m_pianoFrequencyLCDbox->display(C2/100.);
		freqCompare_dialog->setCurrentNoteFreq(B1,C2,Db2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_37){
		m_noteNameLabel->setText("C#2");
		piano_sound = sound_Db2;
		history_dialog->note_recieve(37,C2,Db2,D2);
		m_pianoFrequencyLCDbox->display(Db2/100.);
		freqCompare_dialog->setCurrentNoteFreq(C2,Db2,D2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_38){
		m_noteNameLabel->setText("D2");
		piano_sound = sound_D2;
		history_dialog->note_recieve(38,Db2,D2,Eb2);
		m_pianoFrequencyLCDbox->display(D2/100.);
		freqCompare_dialog->setCurrentNoteFreq(Db2,D2,Eb2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_39){
		m_noteNameLabel->setText("D#2");
		piano_sound = sound_Eb2;
		history_dialog->note_recieve(39,D2,Eb2,E2);
		m_pianoFrequencyLCDbox->display(Eb2/100.);
		freqCompare_dialog->setCurrentNoteFreq(D2,Eb2,E2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_40){
		m_noteNameLabel->setText("E2");
		piano_sound = sound_E2;
		history_dialog->note_recieve(40,Eb2,E2,F2);
		m_pianoFrequencyLCDbox->display(E2/100.);
		freqCompare_dialog->setCurrentNoteFreq(Eb2,E2,F2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_41){
		m_noteNameLabel->setText("F2");
		piano_sound = sound_F2;
		history_dialog->note_recieve(41,E2,F2,Gb2);
		m_pianoFrequencyLCDbox->display(F2/100.);
		freqCompare_dialog->setCurrentNoteFreq(E2,F2,Gb2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_42){
		m_noteNameLabel->setText("F#2");
		piano_sound = sound_Gb2;
		history_dialog->note_recieve(42,F2,Gb2,G2);
		m_pianoFrequencyLCDbox->display(Gb2/100.);
		freqCompare_dialog->setCurrentNoteFreq(F2,Gb2,G2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_43){
		m_noteNameLabel->setText("G2");
		piano_sound = read_wav((char*)"PianoSample/G2.wav");
		history_dialog->note_recieve(43,Gb2,G2,Ab2);
		m_pianoFrequencyLCDbox->display(G2/100.);
		freqCompare_dialog->setCurrentNoteFreq(Gb2,G2,Ab2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_44){
		m_noteNameLabel->setText("G#2");
		piano_sound = sound_Ab2;
		history_dialog->note_recieve(44,G2,Ab2,A2);
		m_pianoFrequencyLCDbox->display(Ab2/100.);
		freqCompare_dialog->setCurrentNoteFreq(G2,Ab2,A2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_45){
		m_noteNameLabel->setText("A2");
		piano_sound = sound_A2;
		history_dialog->note_recieve(45,Ab2,A2,Bb2);
		m_pianoFrequencyLCDbox->display(A2/100.);
		freqCompare_dialog->setCurrentNoteFreq(Ab2,A2,Bb2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_46){
		m_noteNameLabel->setText("A#2");
		piano_sound = sound_Bb2;
		history_dialog->note_recieve(46,A2,Bb2,B2);
		m_pianoFrequencyLCDbox->display(Bb2/100.);
		freqCompare_dialog->setCurrentNoteFreq(A2,Bb2,B2);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_47){
		m_noteNameLabel->setText("B2");
		piano_sound = sound_B2;
		history_dialog->note_recieve(47,Bb2,B2,C3);
		m_pianoFrequencyLCDbox->display(B2/100.);
		freqCompare_dialog->setCurrentNoteFreq(Bb2,B2,C3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_48){
		m_noteNameLabel->setText("C3");
		piano_sound = sound_C3;
		history_dialog->note_recieve(48,B2,C3,Db3);
		m_pianoFrequencyLCDbox->display(C3/100.);
		freqCompare_dialog->setCurrentNoteFreq(B2,C3,Db3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_49){
		m_noteNameLabel->setText("C#3");
		piano_sound = sound_Db3;
		history_dialog->note_recieve(49,C3,Db3,D3);
		m_pianoFrequencyLCDbox->display(Db3/100.);
		freqCompare_dialog->setCurrentNoteFreq(C3,Db3,D3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_50){
		m_noteNameLabel->setText("D3");
		piano_sound = sound_D3;
		history_dialog->note_recieve(50,Db3,D3,Eb3);
		m_pianoFrequencyLCDbox->display(D3/100.);
		freqCompare_dialog->setCurrentNoteFreq(Db3,D3,Eb3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_51){
		m_noteNameLabel->setText("D#3");
		piano_sound = sound_Eb3;
		history_dialog->note_recieve(51,D3,Eb3,E3);
		m_pianoFrequencyLCDbox->display(Eb3/100.);
		freqCompare_dialog->setCurrentNoteFreq(D3,Eb3,E3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_52){
		m_noteNameLabel->setText("E3");
		piano_sound = sound_E3;
		history_dialog->note_recieve(52,Eb3,E3,F3);
		m_pianoFrequencyLCDbox->display(E3/100.);
		freqCompare_dialog->setCurrentNoteFreq(Eb3,E3,F3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_53){
		m_noteNameLabel->setText("F3");
		piano_sound = sound_F3;
		history_dialog->note_recieve(53,E3,F3,Gb3);
		m_pianoFrequencyLCDbox->display(F3/100.);
		freqCompare_dialog->setCurrentNoteFreq(E3,F3,Gb3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_54){
		m_noteNameLabel->setText("F#3");
		piano_sound = sound_Gb3;
		history_dialog->note_recieve(54,F3,Gb3,G3);
		m_pianoFrequencyLCDbox->display(Gb3/100.);
		freqCompare_dialog->setCurrentNoteFreq(F3,Gb3,G3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_55){
		m_noteNameLabel->setText("G3");
		piano_sound = sound_G3;
		history_dialog->note_recieve(55,Gb3,G3,Ab3);
		m_pianoFrequencyLCDbox->display(G3/100.);
		freqCompare_dialog->setCurrentNoteFreq(Gb3,G3,Ab3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_56){
		m_noteNameLabel->setText("G#3");
		piano_sound = sound_Ab3;
		history_dialog->note_recieve(56,G3,Ab3,A3);
		m_pianoFrequencyLCDbox->display(Ab3/100.);
		freqCompare_dialog->setCurrentNoteFreq(G3,Ab3,A3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_57){
		m_noteNameLabel->setText("A3");
		piano_sound = sound_A3;
		history_dialog->note_recieve(57,Ab3,A3,Bb3);
		m_pianoFrequencyLCDbox->display(A3/100.);
		freqCompare_dialog->setCurrentNoteFreq(Ab3,A3,Bb3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_58){
		m_noteNameLabel->setText("A#3");
		piano_sound = sound_Bb3;
		history_dialog->note_recieve(58,A3,Bb3,B3);
		m_pianoFrequencyLCDbox->display(Bb3/100.);
		freqCompare_dialog->setCurrentNoteFreq(A3,Bb3,B3);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_59){
		m_noteNameLabel->setText("B3");
		piano_sound = sound_B3;
		history_dialog->note_recieve(59,Bb3,B3,C4);
		m_pianoFrequencyLCDbox->display(B3/100.);
		freqCompare_dialog->setCurrentNoteFreq(Bb3,B3,C4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_60){
		m_noteNameLabel->setText("C4");
		piano_sound = sound_C4;
		history_dialog->note_recieve(60,B3,C4,Db4);
		m_pianoFrequencyLCDbox->display(C4/100.);
		freqCompare_dialog->setCurrentNoteFreq(B3,C4,Db4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_61){
		m_noteNameLabel->setText("C#4");
		piano_sound = sound_Db4;
		history_dialog->note_recieve(61,C4,Db4,D4);
		m_pianoFrequencyLCDbox->display(Db4/100.);
		freqCompare_dialog->setCurrentNoteFreq(C4,Db4,D4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_62){
		m_noteNameLabel->setText("D4");
		piano_sound = sound_D4;
		history_dialog->note_recieve(62,Db4,D4,Eb4);
		m_pianoFrequencyLCDbox->display(D4/100.);
		freqCompare_dialog->setCurrentNoteFreq(Db4,D4,Eb4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_63){
		m_noteNameLabel->setText("D#4");
		piano_sound = sound_Eb4;
		history_dialog->note_recieve(63,D4,Eb4,E4);
		m_pianoFrequencyLCDbox->display(Eb4/100.);
		freqCompare_dialog->setCurrentNoteFreq(D4,Eb4,E4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_64){
		m_noteNameLabel->setText("E4");
		piano_sound = sound_E4;
		history_dialog->note_recieve(64,Eb4,E4,F4);
		m_pianoFrequencyLCDbox->display(E4/100.);
		freqCompare_dialog->setCurrentNoteFreq(Eb4,E4,F4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_65){
		m_noteNameLabel->setText("F4");
		piano_sound = sound_F4;
		history_dialog->note_recieve(65,E4,F4,Gb4);
		m_pianoFrequencyLCDbox->display(F4/100.);
		freqCompare_dialog->setCurrentNoteFreq(E4,F4,Gb4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_66){
		m_noteNameLabel->setText("F#4");
		piano_sound = sound_Gb4;
		history_dialog->note_recieve(66,F4,Gb4,G4);
		m_pianoFrequencyLCDbox->display(Gb4/100.);
		freqCompare_dialog->setCurrentNoteFreq(F4,Gb4,G4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_67){
		m_noteNameLabel->setText("G4");
		piano_sound = sound_G4;
		history_dialog->note_recieve(67,Gb4,G4,Ab4);
		m_pianoFrequencyLCDbox->display(G4/100.);
		freqCompare_dialog->setCurrentNoteFreq(Gb4,G4,Ab4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_68){
		m_noteNameLabel->setText("G#4");
		piano_sound = sound_Ab4;
		history_dialog->note_recieve(68,G4,Ab4,A4);
		m_pianoFrequencyLCDbox->display(Ab4/100.);
		freqCompare_dialog->setCurrentNoteFreq(G4,Ab4,A4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_69){
		m_noteNameLabel->setText("A4");
		piano_sound = sound_A4;
		history_dialog->note_recieve(69,Ab4,A4,Bb4);
		m_pianoFrequencyLCDbox->display(A4/100.);
		freqCompare_dialog->setCurrentNoteFreq(Ab4,A4,Bb4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_70){
		m_noteNameLabel->setText("A#4");
		piano_sound = sound_Bb4;
		history_dialog->note_recieve(70,A4,Bb4,B4);
		m_pianoFrequencyLCDbox->display(Bb4/100.);
		freqCompare_dialog->setCurrentNoteFreq(A4,Bb4,B4);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_71){
		m_noteNameLabel->setText("B4");
		piano_sound = sound_B4;
		history_dialog->note_recieve(71,Bb4,B4,C5);
		m_pianoFrequencyLCDbox->display(B4/100.);
		freqCompare_dialog->setCurrentNoteFreq(Bb4,B4,C5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_72){
		m_noteNameLabel->setText("C5");
		piano_sound = sound_C5;
		history_dialog->note_recieve(72,B4,C5,Db5);
		m_pianoFrequencyLCDbox->display(C5/100.);
		freqCompare_dialog->setCurrentNoteFreq(B4,C5,Db5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_73){
		m_noteNameLabel->setText("C#5");
		piano_sound = sound_Db5;
		history_dialog->note_recieve(73,C5,Db5,D5);
		m_pianoFrequencyLCDbox->display(Db5/100.);
		freqCompare_dialog->setCurrentNoteFreq(C5,Db5,D5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_74){
		m_noteNameLabel->setText("D5");
		piano_sound = sound_D5;
		history_dialog->note_recieve(74,Db5,D5,Eb5);
		m_pianoFrequencyLCDbox->display(D5/100.);
		freqCompare_dialog->setCurrentNoteFreq(Db5,D5,Eb5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_75){
		m_noteNameLabel->setText("D#5");
		piano_sound = sound_Eb5;
		history_dialog->note_recieve(75,D5,Eb5,E5);
		m_pianoFrequencyLCDbox->display(Eb5/100.);
		freqCompare_dialog->setCurrentNoteFreq(D5,Eb5,E5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_76){
		m_noteNameLabel->setText("E5");
		piano_sound = sound_E5;
		history_dialog->note_recieve(76,Eb5,E5,F5);
		m_pianoFrequencyLCDbox->display(E5/100.);
		freqCompare_dialog->setCurrentNoteFreq(Eb5,E5,F5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_77){
		m_noteNameLabel->setText("F5");
		piano_sound = sound_F5;
		history_dialog->note_recieve(77,E5,F5,Gb5);
		m_pianoFrequencyLCDbox->display(F5/100.);
		freqCompare_dialog->setCurrentNoteFreq(E5,F5,Gb5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_78){
		m_noteNameLabel->setText("F#5");
		piano_sound = sound_Gb5;
		history_dialog->note_recieve(78,F5,Gb5,G5);
		m_pianoFrequencyLCDbox->display(Gb5/100.);
		freqCompare_dialog->setCurrentNoteFreq(F5,Gb5,G5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_79){
		m_noteNameLabel->setText("G5");
		piano_sound = sound_G5;
		history_dialog->note_recieve(79,Gb5,G5,Ab5);
		m_pianoFrequencyLCDbox->display(G5/100.);
		freqCompare_dialog->setCurrentNoteFreq(Gb5,G5,Ab5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_80){
		m_noteNameLabel->setText("G#5");
		piano_sound = sound_Ab5;
		history_dialog->note_recieve(80,G5,Ab5,A5);
		m_pianoFrequencyLCDbox->display(Ab5/100.);
		freqCompare_dialog->setCurrentNoteFreq(G5,Ab5,A5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_81){
		m_noteNameLabel->setText("A5");
		piano_sound = sound_A5;
		history_dialog->note_recieve(81,Ab5,A5,Bb5);
		m_pianoFrequencyLCDbox->display(A5/100.);
		freqCompare_dialog->setCurrentNoteFreq(Ab5,A5,Bb5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_82){
		m_noteNameLabel->setText("A#5");
		piano_sound = sound_Bb5;
		history_dialog->note_recieve(82,A5,Bb5,B5);
		m_pianoFrequencyLCDbox->display(Bb5/100.);
		freqCompare_dialog->setCurrentNoteFreq(A5,Bb5,B5);
    }if(MainWindow::sender() == pianoRoll->piano_ui.pushButton_83){
		m_noteNameLabel->setText("B5");
		piano_sound = sound_B5;
		history_dialog->note_recieve(83,Bb5,B5,104650);
		m_pianoFrequencyLCDbox->display(B5/100.);
		freqCompare_dialog->setCurrentNoteFreq(Bb5,B5,104650);
	}
	if(m_pianoPress != true){
		m_pianoPress = true;
	}else{
		m_pianoPress = false;
	}
}
void MainWindow::keyRelease(){
}


void MainWindow::openHistory(){
	history_dialog->open();
}

void MainWindow::openCompareFrequency(){
	freqCompare_dialog->open();
}

void MainWindow::mousePressEvent(QMouseEvent *event){
	QPoint position;
	position = event->pos();
	//int x = position.xp;
	//position.x();
	QString qStr = QString::number(position.x());
	//qStr.append(QString(",%1"),position.y());
	setStatusTip(qStr);
}

