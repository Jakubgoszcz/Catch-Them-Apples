#include "gameFunctions.h"
#include "globalVariables.h"
#include "imageProcessing.h"

using namespace cv;

int main(int argc, char** argv)
{
	int windowWidth = 640;
	int windowHeight = 480;

	Mat frame;
	Mat referenceFrame;
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		std::cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	int i = 0;
	while (i < 40) {
		cap.read(referenceFrame);
		i++;
	}

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
							"Catch them apples!",
							sf::Style::Titlebar | sf::Style::Close);

	while (displayMainMenu(window, cap) == 1) {
		runGame(window, cap, referenceFrame);
	}

	return 0;
}
