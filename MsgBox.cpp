#include "MsgBox.h"
#include <iostream>

using namespace std;

MsgBox::MsgBox() :m_visible(false), m_display_next_arrow(false), m_first_show(false)
{
}


MsgBox::MsgBox(string str) : m_visible(false), m_display_next_arrow(false), m_first_show(false)
{
	update(str);
}

MsgBox::~MsgBox()
{

}

void MsgBox::setString(string str)
{
	update(str);
}

void MsgBox::setVisible(bool v)
{
	if (!m_first_show)
		m_first_show = true;
	m_visible = v;
}

bool MsgBox::next_frame()
{
	switch (m_text.size())
	{
	case 0:
		m_display_next_arrow = false;
		m_visible = false;

		return false;

	case 1:
		m_display_next_arrow = false;
		m_d_text[0].setString(m_text[0]); m_text.erase(m_text.begin()); m_d_text[1].setString("");
		break;

	case 2:
		m_display_next_arrow = false;
		m_d_text[0].setString(m_text[0]); m_text.erase(m_text.begin()); m_d_text[1].setString(m_text[0]); m_text.erase(m_text.begin());
		break;

	default:
		m_display_next_arrow = true;
		m_d_text[0].setString(m_text[0]); m_text.erase(m_text.begin()); m_d_text[1].setString(m_text[0]); m_text.erase(m_text.begin());
		break;
	}
	return true;
}

bool MsgBox::haveBeenVisible() const
{
	return m_first_show;
}


void MsgBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	if (m_visible)
	{
		target.draw(m_shape[0]);
		target.draw(m_shape[1]);
		target.draw(m_d_text[0]);
		target.draw(m_d_text[1]);

		if (m_display_next_arrow)
			target.draw(m_next_arrow);
	}

}

void MsgBox::update(string str)
{

	// perso je trouve ça top

	/*m_shape[0] = sf::RoundedRectangleShape(sf::Vector2f(720, 100), 5, 20);
	m_shape[0].setPosition(sf::Vector2f(40, 525));
	m_shape[0].setFillColor(sf::Color(0, 200, 184));
	m_shape[0].setOutlineThickness(5);
	m_shape[0].setOutlineColor(sf::Color(0, 248, 152));

	m_shape[1] = sf::RoundedRectangleShape(sf::Vector2f(700, 100), 5, 20);
	m_shape[1].setPosition(sf::Vector2f(50, 525));
	m_shape[1].setFillColor(sf::Color(255, 255,255));*/

	m_shape[0] = sf::RoundedRectangleShape(sf::Vector2f(720, 100), 5, 20);
	m_shape[0].setPosition(sf::Vector2f(40, 525));
	//	m_shape[0].setFillColor(sf::Color(0, 200, 184));
	//	m_shape[0].setOutlineThickness(5);
		//m_shape[0].setOutlineColor(sf::Color(0, 248, 152));
	m_texture.loadFromFile("data/texture.png");
	m_shape[0].setTexture(&m_texture);

	m_shape[1] = sf::RoundedRectangleShape(sf::Vector2f(700, 80), 5, 20);
	m_shape[1].setPosition(sf::Vector2f(50, 535));
	m_shape[1].setFillColor(sf::Color(190, 190, 190));

	m_next_arrow.setRadius(20);
	m_next_arrow.rotate(180);
	m_next_arrow.setFillColor(sf::Color::Red);
	m_next_arrow.setPointCount(3);
	m_next_arrow.setPosition(sf::Vector2f(720, 590));

	string buffer = "";
	int iIndex = 0;

	while (iIndex < str.size()) {
		bool back = (str[iIndex] == '|' && str[iIndex + 1] == 'n');
		if (buffer.size() >= MAX_WIDTH || back) {

			m_text.push_back(buffer);
			buffer.clear();
			if (back)
				iIndex += 2;
		}
		buffer += str[iIndex++];

	}
	m_text.push_back(buffer);

	m_font.loadFromFile("data/main_font.ttf");



	m_d_text[0].setFont(m_font); m_d_text[1].setFont(m_font);
	m_d_text[0].setColor(sf::Color(0, 0, 0)); m_d_text[1].setColor(sf::Color(0, 0, 0));
	m_d_text[0].setPosition(sf::Vector2f(60, 535)); m_d_text[1].setPosition(sf::Vector2f(60, 580));
	m_d_text[0].setCharacterSize(25); m_d_text[1].setCharacterSize(25);

	next_frame();
}

void MsgBox::formatText(string str)
{
	int iIndex = 0;
	string buffer = "";

	while (iIndex < str.size()) {
		bool back = (str[iIndex] == '|' && str[iIndex + 1] == 'n');
		if (buffer.size() >= MAX_WIDTH || back) {

			m_text.push_back(buffer);
			buffer.clear();
			if (back)
				iIndex += 2;
		}
		buffer += str[iIndex++];

	}
	m_text.push_back(buffer);
}

vector<string> MsgBox::split(string s) const
{
	vector<string> res;

	istringstream iss(s);

	do
	{
		string sub;
		iss >> sub;
		res.push_back(sub);
	} while (iss);

	return res;
}
