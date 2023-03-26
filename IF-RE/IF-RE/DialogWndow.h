#pragma once

#include "consts.h"
#include "GObject.hpp"
#include "Bot.h"

#include "ExtraColors.hpp"
#include "Button.h"
#include "Label.h"


namespace gui
{
	class DialogWndow : public GObject
	{
		sf::RenderWindow& root;
		sf::RectangleShape bg, currentCmd;
		sf::Vertex* line;
		sf::Vector2f cmdDefaultPos = sf::Vector2f(DLG_HEAD_BAR / 4 - DLG_CMD_MARGIN / 2, DLG_HEAD_BAR + 20 - DLG_CMD_MARGIN / 2);
		Button* btn_close, * btn_head;
		sf::FloatRect head_hitbox;

		Bot* currentObj = nullptr;
		gui::Label* lb_brain = nullptr;
		gui::Label* lb_extra_info = nullptr;

		sf::String s_brain;
		sf::String s_extra_info;

		bool headerPressed = false;

	public:
		DialogWndow(sf::Vector2f pos, sf::Vector2f _size, sf::Font& font, sf::RenderWindow& _root);
		~DialogWndow();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual  void update(sf::RenderWindow& target) override;
		
		sf::FloatRect getHitBox() { return sf::FloatRect(getPosition(), bg.getSize()); }

		void setCurrentObj(Bot* bot) { currentObj = bot; }
		Bot*& getCurrentObj() { return currentObj; }

		void updateBotInfo();
	};
}
