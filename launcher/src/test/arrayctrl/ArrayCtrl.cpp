/*
 * ArrayCtrl.cpp
 *
 *  Created on: 6 mars 2018
 *      Author: marouane
 */

#include "ArrayCtrl.h"

namespace pwt {
namespace ARRAY_CTRL {

int Column::getSize() const {
	return size;
}

void Column::setSize(int size) {
	this->size = size;
}

const String& Column::getTitle() const {
	return title;
}

void Column::setTitle(const String& title) {
	this->title = title;
}

IView* Column::getView() const {
	return view;
}

int Column::getIndex() const {
	return index;
}

void Column::setIndex(int index) {
	this->index = index;
}

void Column::setView(IView* view) {
	this->view = view;
}







ArrayCtrl::ArrayCtrl() {
	model=nullptr;
	columns=new Columns[50];
	ccount=0;
}

IModel* ArrayCtrl::getModel() const {
	return model;
}

void ArrayCtrl::setModel(IModel* model) {
	this->model = model;
}

ArrayCtrl::~ArrayCtrl() {
	for (int i = 0; i < ccount; ++i) {
		if(columns[i]) delete columns[i];
	}

	if(columns) delete [] columns;
}

Column& ArrayCtrl::addColumn(const String& title, int size) {
	Column* c = new Column();
	c->setTitle(title);
	c->setSize(size);
	columns[ccount]=c;
	ccount++;
	return *c;
}

void ArrayCtrl::paint(Graphics& g) {
	if(!model) return;
	Point org{0,0};
	Rectangle r;
	r.x = org.x;
	Column* c;
	IView* v;
	int co;

	for (int i = 0; i < ccount; ++i) {
		c = columns[i];
		v = c->getView();
		if (!v || c->getSize() <= 0 ) continue;
		r.width = c->getSize();
		co = c->getIndex();

		r.y = org.y;
		for (int ro = 0; ro < model->getRowCount(); ++ro) {
			r.height = 30;
			v->Draw(g,r,ro,co,model);
			r.y += r.height;
		}

		r.x += r.width;
	}

}



} /* namespace ARRAY_CTRL */
} /* namespace pwt */


