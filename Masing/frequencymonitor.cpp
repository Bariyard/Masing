#include "frequencymonitor.h"

#include <QPainter>

#define buffer_size 2048

kiss_fft_cpx cin[buffer_size];
kiss_fft_cpx cout[buffer_size];
kiss_fft_cpx fft_bin[buffer_size];
float r[buffer_size];

FrequencyMonitor::FrequencyMonitor(QWidget *parent)
    : QWidget(parent),in_data(NULL),fft_size(buffer_size),pitch(0)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}



void FrequencyMonitor::setFrequency(float *frequencyData,int size)
{
	fft_size = size;
	kiss_fft_scalar zero;
	for( int i = 0; i< fft_size; i++){
			//FFT
		cin[i].r = (float)frequencyData[i]*(0.53836+0.46164*cos(2*3.14*i/fft_size-1));
		cin[i].i = (float)frequencyData[i]*(0.53836+0.46164*cos(2*3.14*i/fft_size-1));
		cout[i].r = zero;
		cout[i].i = zero;
		fft_bin[i].r = zero;
		fft_bin[i].i = zero;

	}
	kiss_fftr_cfg fftConfiguration = kiss_fftr_alloc( fft_size, 0, NULL, NULL );
	kiss_fftr( fftConfiguration, (kiss_fft_scalar*)cin, cout );
}

void FrequencyMonitor::paintEvent(QPaintEvent * /* event */)
{

    QPainter painter(this);

    painter.setPen(Qt::black);
    float x1,x2,y1,y2;
    int counter = 0;
    float step = 1;
    for (int i = 0; counter < fft_size/2; i+=step) {
    	x1 = 10+i;
    	y1 = 75-(10*(log10((pow(cout[counter].r,2)+pow(cout[counter].i,2)))));
        x2 = 10+i+step;
        y2 = 75-(10*(log10((pow(cout[counter+1].r,2)+pow(cout[counter+1].i,2)))));
        painter.drawLine(QPointF(x1, y1),QPointF(x2, y2));
        counter++;
    }
}



