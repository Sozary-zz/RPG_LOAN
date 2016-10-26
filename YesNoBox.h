#pragma once
#include "Ovale.hpp"
#include <SFML/Graphics.hpp>
#include <string>

#define setFontSize(a) -.93 * a.size() + 24.33


class YesNoBox :public sf::Drawable, public sf::Transformable
{
public:
	YesNoBox(std::string first = std::string("Oui"), std::string scd = std::string("Non"));
	~YesNoBox();
	void setText(std::string, std::string);
	void up();
	void down();
	void setVisible(bool);
	void setResult();
	int getResult() const;

private:
	bool m_visible;
	sf::RoundedRectangleShape m_shape[2];
	sf::Texture m_texture;
	sf::Text m_d_text[2];
	sf::Font m_font;
	sf::RoundedRectangleShape m_selector;
	sf::Vector2f m_selector_choices[2];
	int m_actual_choice;
	int m_choice_done;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(std::string, std::string);
	void choiceChange();
};

