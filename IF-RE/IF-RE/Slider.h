#pragma once
#include <SFML/Graphics.hpp>
#include "GObject.hpp"


namespace gui
{

	class Slider : public GObject
	{
		int max_value;
		int value;
		float circle_radius;

		sf::FloatRect hitbox;
		sf::RectangleShape line1, line2;
		sf::CircleShape circle;

		bool isPressed = false;
		bool isHovered = false;
		bool isClickedOnThis = false;

	public:
		Slider(sf::Vector2f p1, sf::Vector2f p2, float height, int start_value = 0, int _max_value = 100);
		~Slider();

		void setByStat(int status);

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
		void update(sf::RenderWindow&) override;

		void setValue(int val);
		int getValue() { return value; }

	private:
		void setupByPos(sf::Vector2f pos);
	};

}