#ifndef GAME_GAMEFUNCTIONS_H
#define GAME_GAMEFUNCTIONS_H

#include "globalVariables.h"
#include "imageProcessing.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <thread>
#include <vector>

extern sf::Vector2f leftTreeHolePosition;
extern sf::Vector2f rightTreeHolePosition;

using namespace cv;

void processEvents(sf::RenderWindow& window, bool& gameOver);

void updateSpritesPosition(cv::Mat& frame, sf::Sprite& basketSprite,
						   sf::Sprite& weaponSprite, int windowWidth,
						   int windowHeight);

void handleFruitAndEnemies(int& randomFruit, int& randomEnemy,
						   std::vector<sf::Sprite>& appleSprites,
						   std::vector<sf::Sprite>& enemySprites, int& score,
						   int& lifes, int windowWidth, int windowHeight,
						   sf::Sprite& basketSprite, sf::Sprite& weaponSprite,
						   float& direction, sf::Vector2f& collisionVector,
						   float& angle, int& hit, sf::Texture& appleTexture,
						   sf::Texture& bilberryTexture,
						   sf::Texture& cherryTexture, sf::Texture& antTexture,
						   sf::Texture& beetleTexture,
						   sf::Texture& enemyTexture);

bool loadTextures(sf::Texture& appleTexture, sf::Texture& bilberryTexture,
				  sf::Texture& cherryTexture, sf::Texture& basketTexture,
				  sf::Texture& weaponTexture, sf::Texture& enemyTexture,
				  sf::Texture& antTexture, sf::Texture& beetleTexture,
				  sf::Texture& backgroundTexture, sf::Texture& treeholeTexture);

bool loadFont(sf::Font& font);

sf::Text createText(const std::string& content, const sf::Font& font,
					unsigned int characterSize, const sf::Color& color,
					const sf::Vector2f& position);

void createApple(std::vector<sf::Sprite>& appleSprites,
				 const sf::Texture& appleTexture, int windowWidth,
				 int windowHeight);

bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);

sf::Vector2f resolveCollision(sf::Sprite& sprite1, const sf::Sprite& sprite2,
							  sf::Vector2f& collisionVector);

void handleApples(std::vector<sf::Sprite>& appleSprites,
				  sf::Sprite& basketSprite, int& score, int& lifes,
				  int windowHeight, int randoFruit);

void createBasket(sf::Sprite& basketSprite, const sf::Texture& basketTexture,
				  int windowWidth, int windowHeight);

void createWeapon(sf::Sprite& weaponSprite, const sf::Texture& weaponTexture,
				  int windowWidth, int windowHeight);

void createEnemy(std::vector<sf::Sprite>& enemySprites,
				 const sf::Texture& enemyTexture, int windowWidth,
				 int windowHeight);

void handleEnemy(std::vector<sf::Sprite>& enemySprites,
				 sf::Sprite& basketSprite, sf::Sprite& weaponSprite, int& score,
				 int& lifes, int windowHeight, int windowWidth,
				 float* direction, float basketX, float basketY,
				 int randomEnemy, sf::Vector2f& collisionVector, float* angle,
				 int* hit);

void displayText(sf::RenderWindow& window, sf::Text& text,
				 const std::string& content, const sf::Vector2f& position);

void handleBasketMovement(sf::Sprite& basketSprite, int windowWidth);

int displayMainMenu(sf::RenderWindow& window, cv::VideoCapture& cap);

int runGame(sf::RenderWindow& window, cv::VideoCapture& cap,
			cv::Mat& referenceFrame);

void playMusic(const std::string& filename);

sf::Texture drawBodyOnWindowTexture(cv::Mat frame, cv::Mat referenceFrame);
#endif // GAME_GAMEFUNCTIONS_H
