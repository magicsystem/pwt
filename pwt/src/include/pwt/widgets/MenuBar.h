/*
 * MenuBar.h
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_MENUBAR_H_
#define INCLUDE_PWT_WIDGETS_MENUBAR_H_
#include "MenuComponent.h"
#include "Container.h"
namespace pwt {

class MenuBar :public MenuComponent {
public:
	MenuBar();
	~MenuBar();
	virtual void create(Container* parent);
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_WIDGETS_MENUBAR_H_ */
