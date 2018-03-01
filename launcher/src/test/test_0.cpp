/*
 * test_0.cpp
 *
 *  Created on: 9 févr. 2018
 *      Author: azeddine
 */
#include <pwt.h>
#include <stdio.h>
using namespace pwt;

class TestCanvas: public Canvas {
public:
	void paint(Graphics& gc) {
		Rectangle bounds;
		getBounds(bounds);
		//gc.fillRect(10,10,100,50);
		gc.setForeground(Color::gray);
		gc.setLineWidth(1);
		//gc.setLineStyle(Graphics::LINE_DASHDOT);
		gc.setLineCap(Graphics::CAP_FLAT);
		gc.drawRect(0,0,bounds.width,bounds.height);
		gc.drawArc(0,0,bounds.width,bounds.height,0,-90);
		gc.setForeground(Color(0));
		gc.drawString("EL BASSBASI AZEDDINE",10,10);

	}
	void postEvent(Event* e) {
		if (e->clazz == Event::PAINT_EVENT) {
			PaintEvent* ee = (PaintEvent*) e;
			paint(*ee->gc);
		}

	}

};

class TestFrame: public Frame {
public:
	TestCanvas canvas;
	Button button;
	TestFrame() {
		create();
		//canvas.create(this);
		//button.create(this);
		add(&canvas);
		add(&button);
	}
	void init() {
		button.setBounds(10, 10, 100, 100);
		button.setLabel("hello...");
		canvas.setBounds(120, 120, 250, 150);
	}
	void postEvent(Event* e) {
		char txt[100];
		if (e->clazz == Event::MOUSE_EVENT) {
			MouseEvent* ee = (MouseEvent*) e;
			sprintf(txt, "%d , %d", ee->x, ee->y);
			setTitle(txt);

		}
		if (e->clazz == Event::WINDOW_EVENT) {
			WindowEvent*ee = (WindowEvent*) e;
			if (ee->type == WindowEvent::WINDOW_CLOSING) {
				App::getApp()->exit();
			}
		}
	}
};

void test_0() {
	App app;

	TestFrame frame;
	frame.init();

	frame.setBounds(10, 10, 400, 300);
	frame.setVisible(true);
	frame.setTitle("azeddine");

	app.run();
}

