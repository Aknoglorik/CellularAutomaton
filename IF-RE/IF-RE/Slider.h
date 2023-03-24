#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "GObject.hpp"


namespace gui
{

	class Slider : public GObject
	{
		int max_value;
		int min_value;
		int value;
		float circle_radius;

		sf::FloatRect hitbox;
		sf::RectangleShape line1, line2;
		sf::CircleShape circle;

		bool isPressed = false;
		bool isHovered = false;
		bool isClickedOnThis = false;
		std::function<void(int)> m_callback;
		

	public:
		Slider(sf::Vector2f p1, sf::Vector2f size, int start_value = 50, int _min_value = 0, int _max_value = 100, std::function<void(int)> callback = [](int) {});
		~Slider();

		void setByStat(int status);

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
		void update(sf::RenderWindow&) override;

		void setValue(int val);
		int getValue() { return value; }

		void bind(std::function<void(int)> callback) { m_callback = callback; }

	private:
		void setupByPos(sf::Vector2f pos);
	};

}