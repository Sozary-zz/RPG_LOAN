#pragma once
#include <math.h>
#include <vector>
#include "Core.h"
#include "YesNoBox.h"

class Game
{
public:
	Game();
	~Game();
	void run();


private:
	sf::RenderWindow mWindow;
	Core* m_core;
	Package* m_data;
	STATES m_state;

private:
	const sf::Time TimePerFrame;

private:
	void processEvent();
	void update(sf::Time);
	void render();

};
double distanceEuclidienne(sf::Vector2f, sf::Vector2f);


