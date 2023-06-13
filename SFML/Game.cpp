#include "Game.h"
void Game::initFonts()
{
	if (!(this->font.loadFromFile("Fonts/Dosis-Light.ttf")))
	{
		std::cout << "ERROR::GAME::INITFONTS::Fail to load font!" <<std::endl;
	}
}
//declare a window
void Game::initVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->health = 20;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHold = false;
	this->endGame = false;
}
//set up attribute for window
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(videoMode, "SFML Application", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}
void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(20);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}
//set up attribute for enemies
void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(0.5f, 0.5f);
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}
//contructor
Game::Game()
{
	
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
}
//destructor
Game::~Game()
{
	delete this->window;
}
//check if game is still running
const bool Game::running() const
{
	return this->window->isOpen();
}
const bool Game::getEndGame() const
{
	return this->endGame;
}
void Game::spawnEnemies()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	//Randomise enemy type
	int type = rand() % 5;
	
	if(type == 0)
	{
		this->enemy.setSize(sf::Vector2f(10.f, 10.f));
		this->enemy.setFillColor(sf::Color::Magenta);
	}
	else if (type == 1)
	{
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		this->enemy.setFillColor(sf::Color::Blue);
	}
	else if (type == 2)
	{
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
	}
	else if (type == 3)
	{
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		this->enemy.setFillColor(sf::Color::Red);
	}
	else if (type == 4)
	{
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Green);
	}
	else
	{
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Yellow);
	}
	//spawn the enemy
	this->enemies.push_back(enemy);
	//Remove enemy at the end of the screen
}
//handle the event
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}
//update mouse position
void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
void Game::updateEnemies()
{
	//updating the timer for enemies spawning
	if (enemies.size() < maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemies and reset the timer
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}

		else
		{
			this->enemySpawnTimer += 1.f;
		}
			
	}
	//Moving and updating enemies
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		enemies[i].move(0.f, 5.f);
		bool deleted = false;
		if (this->enemies[i].getPosition().y >= this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			
		}
	}
	//check if click upon
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (this->mouseHold == false )
		{
			bool deleted = false;
			this->mouseHold = true;
			for (int i = 0; i < this->enemies.size() && deleted == false; ++i)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					if (this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 7;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 3;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 1;
					//delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
					//Gain points
					
					
				}
			}
		}
		
	}
	else
	{
		this->mouseHold = false;
	}
	
}
void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << "\n"
	   << "Health: " << this->health << "\n";
	this->uiText.setString(ss.str());
}
//update window
void Game::update()
{
	this->pollEvents();
	if (this->endGame == false)
	{
		this->updateMousePosition();
		this->updateText();
		this->updateEnemies();
	}
	//Endgame condition
	if (this->health <= 0)
	{
		this->endGame = true;
	}

}
void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}
void Game::renderEnemies(sf::RenderTarget& target)
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}
//draw every on window
void Game::render()
{
	
	this->window->clear();//Clear old frame

	//Draw your game
	//this->window->draw(this->enemy);
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();//Telling app that window is drawing

}
