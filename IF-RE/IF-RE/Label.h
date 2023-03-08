#pragma once
#include <SFML/Graphics.hpp>


namespace gui
{

	class Label : public sf::Drawable, public sf::Transformable
	{
		sf::Vector2f pos;
		sf::String* m_string;
		sf::Text text;

	public:
		Label();
		Label(sf::Vector2f, unsigned int size);

		void setFont(const sf::Font &);
		void setString(sf::String);
		void setColor(sf::Color);
		void setCharSize(unsigned int size);

		/// \param str - string that can be changed outside this method 
		///		 CANN'T BE DELETED EARLIER THAN THIS ENTITY!
		void setDynamicString(sf::String& str);

		void draw(sf::RenderTarget&, sf::RenderStates) const override;
		void update();
	};

}

