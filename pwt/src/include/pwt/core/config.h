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



#endif /* INCLUDE_PWT_CORE_CONFIG_H_ */
