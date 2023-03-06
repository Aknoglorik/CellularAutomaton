#pragma once
#include <SFML/Graphics.hpp>

namespace gui
{

	class Slider : public sf::Drawable, public sf::Transformable
	{
	public:

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
	};

}