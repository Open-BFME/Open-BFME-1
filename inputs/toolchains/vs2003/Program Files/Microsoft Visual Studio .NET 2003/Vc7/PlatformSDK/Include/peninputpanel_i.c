//+------------------------------------------------------------------------- 
// 
//  Microsoft Windows 
//  Copyright (C) Microsoft Corporation, 2003. 
// 
//  File: peninputpanel_i.c 
//      Microsoft Tablet PC API definitions 
// 
//-------------------------------------------------------------------------- 
	
 	
 	

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* Compiler settings for peninputpanel.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)

#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_PenInputPanelLib,0xd7ca032c,0xb7d0,0x429e,0x9f,0xd7,0x82,0x24,0x1c,0x35,0x6b,0x4a);


MIDL_DEFINE_GUID(IID, IID_IPenInputPanel,0xfa7a4083,0x5747,0x4040,0xa1,0x82,0x0b,0x0e,0x9f,0xd4,0xfa,0xc7);


MIDL_DEFINE_GUID(IID, DIID__IPenInputPanelEvents,0xb7e489da,0x3719,0x439f,0x84,0x8f,0xe7,0xac,0xbd,0x82,0x0f,0x17);


MIDL_DEFINE_GUID(CLSID, CLSID_PenInputPanel,0xf744e496,0x1b5a,0x489e,0x81,0xdc,0xfb,0xd7,0xac,0x62,0x98,0xa8);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/


#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* Compiler settings for peninputpanel.idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)

#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_PenInputPanelLib,0xd7ca032c,0xb7d0,0x429e,0x9f,0xd7,0x82,0x24,0x1c,0x35,0x6b,0x4a);


MIDL_DEFINE_GUID(IID, IID_IPenInputPanel,0xfa7a4083,0x5747,0x4040,0xa1,0x82,0x0b,0x0e,0x9f,0xd4,0xfa,0xc7);


MIDL_DEFINE_GUID(IID, DIID__IPenInputPanelEvents,0xb7e489da,0x3719,0x439f,0x84,0x8f,0xe7,0xac,0xbd,0x82,0x0f,0x17);


MIDL_DEFINE_GUID(CLSID, CLSID_PenInputPanel,0xf744e496,0x1b5a,0x489e,0x81,0xdc,0xfb,0xd7,0xac,0x62,0x98,0xa8);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

