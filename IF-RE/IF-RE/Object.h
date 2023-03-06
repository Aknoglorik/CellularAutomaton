#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Object : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Vector2i position;

	// Vars for RenderTarget
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::VertexArray m_vertices;

public:

	Object();
	virtual ~Object();

	virtual void update() {};

	void setPos(sf::Vector2i newPos) { position = newPos; }
	void setPos(int x, int y) { position = sf::Vector2i(x, y); }
	void setTexture(sf::Texture& new_texture) { m_texture = new_texture; }

	sf::Vector2i getPos() const { return position; }

	void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

