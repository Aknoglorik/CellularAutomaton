#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "GObject.hpp"


namespace gui
{
	class Label;

	class Button : public GObject
	{
		std::function<void(void)> m_callback = [](){};

		sf::FloatRect size;
		sf::RectangleShape rectangle;

		Label *label = nullptr;
		bool isPressed = false;
		bool isHovered = false;
		bool isClickedOnThis = false;

	public:
		Button(sf::FloatRect size, const sf::Font &font, sf::String str = "Button");
		~Button();

		void setString(sf::String);

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
		void update(sf::RenderWindow&) override;
		void bind(std::function<void(void)>);
		void setAnc(Anchor anc) override;

	private:
		void setByStat(int);
	};

}