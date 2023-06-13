#pragma once

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
/*
	Class acts as the game engine
	Wrapper class
*/

class Game
{
private:
	//Window
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event ev;
	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHold;
	//Resource
	sf::Font font;
	//Text
	sf::Text uiText;
	//Game objects
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	std::vector <sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	//Private function
	void initFonts();
	void initVariables();
	void initWindow();
	void initText();
	void initEnemies();
	
public:
	//Constructor and Destructor
	Game();
	virtual ~Game();
	const bool running() const;
	const bool getEndGame() const;

	void spawnEnemies();
	void pollEvents();

	void updateMousePosition();
	void updateEnemies();
	void updateText();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};

#endif 



