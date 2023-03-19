#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace gui
{
	class Label;

	class Button : public sf::Drawable, public sf::Transformable
	{
		std::function<void(void)> m_callback = [](){};

		sf::FloatRect size;
		sf::RectangleShape rectangle;

		Label *label;
		bool isPressed = false;
		bool isHovered = false;
		bool isClickedOnThis = false;

	public:
		Button(sf::FloatRect size, const sf::Font &font, sf::String str = "Button");
		~Button();

		void setString(sf::String);

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
		void update(sf::RenderWindow&);
		void bind(std::function<void(void)>);

	private:
		void setByStat(int);
	};

}