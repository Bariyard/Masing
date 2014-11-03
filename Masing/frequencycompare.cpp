#include "frequencycompare.h"

float detectedFreqRatio[400];

FrequencyCompare::FrequencyCompare(QWidget *parent): QDialog(parent),
	xCounter(0)
	,currentNoteFreq(0)
	,prevNoteFreq(0)
	,nextNoteFreq(0)
	,currentDetecetedFreq(0)
	,ratio(0)
{
	setFixedSize(500,200);
	/*for(int i = 0; i < 400; i++){
		detectedFreqRatio[i] = 0;
	}*/
	xCounter = 0;
}
/*
void FrequencyCompare::paintEvent(QPaintEvent * /*event*/ //){
/*	QPainter painter(this);
	painter.setPen(Qt::black);
	painter.drawLine(0,100,500,100);

	float x1,y1,x2,y2;
	for(int i = 0; i < 400; i++){
		x1 = i;
		y1 = 100-((detectedFreqRatio[i]))*100;
		x2 = i+1;
		y2 = 100-((detectedFreqRatio[i+1]))*100;
	}
	painter.setPen(Qt::red);
	painter.drawLine(QPointF(x1,y1),QPointF(x2,y2));

}
*/
void FrequencyCompare::setCurrentNoteFreq(float prevFreq,float curFreq,float nextFreq){
	prevNoteFreq = prevFreq/100.;
	currentNoteFreq = curFreq/100. ;
	nextNoteFreq = nextFreq/100.;

}

void FrequencyCompare::setCurrentDetecetedFreq(float inFreq){
	if(xCounter==400){
		for(int i = 0; i < 400; i++){
			//detectedFreqRatio[i] = 0;
		}
		xCounter = 0;
	}
	float difFreq1 = 0,difFreq2 = 0;
	ratio = 0;
	if(inFreq > currentNoteFreq){
		difFreq1 = nextNoteFreq - currentNoteFreq;
		difFreq2 = inFreq - currentNoteFreq;
		ratio = (float)difFreq2*1./difFreq1;
	}else if(inFreq < currentNoteFreq){
		difFreq1 = currentNoteFreq - prevNoteFreq;
		difFreq2 = currentNoteFreq - inFreq;
		ratio = (float)difFreq2*1./difFreq1;
	}else if(inFreq == currentNoteFreq ){
		ratio = 0;
	}

	//detectedFreqRatio[xCounter] = ratio;
	xCounter++;

 }
