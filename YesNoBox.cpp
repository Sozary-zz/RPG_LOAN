#include "YesNoBox.h"
#include <iostream>
using namespace std;

YesNoBox::YesNoBox(string first, string scd) :m_visible(false), m_actual_choice(0), m_choice_done(-1)
{
	m_font.loadFromFile("data/main_font.ttf");

	m_selector_choices[0] = sf::Vector2f(680, 415);
	m_selector_choices[1] = sf::Vector2f(680, 450);

	m_shape[0] = sf::RoundedRectangleShape(sf::Vector2f(100, 100), 5, 20);
	m_shape[0].setPosition(sf::Vector2f(660, 400));
	m_texture.loadFromFile("data/texture.png");
	m_shape[0].setTexture(&m_texture);

	m_shape[1] = sf::RoundedRectangleShape(sf::Vector2f(80, 80), 5, 20);
	m_shape[1].setPosition(sf::Vector2f(670, 410));
	m_shape[1].setFillColor(sf::Color(190, 190, 190));

	update(first, scd);
}




YesNoBox::~YesNoBox()
{

}

void YesNoBox::setText(std::string a, std::string b)
{
	update(a, b);
}

void YesNoBox::up()
{
	m_actual_choice = 0; choiceChange();
}

void YesNoBox::down()
{
	m_actual_choice = 1; choiceChange();
}

void YesNoBox::setVisible(bool b)
{
	m_visible = b;
}

void YesNoBox::setResult() // a un moment, le joueur va cliquer sur entrer, ce qui verouillera la pos actual du curseur
{
	m_choice_done = m_actual_choice;

}

int YesNoBox::getResult() const
{
	return m_choice_done;
}

void YesNoBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{


	if (m_visible)
	{
		target.draw(m_shape[0]);
		target.draw(m_shape[1]);
		target.draw(m_d_text[0]);
		target.draw(m_d_text[1]);
		target.draw(m_selector);
	}

}

void YesNoBox::update(string a, string b)
{



	m_d_text[0].setFont(m_font); m_d_text[1].setFont(m_font);
	m_d_text[0].setColor(sf::Color(0, 0, 0)); m_d_text[1].setColor(sf::Color(0, 0, 0));
	m_d_text[0].setPosition(m_selector_choices[0]); m_d_text[1].setPosition(m_selector_choices[1]);
	m_d_text[0].setCharacterSize(setFontSize(a)); m_d_text[1].setCharacterSize(setFontSize(b));
	m_d_text[0].setString(a); m_d_text[1].setString(b);

	m_selector = sf::RoundedRectangleShape(sf::Vector2f(m_d_text[m_actual_choice].getGlobalBounds().width, 5), 5, 5);
	choiceChange();
	m_selector.setFillColor(sf::Color(255, 0, 0));
}

void YesNoBox::choiceChange()
{

	m_selector.setPosition(sf::Vector2f(m_selector_choices[m_actual_choice].x, m_selector_choices[m_actual_choice].y + m_d_text[m_actual_choice].getGlobalBounds().height*1.5));
}
