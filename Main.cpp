/*
 * Main.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: jrparks
 *      Author: https://github.com/jrjparks
 */

#include "Main.h"

int main(int argc, char* argv[]) {
	setenv("DISPLAY", ":0", 0);

	fprintf(stdout, "Preparing to open camera.\n");

	camera.Open("/dev/video0");
	if (!camera.IsOpen()) {
		fprintf(stderr, "Unable to open camera.\n");
		return -1;
	}

	camera.ChangeCaptureSize(v4l2::CAPTURE_SIZE_800x600);

	camera.GetBrightness(Brightness);
	camera.GetContrast(Contrast);
	camera.GetSaturation(Saturation);
	camera.GetSharpness(Sharpness);
	camera.GetGain(Gain);
	camera.GetBacklightCompensation(BacklightCompensation);
	camera.GetWhiteBalanceTemperature(WhiteBalanceTemperature);
	++WhiteBalanceTemperature;
	camera.GetFocus(Focus);
	++Focus;

	cv::namedWindow("Adjustments", CV_WINDOW_NORMAL);
	cv::createTrackbar("Brightness", "Adjustments", &Brightness, 255);
	cv::createTrackbar("Contrast", "Adjustments", &Contrast, 255);
	cv::createTrackbar("Saturation", "Adjustments", &Saturation, 255);
	cv::createTrackbar("Sharpness", "Adjustments", &Sharpness, 255);
	cv::createTrackbar("Gain", "Adjustments", &Gain, 255);
	cv::createTrackbar("Backlight Compensation", "Adjustments", &BacklightCompensation, 1);
	
	// Off by one to account for -1 being auto.
	cv::createTrackbar("White Balance Temperature", "Adjustments", &WhiteBalanceTemperature, 6501);
	cv::createTrackbar("Focus", "Adjustments", &Focus, 256);

	int wait_key = 0;
	while (true) {
		camera.SetBrightness(Brightness);
		camera.SetContrast(Contrast);
		camera.SetSaturation(Saturation);
		camera.SetSharpness(Sharpness);
		camera.SetGain(Gain);
		camera.SetBacklightCompensation(BacklightCompensation);
		--WhiteBalanceTemperature;
		camera.SetWhiteBalanceTemperature(WhiteBalanceTemperature);
		++WhiteBalanceTemperature;
		--Focus;
		camera.SetFocus(Focus);
		++Focus;

		if (camera.GrabFrame()) {
			if (camera.RetrieveMat(frame))
				cv::imshow("Camera", frame);
		} else {
			fprintf(stderr, "Unable to grab frame from camera.\n");
		}
		wait_key = cv::waitKey(30);
		if (wait_key == 27 || wait_key == 32)
			break;
	}

	fprintf(stdout, "Closing camera.\n");
	camera.Close();
}
