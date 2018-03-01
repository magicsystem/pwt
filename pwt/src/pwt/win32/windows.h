/*
 * windows.h
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#ifndef PWT_WIN32_WINDOWS_H_
#define PWT_WIN32_WINDOWS_H_
#include <pwt.h>
#ifdef __WIN
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
class UnicodeConverter {
public:
	UnicodeConverter();
	~UnicodeConverter();
	void set(pwt::String str);
	WCHAR* get();
	WCHAR* str;
	WCHAR* allocated;
	WCHAR temp[0x101];
};

#define WM_AWT_MOUSEENTER (WM_USER + 1)
#define WM_AWT_MOUSEEXIT (WM_USER + 2)



#endif

#endif /* PWT_WIN32_WINDOWS_H_ */
