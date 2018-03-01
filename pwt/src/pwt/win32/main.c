/*
 * main.c
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */
#ifdef __WIN32
#define __WIN
#endif
#ifdef __WIN64
#define __WIN
#endif
#ifdef __WIN
#include <windows.h>

HINSTANCE hinst;
int APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpvReserved) {

	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		hinst = hInstance;
		break;

	case DLL_PROCESS_DETACH:
		hinst = 0;
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
#endif
