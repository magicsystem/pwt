/*
 * ArrayCtrl.h
 *
 *  Created on: 6 mars 2018
 *      Author: marouane
 */

#ifndef ARRAYCTRL_ARRAYCTRL_H_
#define ARRAYCTRL_ARRAYCTRL_H_

//#include <array>
#include <pwt.h>


namespace pwt {
namespace ARRAY_CTRL {

struct IModel {
	virtual void* getValue(int r, int c)=0;
	virtual void setValue(int r, int c, void* v)=0;
	virtual int getRowCount()=0;
	virtual int getColCount()=0;
	virtual ~IModel() {}
};

struct IView {
	virtual void Draw(Graphics& g, Rectangle& rc, int r, int c, IModel* d)=0;
	virtual ~IView(){}
};

class Column {
	IView* view;
	int size;
	String title;
	int index;

	friend class ArrayCtrl;
public:
	int getSize() const;
	void setSize(int size);
	const String& getTitle() const;
	void setTitle(const String& title);
	IView* getView() const;
	void setView(IView* view);

	Column() : view(nullptr),size(0),index(0) {}
	Column(const Column& other) {
		if(&other == this) return;
		view = other.view;
		size = other.size;
		title = other.title;
		index = other.index;
	}

	int getIndex() const;
	void setIndex(int index);
};

class ArrayCtrl: public Canvas {
public:
	typedef Column* Columns;

private:
	IModel* model;
	int ccount;
	Columns* columns;
public:

	ArrayCtrl();
	virtual ~ArrayCtrl();

	Column& addColumn(const String& title,int size);
	IModel* getModel() const;
	void setModel(IModel* model);

	virtual void paint(Graphics& g) override;
};

} /* namespace ARRAY_CTRL */
} /* namespace pwt */

#endif /* ARRAYCTRL_ARRAYCTRL_H_ */
