/*
 * test_0.cpp
 *
 *  Created on: 9 févr. 2018
 *      Author: azeddine
 */
#include "arrayctrl/ArrayCtrl.h"
#include <stdio.h>

using namespace pwt;


class TestCanvas: public Canvas {
public:
	String s;
	void paint(Graphics& gc) {
		Rectangle bounds;
		getBounds(bounds);
		//gc.fillRect(10,10,100,50);
		gc.setForeground(Color::gray);
		gc.setLineWidth(1);
		//gc.setLineStyle(Graphics::LINE_DASHDOT);
		//gc.setLineCap(Graphics::CAP_FLAT);
		gc.drawRect(0, 0, bounds.width, bounds.height);
		gc.setForeground(Color::RED);
		gc.fillRect(0, 0, bounds.width, bounds.height);
		//gc.drawArc(0,0,bounds.width,bounds.height,0,-90);
		gc.setForeground(Color(0));
		gc.drawString(s, 10, 10);

	}
	void setText(String s) {
		this->s = s.clone();
		this->repaint();
	}


};

class SwingButton: public Canvas {
public:
	String text;
	void paint(Graphics& g) {
		Rectangle bounds;
		getBounds(bounds);
		g.setForeground(0xFF7A8A99);
		g.drawRect(0, 0, bounds.width - 2, bounds.height - 2);
		g.setForeground(Color(255, 255, 255));
		g.drawRect(1, 1, bounds.width - 2, bounds.height - 2);
		g.setForeground(0xFFEEEEEE);
		g.drawLine(0, bounds.height - 1, 1, bounds.height - 2);
		g.drawLine(bounds.width - 1, 0, bounds.width - 2, 1);
		g.setForeground(0xFFB8CFE5);
		g.drawLine(1, 1, 1, bounds.height - 2);
		g.drawLine(1, 1, bounds.width - 2, 1);
		g.setForeground(0xFF7A8A99);
		g.drawRect(0, 0, bounds.width - 3, bounds.height - 3);
		g.drawLine(bounds.width - 2, 0, bounds.width - 2, 0);
		g.drawLine(0, bounds.height - 2, 0, bounds.height - 2);
		g.setForeground(0xEEEEEE);
		g.drawLine(bounds.width - 1, 0, bounds.width - 1, 0);
		g.drawLine(0, bounds.height - 1, 0, bounds.height - 1);
		g.setForeground(0xFFB8CFE5);
		g.fillRect(1,1,bounds.width-4,bounds.height-4);
		//g.translate(-x, -y);

	}
	void setLabel(String s) {
		this->text = s.clone();
		this->repaint();
	}

};


class Table : public Canvas {
public:
	struct Elmt {
		Rectangle r;
		String text;
	};

private:

};

class MyArrayCtrl :
		public ARRAY_CTRL::ArrayCtrl,
		public ARRAY_CTRL::IView,
		public ARRAY_CTRL::IModel
{
public:
	virtual void Draw(Graphics& g, Rectangle& rc, int r, int c, ARRAY_CTRL::IModel* d) override {
		//g.setBackground(0xFFB8CFE5);
		//g.drawRectangle(&rc);
		//g.setClipping(rc);
		//g.setForeground(Color(255,0,0));
		g.drawString("Azeddine",5,rc.x,rc.y,true);
	}

	virtual void* getValue(int r, int c) override {
		return &data[r][c];
	}
	virtual void setValue(int r, int c, void* v) override {
		data[r][c] = *((String*) v);
	}
	virtual int getRowCount() override {
		return 100;
	}
	virtual int getColCount() override {
		return 6;
	}

	MyArrayCtrl() {
		setModel(this);
		for (int i = 0; i < 6 ; ++i) {
			addColumn("Column",40).setView(this);
			for (int r = 0; r < 100; ++r) {
				data[r][i] = "Hello world!";
			}
		}
	}

	String data[100][6];
private:
};

class TestFrame: public Frame {
public:
	MyArrayCtrl canvas;
	//Button button;
	//SwingButton swing;
	TestFrame() {
		create();
		//canvas.create(this);
		//button.create(this);
		add(&canvas);
		//add(&button);
		//add(&swing);
	}
	void init() {
		//button.setBounds(10, 10, 100, 100);
		//button.setLabel("hello...");
		canvas.setBounds(120, 120, 250, 150);
		//swing.setBounds(120, 120, 250, 150);
	}
	void processMouseEvent(MouseEvent& e) {
		char txt[100];
		sprintf(txt, "%d , %d", e.x, e.y);
		//swing.setLabel(txt);
	}
	void processWindowEvent(WindowEvent& e) {
		if (e.type == WindowEvent::WINDOW_CLOSING) {
			App::getApp()->exit();
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

