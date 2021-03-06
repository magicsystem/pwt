/*
 * App.h
 *
 *  Created on: 18 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_CORE_APP_H_
#define INCLUDE_PWT_CORE_APP_H_
#include "config.h"
namespace pwt {
class Toolkit;
class PUBLIC App {
private:
	static App* defaultApp;
	void* reserved[2];
public:
	App();
	virtual ~App();
	static App* getApp();
	Toolkit* getSystemToolkit();
	Toolkit* getDefaultToolkit();
	Toolkit* setDefaultToolkit(Toolkit* toolkit);
	virtual int run();
	virtual int exit();
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_CORE_APP_H_ */
