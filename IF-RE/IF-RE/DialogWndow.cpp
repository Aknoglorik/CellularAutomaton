#include "DialogWndow.h"


gui::DialogWndow::DialogWndow(sf::Vector2f pos, sf::Vector2f _size, sf::Font& font, sf::RenderWindow& _root) : root(_root)
{
	// help
	s_brain = "00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00\n00 00 00 00 00 00 00 00\n";
	s_extra_info = "???\n???\n???\n???";

	setPosition(pos);

	bg.setSize(_size);
	bg.setFillColor(Color::DarkGray);

	currentCmd.setSize(sf::Vector2f(DLG_LB_SIZE + DLG_CMD_MARGIN, DLG_LB_SIZE + DLG_CMD_MARGIN));
	currentCmd.setPosition(cmdDefaultPos);
	currentCmd.setFillColor(Color::White1);

	selectedBot.setSize(sf::Vector2f(DLG_LB_SIZE + DLG_CMD_MARGIN, DLG_LB_SIZE + DLG_CMD_MARGIN));
	selectedBot.setFillColor(Color::Yellow);
	selectedBot.setPosition(cmdDefaultPos);


	lb_brain = new Label(pos + sf::Vector2f(DLG_HEAD_BAR/4, DLG_HEAD_BAR + 20), DLG_LB_SIZE);
	lb_brain->setFont(font);
	lb_brain->setColor(sf::Color::White);
	lb_brain->setDynamicString(s_brain);

	lb_extra_info = new Label(pos + sf::Vector2f(DLG_HEAD_BAR/4, DLG_HEAD_BAR + DLG_LB_SIZE * 12), DLG_LB_SIZE);
	lb_extra_info->setFont(font);
	lb_extra_info->setColor(sf::Color::White);
	lb_extra_info->setDynamicString(s_extra_info);


	head_hitbox.width = _size.x;
	head_hitbox.top = DLG_HEAD_BAR;

	btn_close = new Button(sf::FloatRect(pos.x + _size.x - DLG_HEAD_BAR, pos.y, DLG_HEAD_BAR, DLG_HEAD_BAR), font, "X");
	btn_close->bind([&]()
		{
			do_it_close = true;
		});
	btn_head = new Button(sf::FloatRect(pos.x, pos.y, _size.x, DLG_HEAD_BAR), font, " X");
	btn_head->bind([&]() // FIXME!
		{
			sf::Vector2i m_pos = sf::Mouse::getPosition(root);
			sf::Vector2f pos = root.mapPixelToCoords(m_pos);
			setPosition(pos - sf::Vector2f(head_hitbox.width / 2, DLG_HEAD_BAR / 2));

			btn_head->move(pos - btn_head->getPosition() - sf::Vector2f(head_hitbox.width / 2, DLG_HEAD_BAR / 2));
			btn_close->move(pos - btn_close->getPosition() - sf::Vector2f(-head_hitbox.width / 2 + DLG_HEAD_BAR, DLG_HEAD_BAR / 2));

			lb_brain->move(pos - lb_brain->getPosition() - sf::Vector2f(head_hitbox.width / 2, DLG_HEAD_BAR / 2));
			lb_extra_info->move(pos - lb_extra_info->getPosition() - sf::Vector2f(head_hitbox.width / 2, DLG_HEAD_BAR / 2));
		});
	btn_head->setMultiClick(true);

}

gui::DialogWndow::~DialogWndow()
{
	delete btn_close;
	delete btn_head;
	delete lb_brain;
	delete lb_extra_info;
}

void gui::DialogWndow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(bg, states);
	target.draw(currentCmd, states);

	target.draw(*btn_close, states);
	target.draw(*lb_brain, states);
	target.draw(*lb_extra_info, states);

}

void gui::DialogWndow::update(sf::RenderWindow& target)
{
	updateBotInfo();
	lb_brain->update(target);
	lb_extra_info->update(target);

	bool isClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	sf::Vector2i m_pos = sf::Mouse::getPosition(target);
	sf::Vector2f pos = target.mapPixelToCoords(m_pos);
	head_hitbox.left = getPosition().x;
	head_hitbox.top = getPosition().y;
	btn_close->update(target);
	btn_head->update(target);
	// if window was resized.. mb
	//setPosition(getPosition().x - getOrigin().x, getPosition().y - getOrigin().y);
}

void gui::DialogWndow::updateBotInfo()
{
	if (currentObj && currentObj->isDie())
	{
		currentObj = nullptr;
		s_extra_info = "???\n???\n???\n???";
	}
	if (currentObj)
	{
		s_brain = "";
		std::vector<int>& r_brain = currentObj->getBrain();
		for (int i = 0; i < r_brain.size(); i++)
		{
			if (!(i % 8) && i)
				s_brain += '\n';
			if (r_brain[i] < 10)
				s_brain += ' ';
			s_brain += std::to_string(r_brain[i]) + ' ';
		}

		s_extra_info = "Cmd counter:      " + std::to_string(currentObj->getCmdCounter());
		s_extra_info += "\nLife counter: \t" + std::to_string(currentObj->getLifeCounter());
		s_extra_info += "\nEnergy:       \t" + std::to_string(currentObj->getEnergy());
		s_extra_info += "\nDigested mat: \t" + std::to_string(currentObj->getDigestedMaterial());
		
		int x = currentObj->getCmdCounter() % 8;
		int y = currentObj->getCmdCounter() / 8;

		currentCmd.setPosition(cmdDefaultPos + sf::Vector2f(x * 24, y * 17));
	}
}
