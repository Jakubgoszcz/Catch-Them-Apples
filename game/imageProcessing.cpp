//
// Created by root on 4/25/24.
//
#include "imageProcessing.h"
#include <iostream>
#include <opencv2/imgproc.hpp>

using namespace cv;

cv::Point get_hand_cords(const std::vector<std::vector<cv::Point>>& contours)
{
	cv::Moments totalMoments;

	for (const auto& contour : contours) {
		// Oblicz momenty konturu
		cv::Moments m = cv::moments(contour);
		totalMoments.m00 += m.m00;
		totalMoments.m10 += m.m10;
		totalMoments.m01 += m.m01;
	}

	cv::Point point(-1, -1);
	if (totalMoments.m00 != 0) {
		// Oblicz sumaryczny środek ciężkości
		point.x = static_cast<int>(totalMoments.m10 / totalMoments.m00);
		point.y = static_cast<int>(totalMoments.m01 / totalMoments.m00);
	}

	return point;
}

std::vector<std::vector<cv::Point>>
findContoursForColor(const cv::Mat& frame, cv::Scalar lower, cv::Scalar upper)
{
	cv::Mat hsvImage;
	cv::cvtColor(frame, hsvImage, cv::COLOR_BGR2HSV);

	cv::Mat mask;
	cv::inRange(hsvImage, lower, upper, mask);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(mask, contours, cv::RETR_EXTERNAL,
					 cv::CHAIN_APPROX_SIMPLE);

	return contours;
}

cv::Point processImage(const cv::Mat& frame, cv::Scalar lower, cv::Scalar upper)
{
	return get_hand_cords(
		findContoursForColor(frame, std::move(lower), std::move(upper)));
}

cv::Mat bodySegmentation(const cv::Mat& frame, const cv::Mat referenceFrame)
{
	int brightnessFactor = 20;
	int darknessFactor = 20;
	int maskSize = 4;
	cv::Mat darkenedFrame;
	cv::Mat brightenedFrame;
	cv::Mat mask;
	referenceFrame.convertTo(brightenedFrame, -1, 1, brightnessFactor);
	referenceFrame.convertTo(darkenedFrame, -1, 1, darknessFactor * (-1));
	cv::inRange(frame, darkenedFrame, brightenedFrame, mask);
	cv::morphologyEx(mask, mask, cv::MORPH_OPEN,
					 cv::getStructuringElement(cv::MORPH_RECT,
											   cv::Size(maskSize, maskSize)));
	cv::morphologyEx(mask, mask, cv::MORPH_CLOSE,
					 cv::getStructuringElement(cv::MORPH_RECT,
											   cv::Size(maskSize, maskSize)));
	cv::bitwise_not(mask, mask);
	return mask;
}

sf::Image matToSfImageWithTransparency(const cv::Mat& mat, const cv::Mat& mask)
{
	sf::Image image;
	image.create(mat.cols, mat.rows);
	cv::flip(mat, mat, 1);
	cv::flip(mask, mask, 1);
	for (int y = 0; y < mat.rows; ++y) {
		for (int x = 0; x < mat.cols; ++x) {
			cv::Vec3b pixel = mat.at<cv::Vec3b>(y, x);
			uchar alpha = mask.at<uchar>(y, x); // Wartość z maski
			if (alpha > 0) {
				image.setPixel(x, y,
							   sf::Color(pixel[2], pixel[1], pixel[0], alpha));
			}
			else {
				image.setPixel(x, y, sf::Color::Transparent);
			}
		}
	}

	return image;
}
