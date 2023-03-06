#pragma once
#include <SFML/Graphics.hpp>

namespace gui
{

	class Button : public sf::Drawable, public sf::Transformable
	{
		sf::RectangleShape rectangle;

	public:
		Button(sf::IntRect size);

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
	};

}