/*
 * Container.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_CONTAINER_H_
#define INCLUDE_PWT_WIDGETS_CONTAINER_H_
#include "Component.h"
namespace pwt {
class ContainerPeer;
class PUBLIC Container : public Component {
protected:
	ComponentPeer* getComponentPeer();
	virtual ContainerPeer* getContainerPeer();
public:
	Container();
	~Container();
	void add(Component* c);
};
}  // namespace pwt
#endif /* INCLUDE_PWT_WIDGETS_CONTAINER_H_ */
