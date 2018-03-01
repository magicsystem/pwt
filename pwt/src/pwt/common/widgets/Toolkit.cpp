/*
 * Toolkit.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>
namespace pwt {




static Toolkit* defaultToolkit = 0;
Toolkit* Toolkit::getDefaultToolkit() {
	if (defaultToolkit == 0) {
		defaultToolkit = getSystemToolkit();
	}
	return defaultToolkit;
}

Toolkit* Toolkit::setDefaultToolkit(Toolkit* toolkit) {
	Toolkit* last = defaultToolkit;
	if (toolkit == 0)
		defaultToolkit = getSystemToolkit();
	else
		defaultToolkit = toolkit;
	return last;
}
Toolkit::~Toolkit() {
	// TODO Auto-generated destructor stub
}

}  // namespace pwt
