#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "amplitudemonitor.h"
#include "frequencymonitor.h"
#include "inputwaveplotter.h"
#include "piano.h"
#include "portaudio.h"
#include "history.h"
#include "autocorrelation.h"
#include "frequencycompare.h"

#include <QSpinBox>




class BackgroundColorSetter : public QWidget
 {
     Q_OBJECT

 public:
     BackgroundColorSetter(QWidget *parent = 0);

 private:
     void paintEvent(QPaintEvent * /*event*/ );
     void mousePressEvent(QMouseEvent *event);

 private:

 };




typedef struct sound_file{
    	float* data_frame;
    	unsigned long num_frame;
    	float* start_frame;
    	float* end_frame;
}Audio_file;

enum note_frequency{
	C1	= 3270,	//100
	Db1	= 3465,
	D1	= 3671,
	Eb1	= 3889,
	E1	= 4120,
	F1	= 4365,
	Gb1	= 4625,
	G1	= 4900,
	Ab1	= 5191,
	A1	= 5500,
	Bb1	= 5827,
	B1	= 6174,
	C2	= 6541,
	Db2	= 6930,
	D2	= 7342,
	Eb2	= 7778,
	E2	= 8241,
	F2	= 8731,
	Gb2	= 9250,
	G2	= 9800,
	Ab2	= 10383,
	A2	= 11000,
	Bb2	= 11654,
	B2	= 12347,
	C3	= 13081,
	Db3	= 13859,
	D3	= 14683,
	Eb3	= 15556,
	E3	= 16481,
	F3	= 17461,
	Gb3	= 18500,
	G3	= 19600,
	Ab3	= 20765,
	A3	= 22000,
	Bb3	= 23308,
	B3	= 24694,
	C4	= 26163,
	Db4	= 27718,
	D4	= 29366,
	Eb4	= 31113,
	E4	= 32963,
	F4	= 34923,
	Gb4	= 36999,
	G4	= 39200,
	Ab4	= 41530,
	A4	= 44000,
	Bb4	= 46616,
	B4	= 49388,
	C5	= 52325,
	Db5	= 55437,
	D5	= 58733,
	Eb5	= 62225,
	E5	= 65926,
	F5	= 69846,
	Gb5	= 73999,
	G5	= 78399,
	Ab5	= 83061,
	A5	= 88000,
	Bb5	= 93233,
	B5	= 98777
};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initializeProgram();
    void createUI();
    void closeEvent(QCloseEvent *event);

    //void keyPressEvent(QKeyEvent *k);

    //portaudio
    void pa_init();
    void pa_term();
    void pa_start();
    void pa_stop();

    //soundfile
    void loadSoundFile();

    //metronome
    void metronome_init();

    inline bool isMute(){return m_mute;}
    inline bool isPlay(){return m_play;}
    inline bool isMetronome(){return m_metronome;}
    inline Audio_file getMetronome_clk(){return metronome_clk;}
    inline void setWait(bool status){m_metronomeWait = status;}
    inline bool isWait(){return m_metronomeWait;}
    inline int getTempo(){tempo = m_tempoSpinbox->value();return tempo;}
    inline void setEndtime(float time){endtime = time;}
    inline float getEndtime(){return endtime;}

    //piano
    inline bool isPress(){return m_pianoPress;}
    inline void setRelease(bool status){m_pianoPress = status;}

    void processAudio(float *data,int size);
	//void refreshAmpMonitor(float level);
	void refreshMonitor();

	void refreshCompareFrequencyMonitor();
	//void keyboardPress(int midiNote);
	void doHistory();

	void mousePressEvent(QMouseEvent *event);
private slots:
	//main audio

	void play();
	void pause();
	void metronome();
	void toggleMute();

	void keyPress();
	void keyRelease();
	void openHistory();
	void openCompareFrequency();

private:
    //ui
    Ui::MainWindow *ui;

    //portaudio
    int m_num_channels;
    int m_frame_block;
    int m_sampling_rate;
    float m_pitch_detect;
    const PaDeviceInfo *info;
    const PaHostApiInfo * hostapi;
    PaStreamParameters outputParameters, inputParameters;
    PaStream *audioStream;

    //status
    bool m_mute;
    bool m_play;
    bool m_metronome;
    bool m_metronomeWait;

    bool m_pianoPress;

    //ui
    QPushButton *m_muteButton;
    QPushButton *m_playButton;
    QPushButton *m_pauseButton;
    QPushButton *m_metronomeButton;
    QSpinBox *m_tempoSpinbox;
    QLCDNumber *m_frequencyLCDbox;
    QLCDNumber *m_pianoFrequencyLCDbox;
    QLabel *m_noteNameLabel;
    QLabel *m_noteCorrectPercentLabel;

    QLabel *my_freqLabel;
    QLabel *piano_freqLabel;

    static const QString Mute;
    static const QString Play;
    static const QString Pause;
    static const QString Metronome;

    QPushButton *testButton;

    Audio_file metronome_clk;
    float tempo;
    float endtime;

    //AmplitudeMonitor

    AmplitudeMonitor *ampMonitor;
    FrequencyMonitor *frequencyMonitor;
    InputWavePlotter *inputPlotterMonitor;
    Piano *pianoRoll;

    Autocorrelaton *autocorrelation;

    //history _dialog
    QPushButton *history_button;
    History *history_dialog;

    BackgroundColorSetter *bgSetter;
    float ratio;
    //compare frequency
    float detectedFrequency;
    float currentFrequency;

    QPushButton *compare_button;
    FrequencyCompare *freqCompare_dialog;
    QLCDNumber *freq_comareLCD;
    //audio file

    Audio_file sound_C1;
    Audio_file sound_Db1;
    Audio_file sound_D1	;
    Audio_file sound_Eb1;
    Audio_file sound_E1	;
    Audio_file sound_F1	;
    Audio_file sound_Gb1;
    Audio_file sound_G1	;
    Audio_file sound_Ab1;
    Audio_file sound_A1	;
    Audio_file sound_Bb1;
    Audio_file sound_B1	;
    Audio_file sound_C2	;
    Audio_file sound_Db2;
    Audio_file sound_D2	;
    Audio_file sound_Eb2;
    Audio_file sound_E2	;
    Audio_file sound_F2	;
    Audio_file sound_Gb2;
	Audio_file sound_G2	;
	Audio_file sound_Ab2;
	Audio_file sound_A2	;
	Audio_file sound_Bb2;
	Audio_file sound_B2	;
	Audio_file sound_C3	;
	Audio_file sound_Db3;
	Audio_file sound_D3;
	Audio_file sound_Eb3;
	Audio_file sound_E3	;
	Audio_file sound_F3	;
	Audio_file sound_Gb3;
	Audio_file sound_G3;
	Audio_file sound_Ab3;
	Audio_file sound_A3;
	Audio_file sound_Bb3;
	Audio_file sound_B3;
	Audio_file sound_C4;
	Audio_file sound_Db4;
	Audio_file sound_D4	;
	Audio_file sound_Eb4;
	Audio_file sound_E4;
	Audio_file sound_F4;
	Audio_file sound_Gb4;
	Audio_file sound_G4;
	Audio_file sound_Ab4;
	Audio_file sound_A4;
	Audio_file sound_Bb4;
	Audio_file sound_B4;
	Audio_file sound_C5;
	Audio_file sound_Db5;
	Audio_file sound_D5;
	Audio_file sound_Eb5;
	Audio_file sound_E5;
	Audio_file sound_F5;
	Audio_file sound_Gb5;
	Audio_file sound_G5;
	Audio_file sound_Ab5;
	Audio_file sound_A5;
	Audio_file sound_Bb5;
	Audio_file sound_B5;





};

#endif // MAINWINDOW_H
