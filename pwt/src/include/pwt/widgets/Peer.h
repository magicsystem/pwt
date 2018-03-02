/*
 * Peer.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_PEER_H_
#define INCLUDE_PWT_WIDGETS_PEER_H_
#include "Component.h"
namespace pwt {
class Toolkit;
class Container;
class ComponentPeer: public IDestruct {
public:
	static inline void* getReserved(Component* c) {
		return c->handles;
	}
	static inline ComponentPeer* getPeer(Component* c) {
		return c->getComponentPeer();
	}
	static inline void sendEvent(Component* c, Event* e) {
		c->postEvent(e);
	}
	static inline void sendPlatformEvent(Component* c, PlatformEvent* e) {
		c->postPlatformEvent(e);
	}
	static inline void paint(Component* c,Graphics* gc){
		c->paint(*gc);
	}
	virtual void create(Component* c, Container* parent)=0;
	virtual void dispose(Component* c)=0;
	virtual Toolkit* getToolkit()=0;
	virtual void setVisible(Component* c, bool b)=0;
	virtual void setBounds(Component* c, Rectangle& r)=0;
	virtual void getBounds(Component* c, Rectangle& r)=0;
	virtual void postEvent(Component* c, Event* e)=0;
	virtual void postPlatformEvent(Component* c, PlatformEvent* e)=0;
	virtual void paint(Component* c,Graphics& g)=0;
	virtual void update(Component* c,Graphics& g)=0;
	virtual void print(Component* c,Graphics& g)=0;
	virtual void repaint(Component* c)=0;
	virtual void repaint(Component* c,Rectangle& r)=0;
	virtual void getGraphics(Component* c,Graphics& g)=0;
};
class ButtonPeer: public virtual ComponentPeer {
public:
	virtual String getLabel(Component* c)=0;
	virtual void setLabel(Component* c, String label)=0;
};
class CanvasPeer: public virtual ComponentPeer {

};
class ContainerPeer: public virtual ComponentPeer {
public:

};

class WindowPeer: public virtual ContainerPeer {
public:

};

class FramePeer: public virtual WindowPeer {
public:
	virtual const char* getTitle(Component* f)=0;
	virtual void setTitle(Component* f, String title)=0;
	virtual bool isResizable(Component* f)=0;
	virtual void setResizable(Component* f, bool resizable)=0;
	virtual void setState(Component* f, int state)=0;
	virtual int getState(Component* f)=0;
	virtual void setMaximizedBounds(Component* f, Rectangle& bounds)=0;
	virtual void getMaximizedBounds(Component* f, Rectangle& bounds)=0;
};
}  // namespace pwt

#endif /* INCLUDE_PWT_WIDGETS_PEER_H_ */
