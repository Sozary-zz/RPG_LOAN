#pragma once
#include "Ovale.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <sstream>

#define MAX_WIDTH 40

class MsgBox :public sf::Drawable, public sf::Transformable
{
public:
	MsgBox();
	MsgBox(std::string);
	~MsgBox();

	void setString(std::string);
	void setVisible(bool);
	bool next_frame();
	bool haveBeenVisible() const;

private:
	sf::RoundedRectangleShape m_shape[2];
	sf::CircleShape m_next_arrow;
	std::vector<std::string> m_text;
	bool m_visible;
	bool m_first_show;
	bool m_display_next_arrow;
	sf::Text m_d_text[2];
	sf::Font m_font;
	sf::Texture m_texture;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(std::string);
	void formatText(std::string);
	std::vector<std::string> split(std::string) const;
};

