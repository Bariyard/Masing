#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include "ui_history.h"
#include "math.h"

class History : public QDialog
{
    Q_OBJECT

public:
    History(QWidget *parent = 0);
    void clear();
    void note_recieve(int midiNum,float prevFreq,float curFreq,float nextFreq);
    void keepHistory(float inAmp,float detecetedFreq);
    inline void setRatio(float inRatio){ratio = inRatio;}
    void sumNoteCount();

    double getTotalPercent(){return notenum[noteOn][2];}


private slots:
	void clearAction();
	void closeAction();
private:
	void calculateTotalPercent();
	void calculateTotalPercent_pernote();
	int noteOn;
	float amplitude;
	int countTry;
	float totalPercent;



	float prevNoteFreq;
	float currentNoteFreq ;
	float nextNoteFreq;
	float ratio;

	float prevFreq;

    Ui::HistoryClass ui;


    double notenum[84][3];
    float summation;
};

#endif // HISTORY_H
