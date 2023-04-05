#pragma once
#include "GObject.hpp"
#include "ExtraColors.hpp"
#include <iostream>
#include <vector>
#include <fstream>

class DLGGraph : public gui::GObject
{
	sf::VertexArray pts;
	std::vector<sf::Vector2f> pttts;
	sf::Vector2f size;
	sf::Vector2f factor;
	sf::Vector2f rev_factor;
	sf::RectangleShape bg;
	std::ofstream file;
	sf::Vector2f pos;

public:
	bool draw_it = false;
	
	DLGGraph(sf::Vector2f s, sf::Vector2f p) : size(s), pos(p)
	{
		bg.setSize(s);
		bg.setFillColor(gui::Color::DarkGray);

		//setOrigin(-pos.x, -pos.y - size.y);

		factor.x = 1;
		factor.y = 1;
		rev_factor.x = 6;
		rev_factor.y = 6;
		pts = sf::VertexArray(sf::LineStrip);
		setPosition(p);
		AddPoint(sf::Vector2f(0, 0));
		file.open("graph.txt", std::ios_base::app);
	}
	~DLGGraph()
	{
		//delete pts;
		file.close();
	}
	void AddPoint(sf::Vector2f position) 
	{
		//if (getCount() == 2)
		//{
		//	//factor.x = position.x / size.x;
		//	//rev_factor.x = 1 / factor.x;
		//	//
		//	//factor.x = position.y / size.y;
		//	//rev_factor.y = 1 / factor.y;

		//	//setScale(rev_factor);
		//}
		//else
		//{
		//	if (pos.x > size.x * factor.x)
		//	{
		//		factor.x = position.x / size.x;
		//		rev_factor.x = 1 / factor.x;
		//		//setScale(rev_factor);
		//	}
		//	if (pos.y > size.y * factor.y)
		//	{
		//		factor.x = position.y / size.y;
		//		rev_factor.y = 1 / factor.y;
		//		//setScale(rev_factor);
		//	}
		//}
		////position.y = size.y - position.y;

		//std::cout << position.x << ' ' << position.y << std::endl;
		position.x *= 4;
		position.y *= 4;
		pts.append(sf::Vertex(position, sf::Color::Red));


		file << position.x << ' ' << position.y;

		pttts.push_back(position);

	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		if (!draw_it)
			return;


		auto dist = [&](sf::Vector2f p1, sf::Vector2f p2) -> float{ return powf(powf((p1.x - p2.x), 2) + powf((p1.y - p2.y), 2), 0.5); };


		states.transform *= getTransform();
		//sf::VertexArray arr(sf::LinesStrip); 
		//arr.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::Red));
		//arr.append(sf::Vertex(sf::Vector2f(size.x, size.y), sf::Color::Red));
		//target.draw(arr, states);
		//sf::RectangleShape line;
		//line.setFillColor(sf::Color::Red);

		//for (int i = 1; i < pttts.size(); ++i)
		//{
		//	//std::cout  << rev_factor.x << ' ' << rev_factor.y << std::endl;
		//	line.setPosition(pttts[i-1].x * rev_factor.x , pttts[i - 1].y * rev_factor.y);
		//	float ssize = dist(pttts[i - 1] * rev_factor.x, pttts[i] * rev_factor.y);

		//	line.setSize(sf::Vector2f(ssize, 1)); // 4 - tikknet 
		//	
		//	float d_y = pttts[i].y - pttts[i - 1].y;
		//	float d_x = pttts[i].x - pttts[i - 1].x;
		//	
		//	std::cout << atan2f(-d_y * rev_factor.y, d_x * rev_factor.x) << std::endl;
		//	line.setRotation(-atan2f(-d_y * rev_factor.y, d_x * rev_factor.x));
		//	target.draw(line, states);
		////}
		//target.draw(bg, states);
		target.draw(pts, states);
	}
	void update(sf::RenderWindow& target) override
	{
		setAnc(_anchor);
	}
	int getCount() 
	{ 
		return pts.getVertexCount();
	}
};

