#ifndef FREQUENCYMONITOR_H
#define FREQUENCYMONITOR_H

#include <QWidget>
#include "fft/kiss_fftr.h"
#include "fft/kiss_fft.h"




class FrequencyMonitor : public QWidget
 {
     Q_OBJECT

 public:
     FrequencyMonitor(QWidget *parent = 0);

     void setFrequency(float *frequencyData,int size);
     float getPitch(){return pitch;}

 private:
     void paintEvent(QPaintEvent *event);

 private:

     float *in_data;
     int fft_size;

     //pitch

     float pitch;

 };
#endif // FREQUENCYMONITOR_H
