#ifndef GAME_IMAGEPROCESSING_H
#define GAME_IMAGEPROCESSING_H

#include <SFML/Graphics.hpp>
#include <opencv2/core/types.hpp>
#include <vector>

cv::Point get_hand_cords(const std::vector<std::vector<cv::Point>>& contours);
void calculate_HSV_value(int* arr);
std::vector<std::vector<cv::Point>>
findContoursForColor(const cv::Mat& frame, cv::Scalar lower, cv::Scalar upper);
cv::Point processImage(const cv::Mat& frame, cv::Scalar lower,
					   cv::Scalar upper);
cv::Mat bodySegmentation(const cv::Mat& frame, const cv::Mat referenceFrame);
sf::Image matToSfImageWithTransparency(const cv::Mat& mat, const cv::Mat& mask);
#endif // GAME_IMAGEPROCESSING_H
