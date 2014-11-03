#ifndef INPUTWAVEPLOTTER_H
#define INPUTWAVEPLOTTER_H

#include <QWidget>
#include "fft/kiss_fftr.h"
#include "fft/kiss_fft.h"


class InputWavePlotter : public QWidget
 {
     Q_OBJECT

 public:
     InputWavePlotter(QWidget *parent = 0);

     void setFrequency(float *frequencyData,int size);


 private:
     void paintEvent(QPaintEvent *event);

 private:
     float *in_data;
     int buffer_size;

 };

#endif // INPUTWAVEPLOTTER_H
