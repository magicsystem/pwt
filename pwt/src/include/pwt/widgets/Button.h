/*
 * Button.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_BUTTON_H_
#define INCLUDE_PWT_WIDGETS_BUTTON_H_
#include "Component.h"
namespace pwt {
class ButtonPeer;
class PUBLIC Button: public Component {
private:
	const char* label;
public:
	Button();
	Button(Container* parent);
	~Button();
	void create(Container* parent);
	String getLabel();
	void setLabel(const String& label);
};
}  // namespace pwt
#endif /* INCLUDE_PWT_WIDGETS_BUTTON_H_ */
