#ifndef FREQUENCYCOMPARE_H
#define FREQUENCYCOMPARE_H

#include <QDialog>
#include <qpainter.h>
#include "ui_frequencycompare.h"

class FrequencyCompare : public QDialog
 {
     Q_OBJECT

 public:
     FrequencyCompare(QWidget *parent = 0);
     void setCurrentNoteFreq(float prevFreq,float curFreq,float nextFreq);
     void setCurrentDetecetedFreq(float inFreq);
     inline float getRatio(){return ratio;}
 private:
     //void paintEvent(QPaintEvent * /*event*/ );

 private:
     int xCounter;
     float currentNoteFreq;
     float prevNoteFreq;
     float nextNoteFreq;

     float currentDetecetedFreq;

     float ratio;


 };

#endif // FREQUENCYCOMPARE_H
