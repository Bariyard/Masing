/*
 * autocorrelation.h
 *
 *  Created on: Nov 14, 2012
 *      Author: DORAEMIZ
 */

#ifndef AUTOCORRELATION_H_
#define AUTOCORRELATION_H_

class Autocorrelaton {
	Autocorrelaton();
public:
	void find_pitch_offset(float *in,int winSize);
	inline float getDetectedFrequency(){return detectedFrequency;}


private:
    float detectedFrequency, dev;
    float *ratio;


};
#endif /* AUTOCORRELATION_H_ */
