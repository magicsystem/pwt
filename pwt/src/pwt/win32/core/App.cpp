/*
 * App.cpp
 *
 *  Created on: 18 févr. 2018
 *      Author: azeddine
 */
#include <pwt.h>
#ifdef __WIN
#include <windows.h>

namespace pwt {
App* App::defaultApp = 0;

App::App() {
	if (defaultApp == 0)
		defaultApp = this;
}
App* App::getApp() {
	if (defaultApp == 0) {
		defaultApp = new App();
	}
	return defaultApp;
}

App::~App() {
	Toolkit* systemToolkit = getSystemToolkit();
	Toolkit* defaultToolkit = getDefaultToolkit();
	if (defaultToolkit != 0 && defaultToolkit != systemToolkit)
		delete defaultToolkit;
	if (systemToolkit != 0)
		delete systemToolkit;
}

Toolkit* App::getSystemToolkit() {
	return Toolkit::getSystemToolkit();
}
Toolkit* App::getDefaultToolkit() {
	return Toolkit::getDefaultToolkit();
}

Toolkit* App::setDefaultToolkit(Toolkit* toolkit) {
	return Toolkit::setDefaultToolkit(toolkit);
}

int App::run() {
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

int App::exit() {
	PostQuitMessage(1);
	return 1;
}

} /* namespace pwt */
#endif
