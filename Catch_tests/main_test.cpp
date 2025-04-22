#include <catch2/catch_test_macros.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <opencv2/opencv.hpp>
#include "../game/gameFunctions.h"
#include "../game/imageProcessing.h"
#include "../game/globalVariables.h"

const double threshold = 30.;

void recognitionTest(const std::string& baseFilename){
    auto point = processImage(cv::imread("testRes/" + baseFilename + ".jpg"), colorWeaponStart, colorWeaponEnd);
    // todo check for other colors too
    std::ifstream f("testRes/" + baseFilename + ".txt");
    int x, y;
    f >> x >> y;
    double distance = std::sqrt(std::pow(point.x - x, 2) + std::pow(point.y - y, 2));
    CHECK(distance < threshold);
}

TEST_CASE("test0", "[recognition]") {
    recognitionTest("test0");
}

TEST_CASE("test1", "[recognition]") {
    recognitionTest("test1");
}

TEST_CASE("test2", "[recognition]") {
    recognitionTest("test2");
}

TEST_CASE("test3", "[recognition]") {
    recognitionTest("test3");
}

TEST_CASE("test4", "[recognition]") {
    recognitionTest("test4");
}

TEST_CASE("test5", "[recognition]") {
    recognitionTest("test5");
}

TEST_CASE("test6", "[recognition]") {
    recognitionTest("test6");
}

TEST_CASE("test7", "[recognition]") {
    recognitionTest("test7");
}

TEST_CASE("test8", "[recognition]") {
    recognitionTest("test8");
}

TEST_CASE("test9", "[recognition]") {
    recognitionTest("test9");
}

TEST_CASE("test10", "[recognition]") {
    recognitionTest("test10");
}

TEST_CASE("test11", "[recognition]") {
    recognitionTest("test11");
}
