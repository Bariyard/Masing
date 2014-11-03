#include "inputwaveplotter.h"

#include <Qpainter>

InputWavePlotter::InputWavePlotter(QWidget *parent)
    : QWidget(parent),in_data(NULL),buffer_size(0)

{
   // setBackgroundRole(QPalette::Base);
   //setAutoFillBackground(true);
    //setStyleSheet("background-color: blue;");

}


void InputWavePlotter::paintEvent(QPaintEvent * /* event */)
{

    QPainter painter(this);

    painter.setPen(Qt::black);

    float x1,x2,y1,y2;
    int counter = 0;
    float step = 0.15;


    for (float i = 0; counter < buffer_size; i+=step) {
         x1 = 10+i;
         y1 = 60-(in_data[counter]*160);
         x2 = 10+i+step;
         y2 = 60-(in_data[counter+1]*160);

        painter.drawLine(QPointF(x1, y1),QPointF(x2, y2));
        counter++;
    }
  /*   float sum = 0,prev = 0;
    float max = 0 ;
    int max_index = 0;
    /*    for (int i = 0; counter < buffer_size; i+=step) {
         x1 = 10+i;




         sum=0;
         for (int j=0; j<buffer_size-i; j++) {
        	 sum += in_data[i] * in_data[j+i];
        	 prev = sum;
         }

         y1 = 60-(prev*20);x2 = 10+i+step;y2 = 60-(sum*20);
         prev = 0;
         if(sum > max){
        	 max = sum;
        	 max_index = i;
         }
        painter.drawLine(QPointF(x1, y1),QPointF(x2, y2));
        counter++;
    }
   // peak = max_index;

	for (int i=0; i<buffer_size; i++) {
	          int sum=0;
	          for (int j=0; j<buffer_size-i; j++) {
	            sum += in_data[i] * in_data[j+i];
	          }
	          r[i]=sum;
	}
*/


}

void InputWavePlotter::setFrequency(float *frequencyData,int size)
{
	in_data = (float*)frequencyData;
	buffer_size = size;

}

