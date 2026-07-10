/*
**  Miles Sound System altypes.h shim — minimal declarations for sweep compilation
*/

#pragma once

#ifndef _ALTYPES_H
#define _ALTYPES_H

typedef int              S32;
typedef unsigned int     U32;
typedef short            S16;
typedef unsigned short   U16;
typedef char             S8;
typedef unsigned char    U8;
typedef float            F32;
typedef double           F64;
typedef int              BOOL;
typedef unsigned int     UINT;
typedef int              INT;

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define DBG_DECLARE_TYPE(name)

#endif
