/*
 * Main.cpp
 *
 *  Created on: Dec 31, 2014
 *      Author: jrparks
 */

#include "Main.h"
#include <iostream>

int main(int argc, char* argv[]) {
	setenv("DISPLAY", ":0", 0);

	cv::namedWindow("Adjustments", CV_WINDOW_NORMAL);
	cv::createTrackbar("Brightness", "Adjustments", &Brightness, 255);
	cv::createTrackbar("Contrast", "Adjustments", &Contrast, 255);
	cv::createTrackbar("Saturation", "Adjustments", &Saturation, 255);
	cv::createTrackbar("Sharpness", "Adjustments", &Sharpness, 255);
	cv::createTrackbar("Focus", "Adjustments", &Focus, 256);

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
	camera.GetFocus(Focus);

	int wait_key = 0;
	while (true) {
		camera.SetBrightness(Brightness);
		camera.SetContrast(Contrast);
		camera.SetSaturation(Saturation);
		camera.SetSharpness(Sharpness);
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
