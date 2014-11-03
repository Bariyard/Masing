#include "amplitudemonitor.h"

#include <QPainter>

AmplitudeMonitor::AmplitudeMonitor(QWidget *parent)
    : QWidget(parent),m_amplevel(0),in_data(NULL)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMinimumHeight(30);
    setMinimumWidth(100);
}

AmplitudeMonitor::~AmplitudeMonitor(){}

void AmplitudeMonitor::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(QRect(painter.viewport().left()+10,
                           painter.viewport().top()+10,
                           painter.viewport().right()-20,
                           painter.viewport().bottom()-20));
    if (m_amplevel >= 0.7){
    	painter.setPen(Qt::red);
    }else{
    	painter.setPen(Qt::green);
    }
    int pos = ((painter.viewport().right()-20)-(painter.viewport().left()+11))*m_amplevel;

    for (int i = 0; i < 10; ++i) {
        int x1 = painter.viewport().left()+10;
        int y1 = painter.viewport().top()+10+i;
        int x2 = painter.viewport().left()+10+pos;
        int y2 = painter.viewport().top()+10+i;
        if (x2 < painter.viewport().left()+10)
            x2 = painter.viewport().left()+10;

        painter.drawLine(QPoint(x1, y1),QPoint(x2, y2));
    }
}

void AmplitudeMonitor::setAmpLevel(float *data, int size)
{
	in_data = (float*)data;
	float maxVal = 0.0f;
	for( int i = 0; i< size; i++){
		if(maxVal < in_data[i]){ //find max amp
			maxVal = in_data[i];
		}
	}
	m_amplevel = maxVal;
}

