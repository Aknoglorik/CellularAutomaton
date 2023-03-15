#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace gui
{
	enum _status
	{
		_default = 0,
		_hovered = 1,
		_clicked = 2
	};

	void setByStat(_status);

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

		void setString(sf::String);

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
		void update(sf::RenderWindow&);
		void bind(std::function<void(void)>);

	private:
		void setByStat(_status);
	};

}