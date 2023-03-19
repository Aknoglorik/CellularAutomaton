#pragma once
#include <SFML/Graphics.hpp>


namespace gui
{
	class GObject : public sf::Drawable, public sf::Transformable
	{
	protected:

	public:
		GObject() {}
		virtual ~GObject() {}


		virtual void draw(sf::RenderTarget&, sf::RenderStates) const override {};
		virtual void update(sf::RenderWindow&) {};
	};
}
