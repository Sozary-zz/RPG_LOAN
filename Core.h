#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "MsgBox.h"
#include "YesNoBox.h"

enum STATES { WAIT_FOR_BEGIN, GAME_BEGIN, CLASSE_CHOICE };

struct Package
{
	STATES state;
	std::vector<sf::Texture> texture;
	std::vector<sf::Image> picture;
	std::vector<sf::Sprite> sprite;
	std::vector<sf::SoundBuffer> b_sound;
	std::vector<sf::Sound> sound;
	std::vector<std::string> v_str;
	std::vector<double> v_double;
	std::vector<int> v_int;
	std::vector<bool> flag;
	MsgBox* msgBox;
	YesNoBox* yesNo;
};

class Core
{

public:
	Core();
	Package* launchState(STATES, float, float);
	void handleState(STATES&, Package*)const;
	~Core();
private:
	STATES m_state;
private:
	std::string getScriptById(double) const;

};

