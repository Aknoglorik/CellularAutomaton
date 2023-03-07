#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

namespace gui
{

	class Button : public sf::Drawable, public sf::Transformable
	{
		std::function<void(void)> m_callback;

		sf::FloatRect size;
		sf::RectangleShape rectangle;

		/// \brief default = 0, hovered = 1, clicked = 2
		/// \brief *FIXME! rename*
		short myStatus; 
		

	public:
		Button(sf::FloatRect size);

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
		void update(sf::RenderWindow&);
		void bind(std::function<void(void)>);
	};

}