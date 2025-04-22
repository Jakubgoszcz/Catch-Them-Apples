#include "gameFunctions.h"
#include <iostream>

#define LEFT_TREEHOLE_X 100.f
#define LEFT_TREEHOLE_Y 150.f
#define RIGHT_TREEHOLE_X 422.f
#define RIGHT_TREEHOLE_Y 150.f

sf::Music globalMusic;
bool visibility = true;
sf::Vector2f leftTreeHolePosition(LEFT_TREEHOLE_X, LEFT_TREEHOLE_Y);
sf::Vector2f rightTreeHolePosition(RIGHT_TREEHOLE_X, RIGHT_TREEHOLE_Y);

void processEvents(sf::RenderWindow& window, bool& gameOver)
{
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (gameOver && event.type == sf::Event::KeyPressed) {
			window.close();
		}
	}
}

void updateSpritesPosition(cv::Mat& frame, sf::Sprite& basketSprite,
						   sf::Sprite& weaponSprite, int windowWidth,
						   int windowHeight)
{
	std::vector<std::vector<Point>> contours_weapon =
		findContoursForColor(frame, colorWeaponStart, colorWeaponEnd); // blue
	std::vector<std::vector<Point>> contours_basket =
		findContoursForColor(frame, colorBasketStart, colorBasketEnd); // green

	cv::Point point_basket = get_hand_cords(contours_basket);
	cv::Point point_weapon = get_hand_cords(contours_weapon);

	if (point_basket.x >= 0) {
		basketSprite.setPosition(
			(windowWidth - windowWidth * point_basket.x / 640),
			windowHeight * point_basket.y / 480);
	}

	if (point_weapon.x >= 0) {
		weaponSprite.setPosition(
			(windowWidth - windowWidth * point_weapon.x / 640),
			windowHeight * point_weapon.y / 480);
	}
}

void updateWeaponPosition(cv::Mat& frame, sf::Sprite& weaponSprite,
						  int windowWidth, int windowHeight)
{
	std::vector<std::vector<cv::Point>> contours_weapon =
		findContoursForColor(frame, colorWeaponStart, colorWeaponEnd); // blue

	cv::Point point_weapon = get_hand_cords(contours_weapon);

	if (point_weapon.x >= 0) {
		weaponSprite.setPosition(
			(windowWidth - windowWidth * point_weapon.x / 640),
			windowHeight * point_weapon.y / 480);
	}
}

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
						   sf::Texture& enemyTexture)
{
	if (randomFruit == 0) {
		createApple(appleSprites, appleTexture, windowWidth, windowHeight);
	}
	else if (randomFruit == 1) {
		createApple(appleSprites, bilberryTexture, windowWidth, windowHeight);
	}
	else {
		createApple(appleSprites, cherryTexture, windowWidth, windowHeight);
	}

	handleApples(appleSprites, basketSprite, score, lifes, windowHeight,
				 randomFruit);

	if (appleSprites.empty())
		randomFruit = rand() % 3;

	if (randomEnemy == 0) {
		createEnemy(enemySprites, antTexture, windowWidth, windowHeight);
	}
	else if (randomEnemy == 1) {
		createEnemy(enemySprites, beetleTexture, windowWidth, windowHeight);
	}
	else {
		createEnemy(enemySprites, enemyTexture, windowWidth, windowHeight);
	}

	handleEnemy(enemySprites, basketSprite, weaponSprite, score, lifes,
				windowHeight, windowWidth, &direction,
				basketSprite.getPosition().x, basketSprite.getPosition().y,
				randomEnemy, collisionVector, &angle, &hit);
	if (randomEnemy == 0) {
		if (hit == 1) {
			enemySprites.clear();
			collisionVector = sf::Vector2f(0, 0);
			score += 1;
			hit = 0;
		}
	}
	if (randomEnemy == 1) {
		if (hit == 2) {
			enemySprites.clear();
			collisionVector = sf::Vector2f(0, 0);
			score += 1;
			hit = 0;
		}
	}
	if (randomEnemy == 2) {
		if (hit == 3) {
			enemySprites.clear();
			collisionVector = sf::Vector2f(0, 0);
			score += 1;
			hit = 0;
		}
	}

	if (enemySprites.empty())
		randomEnemy = rand() % 3;
}

bool loadTextures(sf::Texture& appleTexture, sf::Texture& bilberryTexture,
				  sf::Texture& cherryTexture, sf::Texture& basketTexture,
				  sf::Texture& weaponTexture, sf::Texture& enemyTexture,
				  sf::Texture& antTexture, sf::Texture& beetleTexture,
				  sf::Texture& backgroundTexture, sf::Texture& treeholeTexture)
{
	if (!appleTexture.loadFromFile("apple.png")) {
		std::cerr << "Failed to load apple texture" << std::endl;
		return false;
	}

	if (!bilberryTexture.loadFromFile("bilberry.png")) {
		std::cerr << "Failed to load bilberry texture" << std::endl;
		return false;
	}

	if (!cherryTexture.loadFromFile("cherry.png")) {
		std::cerr << "Failed to load cherry texture" << std::endl;
		return false;
	}

	if (!basketTexture.loadFromFile("basket.png")) {
		std::cerr << "Failed to load basket texture" << std::endl;
		return false;
	}

	if (!weaponTexture.loadFromFile("weapon.png")) {
		std::cerr << "Failed to load weapon texture" << std::endl;
		return false;
	}

	if (!enemyTexture.loadFromFile("enemy.png")) {
		std::cerr << "Failed to load enemy texture" << std::endl;
		return false;
	}

	if (!antTexture.loadFromFile("ant.png")) {
		std::cerr << "Failed to load ant texture" << std::endl;
		return false;
	}

	if (!beetleTexture.loadFromFile("beetle.png")) {
		std::cerr << "Failed to load beetle texture" << std::endl;
		return false;
	}

	if (!backgroundTexture.loadFromFile("background.png")) {
		std::cerr << "Failed to load background texture" << std::endl;
		return false;
	}

	if (!treeholeTexture.loadFromFile("treehole.png")) {
		std::cerr << "Failed to load treehole texture" << std::endl;
		return false;
	}
	return true;
}

bool loadFont(sf::Font& font)
{
	if (!font.loadFromFile("Quicksand-Bold.ttf")) {
		std::cerr << "Failed to load font" << std::endl;
		return false;
	}
	return true;
}

sf::Text createText(const std::string& content, const sf::Font& font,
					unsigned int characterSize, const sf::Color& color,
					const sf::Vector2f& position)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(characterSize);
	text.setFillColor(color);
	text.setString(content);
	text.setPosition(position);
	return text;
}

bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
{
	return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

sf::Vector2f resolveCollision(sf::Sprite& sprite1, const sf::Sprite& sprite2,
							  sf::Vector2f& collisionVector)
{
	sf::Vector2f direction = sprite1.getPosition() - sprite2.getPosition();
	sf::Vector2f normalized = direction / std::sqrt(direction.x * direction.x +
													direction.y * direction.y);
	collisionVector = normalized * 10.0f;

	return collisionVector;
}

void createApple(std::vector<sf::Sprite>& appleSprites,
				 const sf::Texture& appleTexture, int windowWidth,
				 int windowHeight)
{
	if (appleSprites.empty()) {
		sf::Sprite appleSprite(appleTexture);
		appleSprite.setScale(windowWidth / (appleTexture.getSize().x * 20),
							 windowWidth / (appleTexture.getSize().x * 20));
		appleSprite.setPosition(
			static_cast<float>(std::rand()) /
					(RAND_MAX / (windowWidth * 0.8f - windowWidth * 0.1f)) +
				windowWidth * 0.1f,
			-appleSprite.getGlobalBounds().height);
		appleSprites.push_back(appleSprite);
	}
}

void handleApples(std::vector<sf::Sprite>& appleSprites,
				  sf::Sprite& basketSprite, int& score, int& lifes,
				  int windowHeight, int randomFruit)

{

	for (auto& appleSprite : appleSprites) {
		float moveScale = (windowHeight - windowHeight / 480.0f) / 1000 *
						  ((score / 30 * 0.25) + 1);
		if (randomFruit == 0)
			appleSprite.move(0, 5.0f * moveScale);
		if (randomFruit == 1)
			appleSprite.move(0, 7.0f * moveScale);
		if (randomFruit == 2)
			appleSprite.move(0, 9.0f * moveScale);

		if (appleSprite.getGlobalBounds().intersects(
				basketSprite.getGlobalBounds())) {
			std::thread musicThread(playMusic, "collect.ogg");
			musicThread.detach(); // Pozwól wątkowi działać w tle
			if (randomFruit == 0)
				score++;
			if (randomFruit == 1)
				score += 2;
			if (randomFruit == 2)
				score += 3;
			appleSprites.clear();
		}
		else {
			if (appleSprite.getPosition().y > windowHeight) {
				lifes--;
				appleSprites.clear();
			}
		}
	}
}

void createBasket(sf::Sprite& basketSprite, const sf::Texture& basketTexture,
				  int windowWidth, int windowHeight)
{
	basketSprite.setTexture(basketTexture);
	basketSprite.setScale(windowWidth / (basketTexture.getSize().x * 10),
						  windowWidth / (basketTexture.getSize().x * 10));
	basketSprite.setPosition(
		windowWidth / 2 - basketSprite.getGlobalBounds().width / 2,
		windowHeight - basketSprite.getGlobalBounds().height);
}

void createWeapon(sf::Sprite& weaponSprite, const sf::Texture& weaponTexture,
				  int windowWidth, int windowHeight)
{
	weaponSprite.setTexture(weaponTexture);
	weaponSprite.setScale(windowWidth / (weaponTexture.getSize().x * 10),
						  windowWidth / (weaponTexture.getSize().x * 10));
	weaponSprite.setPosition(
		windowWidth / 2 - weaponSprite.getGlobalBounds().width / 2,
		windowHeight - weaponSprite.getGlobalBounds().height);
}

void createEnemy(std::vector<sf::Sprite>& enemySprites,
				 const sf::Texture& enemyTexture, int windowWidth,
				 int windowHeight)
{
	if (enemySprites.empty()) {
		sf::Sprite enemySprite(enemyTexture, sf::IntRect(0, 0, 16, 16));
		enemySprite.setScale(windowWidth / (enemyTexture.getSize().x * 5),
							 windowWidth / (enemyTexture.getSize().x * 5));

		if (std::rand() % 2 == 0) {
			enemySprite.setPosition(
				(windowWidth * leftTreeHolePosition.x / 640),
				windowHeight * leftTreeHolePosition.y / 480);
		}
		else {
			enemySprite.setPosition(
				(windowWidth * rightTreeHolePosition.x / 640),
				windowHeight * rightTreeHolePosition.y / 480);
		}

		enemySprites.push_back(enemySprite);
	}
}

void playMusic(const std::string& filename)
{
	sf::Music music;
	if (!music.openFromFile(filename)) {
		std::cerr << "Failed to load music file: " << filename << std::endl;
		return;
	}

	music.play();

	while (music.getStatus() == sf::Music::Playing) {
		sf::sleep(sf::milliseconds(100));
	}
}

void handleEnemy(std::vector<sf::Sprite>& enemySprites,
				 sf::Sprite& basketSprite, sf::Sprite& weaponSprite, int& score,
				 int& lifes, int windowHeight, int windowWidth,
				 float* direction, float basketX, float basketY,
				 int randomEnemy, sf::Vector2f& collisionVector, float* angle,
				 int* hit)

{

	static int enemyAnimationFrame = 0;

	for (auto& enemySprite : enemySprites) {
		enemySprite.setTextureRect(
			sf::IntRect(enemyAnimationFrame * 16, 0, 16, 16));
		enemyAnimationFrame = (enemyAnimationFrame + 1) % 4;
	}

	float moveScale = (windowHeight - windowHeight / 480.0f) / 1000 *
					  ((score / 30 * 0.25) + 1);

	for (auto& enemySprite : enemySprites) {
		if (collisionVector == sf::Vector2f(0, 0)) {

			if (enemySprite.getGlobalBounds().intersects(
					basketSprite.getGlobalBounds())) {
				std::thread musicThread(playMusic, "hurt.ogg");
				musicThread.detach();
				lifes--;
				enemySprites.clear();
			}

			if (checkCollision(enemySprite, weaponSprite)) {
				*hit += 1;
				std::thread musicThread(playMusic, "hit.ogg");
				musicThread.detach();
				collisionVector = resolveCollision(enemySprite, weaponSprite,
												   collisionVector);
			}
			enemySprite.setRotation(0);
			if (enemySprite.getPosition().x < basketX) {
				enemySprite.move(*direction, 0);
			}
			else if (enemySprite.getPosition().x > basketX) {
				enemySprite.move(-(*direction), 0);
			}

			if (enemySprite.getPosition().y < basketY) {
				enemySprite.move(0, *direction);
			}
			else if (enemySprite.getPosition().y > basketY) {
				enemySprite.move(0, -(*direction));
			}

			*direction = 7.0f * moveScale;
		}
		else {
			*angle += 20;
			enemySprite.setRotation(*angle);
			enemySprite.move(collisionVector * moveScale);
			collisionVector *= 0.94f;
			if (collisionVector.x < 1.0f && collisionVector.y < 1.0f) {
				collisionVector = sf::Vector2f(0, 0);
			}
		}

		if (enemySprite.getPosition().x < 0 ||
			enemySprite.getPosition().x > windowWidth) {
			collisionVector.x = -collisionVector.x;
		}
		if (enemySprite.getPosition().y < 0 ||
			enemySprite.getPosition().y > windowHeight) {
			collisionVector.y = -collisionVector.y;
		}
	}
}

void displayText(sf::RenderWindow& window, sf::Text& text,
				 const std::string& content, const sf::Vector2f& position)
{
	text.setString(content);
	text.setPosition(position);
	window.draw(text);
}

void handleBasketMovement(sf::Sprite& basketSprite, int windowWidth)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
		basketSprite.getPosition().x > 0) {
		basketSprite.move(-2, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
		basketSprite.getPosition().x + basketSprite.getGlobalBounds().width <
			windowWidth) {
		basketSprite.move(2, 0);
	}
}

int displayMainMenu(sf::RenderWindow& window, cv::VideoCapture& cap)
{

	sf::Texture buttonTexture;
	if (!buttonTexture.loadFromFile("button.png")) {
		std::cerr << "Failed to load button texture" << std::endl;
		return 0;
	}

	sf::Font bearpawFont;
	if (!bearpawFont.loadFromFile("BEARPAW_.ttf")) {
		std::cerr << "Failed to load BEARPAW_ font" << std::endl;
		return 0;
	}

	sf::Font font;
	if (!loadFont(font)) {
		return 0;
	}

	sf::Music music;

	if (!music.openFromFile("ukulele.ogg")) {
		std::cerr << "Nie można załadować pliku muzycznego!" << std::endl;
	}

	music.play();
	music.setLoop(true);

	int windowWidth = window.getSize().x;
	int windowHeight = window.getSize().y;
	int x = 0;

	int collision = 0;
	int collision2 = 0;
	int collision3 = 0;
	int collision4 = 0;

	sf::Sprite weaponSprite;
	sf::Texture weaponTexture;
	if (!weaponTexture.loadFromFile("weapon.png")) {
		std::cerr << "Failed to load weapon texture" << std::endl;
		return 0;
	}
	weaponSprite.setTexture(weaponTexture);

	weaponSprite.setPosition(
		window.getSize().x / 2 - weaponSprite.getLocalBounds().width / 2,
		window.getSize().y / 2 - weaponSprite.getLocalBounds().height / 2);

	sf::Sprite playButton(buttonTexture);
	sf::Sprite optionsButton(buttonTexture);
	sf::Sprite exitButton(buttonTexture);
	sf::Sprite visibilityButton(buttonTexture);

	sf::Text playText("Play", font, 20);
	sf::Text optionsText("Fullscreen", font, 20);
	sf::Text exitText("Exit", font, 20);
	sf::Text visibilityText("Figure", font, 20);
	sf::Text titleText("Catch Them Apples", bearpawFont, 30);

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Mainbackground.png")) {
		std::cerr << "Failed to load background texture" << std::endl;
		return 00;
	}

	sf::Sprite backgroundSprite(backgroundTexture);

	cv::Mat frame;

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {

			int windowWidth = window.getSize().x;
			int windowHeight = window.getSize().y;

			playButton.setScale(windowWidth / 1500.f, windowWidth / 1500.f);
			optionsButton.setScale(windowWidth / 1500.f, windowWidth / 1500.f);
			exitButton.setScale(windowWidth / 1500.f, windowWidth / 1500.f);
			visibilityButton.setScale(windowWidth / 1500.f,
									  windowWidth / 1500.f);

			playButton.setPosition(windowWidth * 0.20 -
									   playButton.getGlobalBounds().width / 2,
								   20);
			optionsButton.setPosition(
				windowWidth * 0.5 - optionsButton.getGlobalBounds().width / 2,
				20);
			exitButton.setPosition(windowWidth * 0.80 -
									   exitButton.getGlobalBounds().width / 2,
								   20);
			visibilityButton.setPosition(
				windowWidth * 0.80 -
					visibilityButton.getGlobalBounds().width / 2,
				windowHeight - visibilityButton.getGlobalBounds().height * 2);

			backgroundSprite.setScale(static_cast<float>(windowWidth) /
										  backgroundTexture.getSize().x,
									  static_cast<float>(windowHeight) /
										  backgroundTexture.getSize().y);
			backgroundSprite.setPosition(0, 0);

			playText.setPosition(
				playButton.getPosition() +
				sf::Vector2f(playButton.getGlobalBounds().width / 2 -
								 playText.getGlobalBounds().width / 2,
							 playButton.getGlobalBounds().height / 2 -
								 playText.getGlobalBounds().height / 2));
			optionsText.setPosition(
				optionsButton.getPosition() +
				sf::Vector2f(optionsButton.getGlobalBounds().width / 2 -
								 optionsText.getGlobalBounds().width / 2,
							 optionsButton.getGlobalBounds().height / 2 -
								 optionsText.getGlobalBounds().height / 2));
			exitText.setPosition(
				exitButton.getPosition() +
				sf::Vector2f(exitButton.getGlobalBounds().width / 2 -
								 exitText.getGlobalBounds().width / 2,
							 exitButton.getGlobalBounds().height / 2 -
								 exitText.getGlobalBounds().height / 2));
			titleText.setPosition(
				windowWidth / 2 - titleText.getGlobalBounds().width / 2,
				windowHeight / 2 - titleText.getGlobalBounds().height / 2);
			visibilityText.setPosition(
				visibilityButton.getPosition() +
				sf::Vector2f(visibilityButton.getGlobalBounds().width / 2 -
								 visibilityText.getGlobalBounds().width / 2,
							 visibilityButton.getGlobalBounds().height / 2 -
								 visibilityText.getGlobalBounds().height / 2));

			playText.setCharacterSize(windowWidth / 25);
			optionsText.setCharacterSize(windowWidth / 25);
			exitText.setCharacterSize(windowWidth / 25);
			titleText.setCharacterSize(windowWidth / 10);
			visibilityText.setCharacterSize(windowWidth / 25);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (checkCollision(playButton, weaponSprite)) {
			collision++;
			if (collision == 20) {
				return 1;
			}
			playButton.setColor(sf::Color(0, 255, 0, 255 * collision / 20));
		}
		else {
			collision = 0;
			playButton.setColor(sf::Color(255, 255, 255, 255));
		}
		if (checkCollision(optionsButton, weaponSprite)) {
			collision2++;
			if (collision2 == 20) {
				if (x == 1) {
					window.create(sf::VideoMode(640, 480), "Fruit Catcher");
					x = 0;
				}
				else {
					window.create(sf::VideoMode::getFullscreenModes()[0],
								  "Fruit Catcher", sf::Style::Fullscreen);
					x = 1;
				}
			}
			optionsButton.setColor(sf::Color(0, 255, 0, 255 * collision2 / 20));
		}
		else {
			collision2 = 0;
			optionsButton.setColor(sf::Color(255, 255, 255, 255));
		}

		if (checkCollision(exitButton, weaponSprite)) {
			collision3++;
			if (collision3 == 20) {
				window.close();
				return 0;
			}
			exitButton.setColor(sf::Color(255, 0, 0, 255 * collision3 / 20));
		}
		else {
			collision3 = 0;
			exitButton.setColor(sf::Color(255, 255, 255, 255));
		}
		if (checkCollision(visibilityButton, weaponSprite)) {
			collision4++;

			if (visibility) {
				visibilityButton.setColor(
					sf::Color(255, 0, 0, 255 * collision4 / 20));
				if (collision4 == 20) {
					visibility = false;
				}
			}
			else {
				visibilityButton.setColor(
					sf::Color(0, 255, 0, 255 * collision4 / 20));
				if (collision4 == 20) {
					visibility = true;
				}
			}
		}
		else {
			collision4 = 0;
			if (visibility) {
				visibilityButton.setColor(sf::Color(0, 255, 0, 255));
			}
			else {
				visibilityButton.setColor(sf::Color(255, 0, 0, 255));
			}
		}

		cap.read(frame);
		windowWidth = window.getSize().x;
		windowHeight = window.getSize().y;
		weaponSprite.setScale(windowWidth / (weaponTexture.getSize().x * 10),
							  windowWidth / (weaponTexture.getSize().x * 10));

		updateWeaponPosition(frame, weaponSprite, windowWidth, windowHeight);

		window.clear();
		window.draw(backgroundSprite);
		window.draw(playButton);
		window.draw(optionsButton);
		window.draw(exitButton);
		window.draw(visibilityButton);
		window.draw(playText);
		window.draw(optionsText);
		window.draw(exitText);
		window.draw(titleText);
		window.draw(weaponSprite);
		window.draw(visibilityText);
		window.display();
	}
	return 0;
}

int runGame(sf::RenderWindow& window, cv::VideoCapture& cap,
			cv::Mat& referenceFrame)
{

	sf::Texture appleTexture, bilberryTexture, cherryTexture, basketTexture,
		weaponTexture, enemyTexture, antTexture, beetleTexture,
		backgroundTexture, treeholeTexture;
	if (!loadTextures(appleTexture, bilberryTexture, cherryTexture,
					  basketTexture, weaponTexture, enemyTexture, antTexture,
					  beetleTexture, backgroundTexture, treeholeTexture)) {
		return -3;
	}

	int windowWidth = window.getSize().x;
	int windowHeight = window.getSize().y;

	int score = 0;
	int lifes = 5;

	std::srand(std::time(nullptr));
	bool gameOver = false;
	float angle = 20.0f;
	int hit = 0;
	cv::Mat frame;

	sf::Music music;
	sf::Music gameover;

	if (!music.openFromFile("forest.ogg")) {
		std::cerr << "Nie można załadować pliku muzycznego!" << std::endl;
	}
	if (!gameover.openFromFile("gameover.ogg")) {
		std::cerr << "Nie można załadować pliku muzycznego!" << std::endl;
	}

	sf::Font font;
	if (!loadFont(font)) {
		return EXIT_FAILURE;
	}

	sf::Font bearpawFont;
	if (!bearpawFont.loadFromFile("BEARPAW_.ttf")) {
		std::cerr << "Failed to load BEARPAW_ font" << std::endl;
		return 0;
	}

	music.setLoop(true);
	music.play();

	sf::Text gameOverText =
		createText("Game Over", bearpawFont, windowWidth / 10, sf::Color::Red,
				   sf::Vector2f(windowWidth / 2 - windowWidth / 20,
								windowHeight / 2 - windowHeight / 60));
	gameOverText.setPosition(
		windowWidth / 2 - gameOverText.getLocalBounds().width / 2,
		windowHeight / 2 - gameOverText.getLocalBounds().height / 2);

	sf::Texture bodyTexture;
	sf::Sprite backgroundSprite(backgroundTexture);
	sf::Sprite basketSprite;
	sf::Sprite weaponSprite;
	sf::Sprite leftTreeholeSprite(treeholeTexture);
	sf::Sprite bodySprite;
	leftTreeholeSprite.setScale(
		windowWidth / (treeholeTexture.getSize().x * 10),
		windowWidth / (treeholeTexture.getSize().x * 10));
	leftTreeholeSprite.setPosition((windowWidth * leftTreeHolePosition.x / 640),
								   windowHeight * leftTreeHolePosition.y / 480);

	sf::Sprite rightTreeholeSprite(treeholeTexture);
	rightTreeholeSprite.setScale(
		windowWidth / (treeholeTexture.getSize().x * 10),
		windowWidth / (treeholeTexture.getSize().x * 10));
	rightTreeholeSprite.setPosition(
		(windowWidth * rightTreeHolePosition.x / 640),
		windowHeight * rightTreeHolePosition.y / 480);

	std::vector<sf::Sprite> enemySprites;
	std::vector<sf::Sprite> appleSprites;

	float direction = 10.0f;
	int randomFruit = 0;
	int randomEnemy = 0;

	createBasket(basketSprite, basketTexture, windowWidth, windowHeight);
	createWeapon(weaponSprite, weaponTexture, windowWidth, windowHeight);

	sf::Vector2f collisionVector(0, 0);
	int start = 0;

	while (window.isOpen()) {
		start++;
		processEvents(window, gameOver);

		cap.read(frame);

		if (frame.empty()) {
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		updateSpritesPosition(frame, basketSprite, weaponSprite, windowWidth,
							  windowHeight);

		if (lifes < 0) {
			gameOver = true;
		}

		if (gameOver) {

			window.clear();
			window.draw(backgroundSprite);
			window.draw(gameOverText);
			window.display();
			gameover.play();
			sf::sleep(sf::milliseconds(3000));
			return 0;
		}
		if (start > 20) {
			handleFruitAndEnemies(randomFruit, randomEnemy, appleSprites,
								  enemySprites, score, lifes, windowWidth,
								  windowHeight, basketSprite, weaponSprite,
								  direction, collisionVector, angle, hit,
								  appleTexture, bilberryTexture, cherryTexture,
								  antTexture, beetleTexture, enemyTexture);
		}

		window.clear();
		bodyTexture = drawBodyOnWindowTexture(frame, referenceFrame);
		bodySprite.setTexture(bodyTexture);
		bodySprite.setScale(
			windowWidth * 2 / static_cast<float>(backgroundTexture.getSize().x),
			windowHeight * 2 /
				static_cast<float>(backgroundTexture.getSize().y));
		bodySprite.setPosition(0, 0);

		backgroundSprite.setScale(
			windowWidth / static_cast<float>(backgroundTexture.getSize().x),
			windowHeight / static_cast<float>(backgroundTexture.getSize().y));
		backgroundSprite.setPosition(0, 0);
		window.draw(backgroundSprite);
		if (visibility) {
			window.draw(bodySprite);
		}
		window.draw(leftTreeholeSprite);
		window.draw(rightTreeholeSprite);

		if (start > 20) {

			for (const auto& appleSprite : appleSprites) {
				window.draw(appleSprite);
			}

			for (const auto& enemySprite : enemySprites) {
				window.draw(enemySprite);
			}
		}
		window.draw(basketSprite);
		window.draw(weaponSprite);

		sf::Text scoreText =
			createText("Score: " + std::to_string(score), font,
					   windowWidth / 30, sf::Color::White,
					   sf::Vector2f(windowWidth / 50, windowHeight / 30));
		sf::Text lifesText = createText(
			"Lifes: " + std::to_string(lifes), font, windowWidth / 30,
			sf::Color::Green,
			sf::Vector2f(windowWidth - windowWidth / 10, windowHeight / 30));
		scoreText.setPosition(10, 10);
		lifesText.setPosition(windowWidth - (windowWidth / 8) -
								  lifesText.getLocalBounds().width * 2,
							  windowHeight / 30);

		displayText(window, scoreText, "Score: " + std::to_string(score),
					sf::Vector2f(10, 10));
		displayText(
			window, lifesText, "Lives: " + std::to_string(lifes),
			sf::Vector2f(windowWidth - lifesText.getLocalBounds().width * 1.2,
						 windowHeight / 30));

		window.display();
	}
	return 0;
}

sf::Texture drawBodyOnWindowTexture(cv::Mat frame, cv::Mat referenceFrame)
{
	cv::Mat mask = bodySegmentation(frame, referenceFrame);
	sf::Image resultImage = matToSfImageWithTransparency(frame, mask);
	sf::Texture resultTexture;
	resultTexture.loadFromImage(resultImage);
	return resultTexture;
}
