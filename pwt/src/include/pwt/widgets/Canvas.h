/*
 * Canvas.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_CANVAS_H_
#define INCLUDE_PWT_WIDGETS_CANVAS_H_
#include "Component.h"
namespace pwt {
class CanvasPeer;
class PUBLIC Canvas: public Component {
public:
	Canvas();
	~Canvas();
	void create(Container* parent);
};
}  // namespace pwt
#endif /* INCLUDE_PWT_WIDGETS_CANVAS_H_ */
