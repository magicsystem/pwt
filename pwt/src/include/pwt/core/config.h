/*
 * config.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_CORE_CONFIG_H_
#define INCLUDE_PWT_CORE_CONFIG_H_

#ifdef __WIN32
#define __WIN
#endif
#ifdef __WIN64
#define __WIN
#endif

#ifdef __WIN
#ifndef PUBLIC
#ifdef BUILD
#define PUBLIC __declspec (dllexport)
#else
#define PUBLIC __declspec (dllimport)
#endif
#endif
#else
#define PUBLIC
#endif

typedef unsigned char      byte;
typedef signed char        int8;
typedef unsigned char      uint8;

typedef short unsigned     word;
typedef short int          int16;
typedef short unsigned     uint16;

typedef unsigned int       dword;
typedef int                int32;
typedef unsigned int       uint32;
typedef wchar_t            wchar;
typedef long long int      int64;
typedef long long unsigned uint64;
typedef bool boolean;


#endif /* INCLUDE_PWT_CORE_CONFIG_H_ */
