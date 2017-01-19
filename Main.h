/*
 * Main.h
 *
 *  Created on: Dec 31, 2014
 *      Author: jrparks
 *      Author: https://github.com/jrjparks
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "C920Camera.h"

using namespace std;

int Brightness = 128, Contrast = 128, Saturation = 128, Sharpness = 128, Gain = 0, Focus = 0, BacklightCompensation = 0,
		WhiteBalanceTemperature = 0;

v4l2::C920Camera camera;
cv::Mat frame;

#endif /* MAIN_H_ */
