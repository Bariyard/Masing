/*
 * autocorrelation.cpp
 *
 *  Created on: Nov 14, 2012
 *      Author: DORAEMIZ
 */
#include "autocorrelation.h"

#define peakThreshold 0.8
#define fs 44100 //samplingrate

/* Chromatic Scale */
#define NUM_NOTES 25
float reference[NUM_NOTES] = { 	164.8, // E
								174.6, // F
								185.0, // F#
								196.0, // G
								207.7, // G#
								220.0, // A
								233.1, // A#
								246.9, // B
								261.6, // C
								277.2, // C#
								293.7, // D
								311.1, // D#
								329.6, // E
								349.6, // F
								370.0, // F#
								392.0, // G
								415.3, // G#
								440.0, // A
								466.2, // A#
								493.9, // B
								523.3, // C
								554.4, // C#
								583.3, // D
								622.3, // D#
								659.3 }; // E
//
/* C MAJOR SCALE =================================================================
#define NUM_NOTES 15
float reference[NUM_NOTES] = { 164.8, // E
174.6, // F
196.0, // G
220.0, // A
246.9, // B
261.6, // C
293.7, // D
329.6, // E
349.6, // F
392.0, // G
440.0, // A
493.9, // B
523.3, // C
583.3, // D
659.3 }; // E
*/

float z[4096];



Autocorrelaton::Autocorrelaton():detectedFrequency(0), dev(0){

}

void Autocorrelaton::find_pitch_offset(float *in,int winSize) {
	float ratio, max;
	int i=0, j=0, swit, first;

	int peakCounter = 0,peakIndex = 0;
	float peak = 0,delta1 = 0,delta2 = 0;
	float difference1,minDifference = 100,referenceFrequency;

	// ---------------
	// Autocorrelation
	// ---------------
	max = 1.;
	for(i = 0; i < winSize; i++) {
		z[i] = 0;
		for(j = 0; j < 13; j++)
			z[i] += in[i+j]*in[j];
		if(z[i] > max){
			max = z[i]; // Record max correlation peak
		}
	}
	// -----------------------------
	// Autocorrelation Normalization
	// -----------------------------
	for(i = 0; i < winSize; i++){
		z[i] = z[i]/max; // Normalize with respect to max peak
	}

	// --------------
	// Peak Detection
	// --------------

	first = -1; peakCounter = 0; dev = 0.;
	for(i = 10; i < winSize-15; i++){
		delta1 = z[i] -z[i-1];
		delta2 = z[i+1] - z[i];

		if((delta1 >= 0) && (delta2 < 0) && (z[i] > z[0] * peakThreshold)){
			swit=1;
			for (j=-9; j<14; j++)
				if (z[i+j] > z[i]) swit = 0;
			if (swit) {
				if (first == -1)
					first = i;
				else {
					delta1 = i - peakIndex;
					delta2 = first - (i - delta1 * peakCounter);
					dev += delta2 * delta2;
				}
				peakIndex = i;
				peakCounter ++;
			}
		}
	}

	// ---------------------------
	// Refined Frequency Detection
	// ---------------------------
	detectedFrequency = (fs*(peakCounter-1)*1.)/(peakIndex - first);

/*	// --------------------------------
	// Frequency & Reference Comparison
	// --------------------------------
	minDifference = 10000.;
	if((detectedFrequency >= reference[0]) && (detectedFrequency <= reference[NUM_NOTES-1]) &&
			(dev < 100.)) {
		for(i = 0; i < NUM_NOTES; i++) {
			difference1 = fabs(detectedFrequency - reference[i]);
			if(difference1 < minDifference) {
				minDifference = difference1;
				referenceFrequency = reference[i];
			} else {
				break;
			}
		}
		ratio = detectedFrequency/referenceFrequency;
	} else {
		ratio = 1.;
	}*/

}
