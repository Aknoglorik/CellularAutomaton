#pragma once
#include <SFML/Graphics.hpp>

namespace gui
{

	class Slider : public sf::Drawable, public sf::Transformable
	{
		int max_value;


	public:

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
	};

}