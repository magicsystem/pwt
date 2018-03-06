/*
 * Menu.h
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_MENU_H_
#define INCLUDE_PWT_WIDGETS_MENU_H_
#include "MenuItem.h"
namespace pwt {
class MenuBar;
class Menu : public MenuItem {
public:
	Menu();
	~Menu();
	virtual void create(MenuBar* bar);
};

class PopupMenu : public Menu {
public:
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_WIDGETS_MENU_H_ */
