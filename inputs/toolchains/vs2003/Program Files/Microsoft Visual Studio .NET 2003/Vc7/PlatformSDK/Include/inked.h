//-------------------------------------------------------------------------- 
// 
//  Copyright (c) Microsoft Corporation.  All rights reserved. 
// 
//  File: inked.h 
//      Microsoft Tablet PC API definitions 
// 
//-------------------------------------------------------------------------- 
	
 	
 	

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* Compiler settings for inked.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __inked_h__
#define __inked_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IInkEdit_FWD_DEFINED__
#define __IInkEdit_FWD_DEFINED__
typedef interface IInkEdit IInkEdit;
#endif 	/* __IInkEdit_FWD_DEFINED__ */


#ifndef ___IInkEditEvents_FWD_DEFINED__
#define ___IInkEditEvents_FWD_DEFINED__
typedef interface _IInkEditEvents _IInkEditEvents;
#endif 	/* ___IInkEditEvents_FWD_DEFINED__ */


#ifndef __InkEdit_FWD_DEFINED__
#define __InkEdit_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkEdit InkEdit;
#else
typedef struct InkEdit InkEdit;
#endif /* __cplusplus */

#endif 	/* __InkEdit_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "msinkaut.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_inked_0000 */
/* [local] */ 


///////////////////////////////////////////////////////////////////////////////
//
// InkEdit Win32 API
//
///////////////////////////////////////////////////////////////////////////////

#define INKEDIT_CLASSW  L"INKEDIT"

#ifdef UNICODE
#define INKEDIT_CLASS   INKEDIT_CLASSW
#else
#define INKEDIT_CLASS   "INKEDIT"
#endif

// InkEdit Constants

// InkEdit Structures

struct IEC_STROKEINFO
{
     NMHDR nmhdr; 
     IInkCursor * Cursor;
     IInkStrokeDisp * Stroke;
};

struct IEC_GESTUREINFO
{
     NMHDR nmhdr; 
     IInkCursor * Cursor;
     IInkStrokes * Strokes;
     VARIANT Gestures;
};

struct IEC_RECOGNITIONRESULTINFO
{
     NMHDR nmhdr; 
     IInkRecognitionResult * RecognitionResult;
};

// InkEdit messages

#define IEC__BASE           (WM_USER + 0x0200)
#define EM_GETINKMODE       (IEC__BASE + 1)
#define EM_SETINKMODE       (IEC__BASE + 2)
#define EM_GETINKINSERTMODE (IEC__BASE + 3)
#define EM_SETINKINSERTMODE (IEC__BASE + 4)
#define EM_GETDRAWATTR      (IEC__BASE + 5)
#define EM_SETDRAWATTR      (IEC__BASE + 6)
#define EM_GETRECOTIMEOUT   (IEC__BASE + 7)
#define EM_SETRECOTIMEOUT   (IEC__BASE + 8)
#define EM_GETGESTURESTATUS (IEC__BASE + 9)
#define EM_SETGESTURESTATUS (IEC__BASE + 10)
#define EM_GETRECOGNIZER    (IEC__BASE + 11)
#define EM_SETRECOGNIZER    (IEC__BASE + 12)
#define EM_GETFACTOID       (IEC__BASE + 13)
#define EM_SETFACTOID       (IEC__BASE + 14)
#define EM_GETSELINK        (IEC__BASE + 15)
#define EM_SETSELINK        (IEC__BASE + 16)
#define EM_GETMOUSEICON     (IEC__BASE + 17)
#define EM_SETMOUSEICON     (IEC__BASE + 18)
#define EM_GETMOUSEPOINTER  (IEC__BASE + 19)
#define EM_SETMOUSEPOINTER  (IEC__BASE + 20)
#define EM_GETSTATUS        (IEC__BASE + 21)
#define EM_RECOGNIZE        (IEC__BASE + 22)
#define EM_GETUSEMOUSEFORINPUT   (IEC__BASE + 23)
#define EM_SETUSEMOUSEFORINPUT   (IEC__BASE + 24)
#define EM_SETSELINKDISPLAYMODE  (IEC__BASE + 25)
#define EM_GETSELINKDISPLAYMODE  (IEC__BASE + 26)

///////////////////////////////////////////////////////////////////////////////

// InkEdit notifications

#define IECN__BASE             (0x0800)
#define IECN_STROKE            (IECN__BASE + 1)
#define IECN_GESTURE           (IECN__BASE + 2)
#define IECN_RECOGNITIONRESULT (IECN__BASE + 3)




extern RPC_IF_HANDLE __MIDL_itf_inked_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_inked_0000_v0_0_s_ifspec;


#ifndef __INKEDLib_LIBRARY_DEFINED__
#define __INKEDLib_LIBRARY_DEFINED__

/* library INKEDLib */
/* [helpcontext][helpstring][helpfile][version][uuid] */ 

typedef /* [helpcontext][helpstring] */ 
enum MouseButton
    {	NO_BUTTON	= 0,
	LEFT_BUTTON	= 0x1,
	RIGHT_BUTTON	= 0x2,
	MIDDLE_BUTTON	= 0x4
    } 	MouseButton;

typedef /* [helpcontext][helpstring] */ 
enum SelAlignmentConstants
    {	rtfLeft	= 0,
	rtfRight	= 1,
	rtfCenter	= 2
    } 	SelAlignmentConstants;

typedef /* [hidden] */ 
enum DISPID_InkEdit
    {	DISPID_Text	= DISPID_VALUE,
	DISPID_TextRTF	= DISPID_Text + 1,
	DISPID_Hwnd	= DISPID_TextRTF + 1,
	DISPID_DisableNoScroll	= DISPID_Hwnd + 1,
	DISPID_Locked	= DISPID_DisableNoScroll + 1,
	DISPID_Enabled	= DISPID_Locked + 1,
	DISPID_MaxLength	= DISPID_Enabled + 1,
	DISPID_MultiLine	= DISPID_MaxLength + 1,
	DISPID_ScrollBars	= DISPID_MultiLine + 1,
	DISPID_RTSelStart	= DISPID_ScrollBars + 1,
	DISPID_RTSelLength	= DISPID_RTSelStart + 1,
	DISPID_RTSelText	= DISPID_RTSelLength + 1,
	DISPID_SelAlignment	= DISPID_RTSelText + 1,
	DISPID_SelBold	= DISPID_SelAlignment + 1,
	DISPID_SelCharOffset	= DISPID_SelBold + 1,
	DISPID_SelColor	= DISPID_SelCharOffset + 1,
	DISPID_SelFontName	= DISPID_SelColor + 1,
	DISPID_SelFontSize	= DISPID_SelFontName + 1,
	DISPID_SelItalic	= DISPID_SelFontSize + 1,
	DISPID_SelRTF	= DISPID_SelItalic + 1,
	DISPID_SelUnderline	= DISPID_SelRTF + 1,
	DISPID_DragIcon	= DISPID_SelUnderline + 1,
	DISPID_Status	= DISPID_DragIcon + 1,
	DISPID_UseMouseForInput	= DISPID_Status + 1,
	DISPID_InkMode	= DISPID_UseMouseForInput + 1,
	DISPID_InkInsertMode	= DISPID_InkMode + 1,
	DISPID_RecoTimeout	= DISPID_InkInsertMode + 1,
	DISPID_DrawAttr	= DISPID_RecoTimeout + 1,
	DISPID_Recognizer	= DISPID_DrawAttr + 1,
	DISPID_Factoid	= DISPID_Recognizer + 1,
	DISPID_SelInk	= DISPID_Factoid + 1,
	DISPID_SelInksDisplayMode	= DISPID_SelInk + 1,
	DISPID_Recognize	= DISPID_SelInksDisplayMode + 1,
	DISPID_GetGestStatus	= DISPID_Recognize + 1,
	DISPID_SetGestStatus	= DISPID_GetGestStatus + 1,
	DISPID_Refresh	= DISPID_SetGestStatus + 1
    } 	DISPID_InkEdit;

typedef /* [hidden] */ 
enum DISPID_InkEditEvents
    {	DISPID_IeeChange	= 1,
	DISPID_IeeSelChange	= 2,
	DISPID_IeeKeyDown	= 3,
	DISPID_IeeKeyUp	= 4,
	DISPID_IeeMouseUp	= 5,
	DISPID_IeeMouseDown	= 6,
	DISPID_IeeKeyPress	= 7,
	DISPID_IeeDblClick	= 8,
	DISPID_IeeClick	= 9,
	DISPID_IeeMouseMove	= 10,
	DISPID_IeeCursorDown	= 21,
	DISPID_IeeStroke	= 22,
	DISPID_IeeGesture	= 23,
	DISPID_IeeRecognitionResult	= 24
    } 	DISPID_InkEditEvents;


EXTERN_C const IID LIBID_INKEDLib;

#ifndef __IInkEdit_INTERFACE_DEFINED__
#define __IInkEdit_INTERFACE_DEFINED__

/* interface IInkEdit */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 

typedef /* [helpcontext][helpstring] */ 
enum InkMode
    {	IEM_Disabled	= 0,
	IEM_Ink	= 1,
	IEM_InkAndGesture	= 2
    } 	InkMode;

typedef /* [helpcontext][helpstring] */ 
enum InkInsertMode
    {	IEM_InsertText	= 0,
	IEM_InsertInk	= 1
    } 	InkInsertMode;

typedef /* [helpcontext][helpstring] */ 
enum InkEditStatus
    {	IES_Idle	= 0,
	IES_Collecting	= 1,
	IES_Recognizing	= 2
    } 	InkEditStatus;

typedef /* [helpcontext][helpstring] */ 
enum InkDisplayMode
    {	IDM_Ink	= 0,
	IDM_Text	= 1
    } 	InkDisplayMode;

typedef /* [helpcontext][helpstring] */ 
enum AppearanceConstants
    {	rtfFlat	= 0,
	rtfThreeD	= 1
    } 	AppearanceConstants;

typedef /* [helpcontext][helpstring] */ 
enum BorderStyleConstants
    {	rtfNoBorder	= 0,
	rtfFixedSingle	= 1
    } 	BorderStyleConstants;

typedef /* [helpcontext][helpstring] */ 
enum ScrollBarsConstants
    {	rtfNone	= 0,
	rtfHorizontal	= 1,
	rtfVertical	= 2,
	rtfBoth	= 3
    } 	ScrollBarsConstants;


EXTERN_C const IID IID_IInkEdit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F2127A19-FBFB-4AED-8464-3F36D78CFEFB")
    IInkEdit : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ InkEditStatus *pStatus) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_UseMouseForInput( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_UseMouseForInput( 
            /* [defaultvalue][in] */ VARIANT_BOOL newVal = ( VARIANT_BOOL  )-1) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InkMode( 
            /* [retval][out] */ InkMode *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_InkMode( 
            /* [defaultvalue][in] */ InkMode newVal = IEM_InkAndGesture) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_InkInsertMode( 
            /* [retval][out] */ InkInsertMode *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_InkInsertMode( 
            /* [defaultvalue][in] */ InkInsertMode newVal = IEM_InsertText) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DrawingAttributes( 
            /* [retval][out] */ IInkDrawingAttributes **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref][id] */ HRESULT STDMETHODCALLTYPE putref_DrawingAttributes( 
            /* [in] */ IInkDrawingAttributes *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RecognitionTimeout( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_RecognitionTimeout( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Recognizer( 
            /* [retval][out] */ IInkRecognizer **pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propputref][id] */ HRESULT STDMETHODCALLTYPE putref_Recognizer( 
            /* [in] */ IInkRecognizer *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Factoid( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Factoid( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelInks( 
            /* [retval][out] */ VARIANT *pSelInk) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelInks( 
            /* [in] */ VARIANT SelInk) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelInksDisplayMode( 
            /* [retval][out] */ InkDisplayMode *pInkDisplayMode) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelInksDisplayMode( 
            /* [in] */ InkDisplayMode InkDisplayMode) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Recognize( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGestureStatus( 
            /* [in] */ InkApplicationGesture Gesture,
            /* [retval][out] */ VARIANT_BOOL *pListen) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGestureStatus( 
            /* [in] */ InkApplicationGesture Gesture,
            /* [in] */ VARIANT_BOOL Listen) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Appearance( 
            /* [retval][out] */ AppearanceConstants *pAppearance) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Appearance( 
            /* [in] */ AppearanceConstants pAppearance) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_BorderStyle( 
            /* [retval][out] */ BorderStyleConstants *pBorderStyle) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_BorderStyle( 
            /* [in] */ BorderStyleConstants pBorderStyle) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Hwnd( 
            /* [retval][out] */ OLE_HANDLE *pohHwnd) = 0;
        
        virtual /* [helpcontext][helpstring][bindable][propget][id] */ HRESULT STDMETHODCALLTYPE get_Font( 
            /* [retval][out] */ IFontDisp **ppFont) = 0;
        
        virtual /* [helpcontext][helpstring][bindable][propputref][id] */ HRESULT STDMETHODCALLTYPE putref_Font( 
            /* [in] */ IFontDisp *ppFont) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR *pbstrText) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR pbstrText) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_MouseIcon( 
            /* [retval][out] */ IPictureDisp **MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_MouseIcon( 
            /* [in] */ IPictureDisp *MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][propputref][id] */ HRESULT STDMETHODCALLTYPE putref_MouseIcon( 
            /* [in] */ IPictureDisp *MouseIcon) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_MousePointer( 
            /* [retval][out] */ InkMousePointer *MousePointer) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_MousePointer( 
            /* [in] */ InkMousePointer MousePointer) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Locked( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Locked( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_MaxLength( 
            /* [retval][out] */ long *plMaxLength) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_MaxLength( 
            /* [in] */ long lMaxLength) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_MultiLine( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_MultiLine( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ScrollBars( 
            /* [retval][out] */ ScrollBarsConstants *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ScrollBars( 
            /* [in] */ ScrollBarsConstants newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DisableNoScroll( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DisableNoScroll( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelAlignment( 
            /* [retval][out] */ VARIANT *pvarSelAlignment) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelAlignment( 
            /* [in] */ VARIANT pvarSelAlignment) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelBold( 
            /* [retval][out] */ VARIANT *pvarSelBold) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelBold( 
            /* [in] */ VARIANT pvarSelBold) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelItalic( 
            /* [retval][out] */ VARIANT *pvarSelItalic) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelItalic( 
            /* [in] */ VARIANT pvarSelItalic) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelUnderline( 
            /* [retval][out] */ VARIANT *pvarSelUnderline) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelUnderline( 
            /* [in] */ VARIANT pvarSelUnderline) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelColor( 
            /* [retval][out] */ VARIANT *pvarSelColor) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelColor( 
            /* [in] */ VARIANT pvarSelColor) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelFontName( 
            /* [retval][out] */ VARIANT *pvarSelFontName) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelFontName( 
            /* [in] */ VARIANT pvarSelFontName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelFontSize( 
            /* [retval][out] */ VARIANT *pvarSelFontSize) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelFontSize( 
            /* [in] */ VARIANT pvarSelFontSize) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelCharOffset( 
            /* [retval][out] */ VARIANT *pvarSelCharOffset) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelCharOffset( 
            /* [in] */ VARIANT pvarSelCharOffset) = 0;
        
        virtual /* [helpcontext][helpstring][defaultbind][displaybind][bindable][propget][id] */ HRESULT STDMETHODCALLTYPE get_TextRTF( 
            /* [retval][out] */ BSTR *pbstrTextRTF) = 0;
        
        virtual /* [helpcontext][helpstring][displaybind][bindable][propput][id] */ HRESULT STDMETHODCALLTYPE put_TextRTF( 
            /* [in] */ BSTR pbstrTextRTF) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelStart( 
            /* [retval][out] */ long *plSelStart) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelStart( 
            /* [in] */ long plSelStart) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelLength( 
            /* [retval][out] */ long *plSelLength) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelLength( 
            /* [in] */ long plSelLength) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelText( 
            /* [retval][out] */ BSTR *pbstrSelText) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelText( 
            /* [in] */ BSTR pbstrSelText) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_SelRTF( 
            /* [retval][out] */ BSTR *pbstrSelRTF) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_SelRTF( 
            /* [in] */ BSTR pbstrSelRTF) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkEditVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkEdit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkEdit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkEdit * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkEdit * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkEdit * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkEdit * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkEdit * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Status )( 
            IInkEdit * This,
            /* [retval][out] */ InkEditStatus *pStatus);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_UseMouseForInput )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_UseMouseForInput )( 
            IInkEdit * This,
            /* [defaultvalue][in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_InkMode )( 
            IInkEdit * This,
            /* [retval][out] */ InkMode *pVal);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_InkMode )( 
            IInkEdit * This,
            /* [defaultvalue][in] */ InkMode newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_InkInsertMode )( 
            IInkEdit * This,
            /* [retval][out] */ InkInsertMode *pVal);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_InkInsertMode )( 
            IInkEdit * This,
            /* [defaultvalue][in] */ InkInsertMode newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DrawingAttributes )( 
            IInkEdit * This,
            /* [retval][out] */ IInkDrawingAttributes **pVal);
        
        /* [helpcontext][helpstring][propputref][id] */ HRESULT ( STDMETHODCALLTYPE *putref_DrawingAttributes )( 
            IInkEdit * This,
            /* [in] */ IInkDrawingAttributes *newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_RecognitionTimeout )( 
            IInkEdit * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_RecognitionTimeout )( 
            IInkEdit * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Recognizer )( 
            IInkEdit * This,
            /* [retval][out] */ IInkRecognizer **pVal);
        
        /* [helpcontext][helpstring][propputref][id] */ HRESULT ( STDMETHODCALLTYPE *putref_Recognizer )( 
            IInkEdit * This,
            /* [in] */ IInkRecognizer *newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Factoid )( 
            IInkEdit * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Factoid )( 
            IInkEdit * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelInks )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT *pSelInk);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelInks )( 
            IInkEdit * This,
            /* [in] */ VARIANT SelInk);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelInksDisplayMode )( 
            IInkEdit * This,
            /* [retval][out] */ InkDisplayMode *pInkDisplayMode);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelInksDisplayMode )( 
            IInkEdit * This,
            /* [in] */ InkDisplayMode InkDisplayMode);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Recognize )( 
            IInkEdit * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetGestureStatus )( 
            IInkEdit * This,
            /* [in] */ InkApplicationGesture Gesture,
            /* [retval][out] */ VARIANT_BOOL *pListen);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetGestureStatus )( 
            IInkEdit * This,
            /* [in] */ InkApplicationGesture Gesture,
            /* [in] */ VARIANT_BOOL Listen);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IInkEdit * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IInkEdit * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Appearance )( 
            IInkEdit * This,
            /* [retval][out] */ AppearanceConstants *pAppearance);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Appearance )( 
            IInkEdit * This,
            /* [in] */ AppearanceConstants pAppearance);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_BorderStyle )( 
            IInkEdit * This,
            /* [retval][out] */ BorderStyleConstants *pBorderStyle);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_BorderStyle )( 
            IInkEdit * This,
            /* [in] */ BorderStyleConstants pBorderStyle);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Hwnd )( 
            IInkEdit * This,
            /* [retval][out] */ OLE_HANDLE *pohHwnd);
        
        /* [helpcontext][helpstring][bindable][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Font )( 
            IInkEdit * This,
            /* [retval][out] */ IFontDisp **ppFont);
        
        /* [helpcontext][helpstring][bindable][propputref][id] */ HRESULT ( STDMETHODCALLTYPE *putref_Font )( 
            IInkEdit * This,
            /* [in] */ IFontDisp *ppFont);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Text )( 
            IInkEdit * This,
            /* [retval][out] */ BSTR *pbstrText);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Text )( 
            IInkEdit * This,
            /* [in] */ BSTR pbstrText);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_MouseIcon )( 
            IInkEdit * This,
            /* [retval][out] */ IPictureDisp **MouseIcon);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MouseIcon )( 
            IInkEdit * This,
            /* [in] */ IPictureDisp *MouseIcon);
        
        /* [helpcontext][helpstring][propputref][id] */ HRESULT ( STDMETHODCALLTYPE *putref_MouseIcon )( 
            IInkEdit * This,
            /* [in] */ IPictureDisp *MouseIcon);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_MousePointer )( 
            IInkEdit * This,
            /* [retval][out] */ InkMousePointer *MousePointer);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MousePointer )( 
            IInkEdit * This,
            /* [in] */ InkMousePointer MousePointer);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Locked )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Locked )( 
            IInkEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IInkEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_MaxLength )( 
            IInkEdit * This,
            /* [retval][out] */ long *plMaxLength);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MaxLength )( 
            IInkEdit * This,
            /* [in] */ long lMaxLength);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_MultiLine )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_MultiLine )( 
            IInkEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ScrollBars )( 
            IInkEdit * This,
            /* [retval][out] */ ScrollBarsConstants *pVal);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_ScrollBars )( 
            IInkEdit * This,
            /* [in] */ ScrollBarsConstants newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DisableNoScroll )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DisableNoScroll )( 
            IInkEdit * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelAlignment )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT *pvarSelAlignment);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelAlignment )( 
            IInkEdit * This,
            /* [in] */ VARIANT pvarSelAlignment);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelBold )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT *pvarSelBold);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelBold )( 
            IInkEdit * This,
            /* [in] */ VARIANT pvarSelBold);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelItalic )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT *pvarSelItalic);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelItalic )( 
            IInkEdit * This,
            /* [in] */ VARIANT pvarSelItalic);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelUnderline )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT *pvarSelUnderline);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelUnderline )( 
            IInkEdit * This,
            /* [in] */ VARIANT pvarSelUnderline);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelColor )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT *pvarSelColor);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelColor )( 
            IInkEdit * This,
            /* [in] */ VARIANT pvarSelColor);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelFontName )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT *pvarSelFontName);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelFontName )( 
            IInkEdit * This,
            /* [in] */ VARIANT pvarSelFontName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelFontSize )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT *pvarSelFontSize);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelFontSize )( 
            IInkEdit * This,
            /* [in] */ VARIANT pvarSelFontSize);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelCharOffset )( 
            IInkEdit * This,
            /* [retval][out] */ VARIANT *pvarSelCharOffset);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelCharOffset )( 
            IInkEdit * This,
            /* [in] */ VARIANT pvarSelCharOffset);
        
        /* [helpcontext][helpstring][defaultbind][displaybind][bindable][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_TextRTF )( 
            IInkEdit * This,
            /* [retval][out] */ BSTR *pbstrTextRTF);
        
        /* [helpcontext][helpstring][displaybind][bindable][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_TextRTF )( 
            IInkEdit * This,
            /* [in] */ BSTR pbstrTextRTF);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelStart )( 
            IInkEdit * This,
            /* [retval][out] */ long *plSelStart);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelStart )( 
            IInkEdit * This,
            /* [in] */ long plSelStart);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelLength )( 
            IInkEdit * This,
            /* [retval][out] */ long *plSelLength);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelLength )( 
            IInkEdit * This,
            /* [in] */ long plSelLength);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelText )( 
            IInkEdit * This,
            /* [retval][out] */ BSTR *pbstrSelText);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelText )( 
            IInkEdit * This,
            /* [in] */ BSTR pbstrSelText);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_SelRTF )( 
            IInkEdit * This,
            /* [retval][out] */ BSTR *pbstrSelRTF);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_SelRTF )( 
            IInkEdit * This,
            /* [in] */ BSTR pbstrSelRTF);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IInkEdit * This);
        
        END_INTERFACE
    } IInkEditVtbl;

    interface IInkEdit
    {
        CONST_VTBL struct IInkEditVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkEdit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkEdit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkEdit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkEdit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkEdit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkEdit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkEdit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkEdit_get_Status(This,pStatus)	\
    (This)->lpVtbl -> get_Status(This,pStatus)

#define IInkEdit_get_UseMouseForInput(This,pVal)	\
    (This)->lpVtbl -> get_UseMouseForInput(This,pVal)

#define IInkEdit_put_UseMouseForInput(This,newVal)	\
    (This)->lpVtbl -> put_UseMouseForInput(This,newVal)

#define IInkEdit_get_InkMode(This,pVal)	\
    (This)->lpVtbl -> get_InkMode(This,pVal)

#define IInkEdit_put_InkMode(This,newVal)	\
    (This)->lpVtbl -> put_InkMode(This,newVal)

#define IInkEdit_get_InkInsertMode(This,pVal)	\
    (This)->lpVtbl -> get_InkInsertMode(This,pVal)

#define IInkEdit_put_InkInsertMode(This,newVal)	\
    (This)->lpVtbl -> put_InkInsertMode(This,newVal)

#define IInkEdit_get_DrawingAttributes(This,pVal)	\
    (This)->lpVtbl -> get_DrawingAttributes(This,pVal)

#define IInkEdit_putref_DrawingAttributes(This,newVal)	\
    (This)->lpVtbl -> putref_DrawingAttributes(This,newVal)

#define IInkEdit_get_RecognitionTimeout(This,pVal)	\
    (This)->lpVtbl -> get_RecognitionTimeout(This,pVal)

#define IInkEdit_put_RecognitionTimeout(This,newVal)	\
    (This)->lpVtbl -> put_RecognitionTimeout(This,newVal)

#define IInkEdit_get_Recognizer(This,pVal)	\
    (This)->lpVtbl -> get_Recognizer(This,pVal)

#define IInkEdit_putref_Recognizer(This,newVal)	\
    (This)->lpVtbl -> putref_Recognizer(This,newVal)

#define IInkEdit_get_Factoid(This,pVal)	\
    (This)->lpVtbl -> get_Factoid(This,pVal)

#define IInkEdit_put_Factoid(This,newVal)	\
    (This)->lpVtbl -> put_Factoid(This,newVal)

#define IInkEdit_get_SelInks(This,pSelInk)	\
    (This)->lpVtbl -> get_SelInks(This,pSelInk)

#define IInkEdit_put_SelInks(This,SelInk)	\
    (This)->lpVtbl -> put_SelInks(This,SelInk)

#define IInkEdit_get_SelInksDisplayMode(This,pInkDisplayMode)	\
    (This)->lpVtbl -> get_SelInksDisplayMode(This,pInkDisplayMode)

#define IInkEdit_put_SelInksDisplayMode(This,InkDisplayMode)	\
    (This)->lpVtbl -> put_SelInksDisplayMode(This,InkDisplayMode)

#define IInkEdit_Recognize(This)	\
    (This)->lpVtbl -> Recognize(This)

#define IInkEdit_GetGestureStatus(This,Gesture,pListen)	\
    (This)->lpVtbl -> GetGestureStatus(This,Gesture,pListen)

#define IInkEdit_SetGestureStatus(This,Gesture,Listen)	\
    (This)->lpVtbl -> SetGestureStatus(This,Gesture,Listen)

#define IInkEdit_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define IInkEdit_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define IInkEdit_get_Appearance(This,pAppearance)	\
    (This)->lpVtbl -> get_Appearance(This,pAppearance)

#define IInkEdit_put_Appearance(This,pAppearance)	\
    (This)->lpVtbl -> put_Appearance(This,pAppearance)

#define IInkEdit_get_BorderStyle(This,pBorderStyle)	\
    (This)->lpVtbl -> get_BorderStyle(This,pBorderStyle)

#define IInkEdit_put_BorderStyle(This,pBorderStyle)	\
    (This)->lpVtbl -> put_BorderStyle(This,pBorderStyle)

#define IInkEdit_get_Hwnd(This,pohHwnd)	\
    (This)->lpVtbl -> get_Hwnd(This,pohHwnd)

#define IInkEdit_get_Font(This,ppFont)	\
    (This)->lpVtbl -> get_Font(This,ppFont)

#define IInkEdit_putref_Font(This,ppFont)	\
    (This)->lpVtbl -> putref_Font(This,ppFont)

#define IInkEdit_get_Text(This,pbstrText)	\
    (This)->lpVtbl -> get_Text(This,pbstrText)

#define IInkEdit_put_Text(This,pbstrText)	\
    (This)->lpVtbl -> put_Text(This,pbstrText)

#define IInkEdit_get_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> get_MouseIcon(This,MouseIcon)

#define IInkEdit_put_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> put_MouseIcon(This,MouseIcon)

#define IInkEdit_putref_MouseIcon(This,MouseIcon)	\
    (This)->lpVtbl -> putref_MouseIcon(This,MouseIcon)

#define IInkEdit_get_MousePointer(This,MousePointer)	\
    (This)->lpVtbl -> get_MousePointer(This,MousePointer)

#define IInkEdit_put_MousePointer(This,MousePointer)	\
    (This)->lpVtbl -> put_MousePointer(This,MousePointer)

#define IInkEdit_get_Locked(This,pVal)	\
    (This)->lpVtbl -> get_Locked(This,pVal)

#define IInkEdit_put_Locked(This,newVal)	\
    (This)->lpVtbl -> put_Locked(This,newVal)

#define IInkEdit_get_Enabled(This,pVal)	\
    (This)->lpVtbl -> get_Enabled(This,pVal)

#define IInkEdit_put_Enabled(This,newVal)	\
    (This)->lpVtbl -> put_Enabled(This,newVal)

#define IInkEdit_get_MaxLength(This,plMaxLength)	\
    (This)->lpVtbl -> get_MaxLength(This,plMaxLength)

#define IInkEdit_put_MaxLength(This,lMaxLength)	\
    (This)->lpVtbl -> put_MaxLength(This,lMaxLength)

#define IInkEdit_get_MultiLine(This,pVal)	\
    (This)->lpVtbl -> get_MultiLine(This,pVal)

#define IInkEdit_put_MultiLine(This,newVal)	\
    (This)->lpVtbl -> put_MultiLine(This,newVal)

#define IInkEdit_get_ScrollBars(This,pVal)	\
    (This)->lpVtbl -> get_ScrollBars(This,pVal)

#define IInkEdit_put_ScrollBars(This,newVal)	\
    (This)->lpVtbl -> put_ScrollBars(This,newVal)

#define IInkEdit_get_DisableNoScroll(This,pVal)	\
    (This)->lpVtbl -> get_DisableNoScroll(This,pVal)

#define IInkEdit_put_DisableNoScroll(This,newVal)	\
    (This)->lpVtbl -> put_DisableNoScroll(This,newVal)

#define IInkEdit_get_SelAlignment(This,pvarSelAlignment)	\
    (This)->lpVtbl -> get_SelAlignment(This,pvarSelAlignment)

#define IInkEdit_put_SelAlignment(This,pvarSelAlignment)	\
    (This)->lpVtbl -> put_SelAlignment(This,pvarSelAlignment)

#define IInkEdit_get_SelBold(This,pvarSelBold)	\
    (This)->lpVtbl -> get_SelBold(This,pvarSelBold)

#define IInkEdit_put_SelBold(This,pvarSelBold)	\
    (This)->lpVtbl -> put_SelBold(This,pvarSelBold)

#define IInkEdit_get_SelItalic(This,pvarSelItalic)	\
    (This)->lpVtbl -> get_SelItalic(This,pvarSelItalic)

#define IInkEdit_put_SelItalic(This,pvarSelItalic)	\
    (This)->lpVtbl -> put_SelItalic(This,pvarSelItalic)

#define IInkEdit_get_SelUnderline(This,pvarSelUnderline)	\
    (This)->lpVtbl -> get_SelUnderline(This,pvarSelUnderline)

#define IInkEdit_put_SelUnderline(This,pvarSelUnderline)	\
    (This)->lpVtbl -> put_SelUnderline(This,pvarSelUnderline)

#define IInkEdit_get_SelColor(This,pvarSelColor)	\
    (This)->lpVtbl -> get_SelColor(This,pvarSelColor)

#define IInkEdit_put_SelColor(This,pvarSelColor)	\
    (This)->lpVtbl -> put_SelColor(This,pvarSelColor)

#define IInkEdit_get_SelFontName(This,pvarSelFontName)	\
    (This)->lpVtbl -> get_SelFontName(This,pvarSelFontName)

#define IInkEdit_put_SelFontName(This,pvarSelFontName)	\
    (This)->lpVtbl -> put_SelFontName(This,pvarSelFontName)

#define IInkEdit_get_SelFontSize(This,pvarSelFontSize)	\
    (This)->lpVtbl -> get_SelFontSize(This,pvarSelFontSize)

#define IInkEdit_put_SelFontSize(This,pvarSelFontSize)	\
    (This)->lpVtbl -> put_SelFontSize(This,pvarSelFontSize)

#define IInkEdit_get_SelCharOffset(This,pvarSelCharOffset)	\
    (This)->lpVtbl -> get_SelCharOffset(This,pvarSelCharOffset)

#define IInkEdit_put_SelCharOffset(This,pvarSelCharOffset)	\
    (This)->lpVtbl -> put_SelCharOffset(This,pvarSelCharOffset)

#define IInkEdit_get_TextRTF(This,pbstrTextRTF)	\
    (This)->lpVtbl -> get_TextRTF(This,pbstrTextRTF)

#define IInkEdit_put_TextRTF(This,pbstrTextRTF)	\
    (This)->lpVtbl -> put_TextRTF(This,pbstrTextRTF)

#define IInkEdit_get_SelStart(This,plSelStart)	\
    (This)->lpVtbl -> get_SelStart(This,plSelStart)

#define IInkEdit_put_SelStart(This,plSelStart)	\
    (This)->lpVtbl -> put_SelStart(This,plSelStart)

#define IInkEdit_get_SelLength(This,plSelLength)	\
    (This)->lpVtbl -> get_SelLength(This,plSelLength)

#define IInkEdit_put_SelLength(This,plSelLength)	\
    (This)->lpVtbl -> put_SelLength(This,plSelLength)

#define IInkEdit_get_SelText(This,pbstrSelText)	\
    (This)->lpVtbl -> get_SelText(This,pbstrSelText)

#define IInkEdit_put_SelText(This,pbstrSelText)	\
    (This)->lpVtbl -> put_SelText(This,pbstrSelText)

#define IInkEdit_get_SelRTF(This,pbstrSelRTF)	\
    (This)->lpVtbl -> get_SelRTF(This,pbstrSelRTF)

#define IInkEdit_put_SelRTF(This,pbstrSelRTF)	\
    (This)->lpVtbl -> put_SelRTF(This,pbstrSelRTF)

#define IInkEdit_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_Status_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ InkEditStatus *pStatus);


void __RPC_STUB IInkEdit_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_UseMouseForInput_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IInkEdit_get_UseMouseForInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_UseMouseForInput_Proxy( 
    IInkEdit * This,
    /* [defaultvalue][in] */ VARIANT_BOOL newVal);


void __RPC_STUB IInkEdit_put_UseMouseForInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_InkMode_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ InkMode *pVal);


void __RPC_STUB IInkEdit_get_InkMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_InkMode_Proxy( 
    IInkEdit * This,
    /* [defaultvalue][in] */ InkMode newVal);


void __RPC_STUB IInkEdit_put_InkMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_InkInsertMode_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ InkInsertMode *pVal);


void __RPC_STUB IInkEdit_get_InkInsertMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_InkInsertMode_Proxy( 
    IInkEdit * This,
    /* [defaultvalue][in] */ InkInsertMode newVal);


void __RPC_STUB IInkEdit_put_InkInsertMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_DrawingAttributes_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ IInkDrawingAttributes **pVal);


void __RPC_STUB IInkEdit_get_DrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propputref][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_putref_DrawingAttributes_Proxy( 
    IInkEdit * This,
    /* [in] */ IInkDrawingAttributes *newVal);


void __RPC_STUB IInkEdit_putref_DrawingAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_RecognitionTimeout_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IInkEdit_get_RecognitionTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_RecognitionTimeout_Proxy( 
    IInkEdit * This,
    /* [in] */ long newVal);


void __RPC_STUB IInkEdit_put_RecognitionTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_Recognizer_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ IInkRecognizer **pVal);


void __RPC_STUB IInkEdit_get_Recognizer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propputref][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_putref_Recognizer_Proxy( 
    IInkEdit * This,
    /* [in] */ IInkRecognizer *newVal);


void __RPC_STUB IInkEdit_putref_Recognizer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_Factoid_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IInkEdit_get_Factoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_Factoid_Proxy( 
    IInkEdit * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IInkEdit_put_Factoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelInks_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT *pSelInk);


void __RPC_STUB IInkEdit_get_SelInks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelInks_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT SelInk);


void __RPC_STUB IInkEdit_put_SelInks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelInksDisplayMode_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ InkDisplayMode *pInkDisplayMode);


void __RPC_STUB IInkEdit_get_SelInksDisplayMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelInksDisplayMode_Proxy( 
    IInkEdit * This,
    /* [in] */ InkDisplayMode InkDisplayMode);


void __RPC_STUB IInkEdit_put_SelInksDisplayMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_Recognize_Proxy( 
    IInkEdit * This);


void __RPC_STUB IInkEdit_Recognize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_GetGestureStatus_Proxy( 
    IInkEdit * This,
    /* [in] */ InkApplicationGesture Gesture,
    /* [retval][out] */ VARIANT_BOOL *pListen);


void __RPC_STUB IInkEdit_GetGestureStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_SetGestureStatus_Proxy( 
    IInkEdit * This,
    /* [in] */ InkApplicationGesture Gesture,
    /* [in] */ VARIANT_BOOL Listen);


void __RPC_STUB IInkEdit_SetGestureStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_BackColor_Proxy( 
    IInkEdit * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IInkEdit_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_BackColor_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IInkEdit_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_Appearance_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ AppearanceConstants *pAppearance);


void __RPC_STUB IInkEdit_get_Appearance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_Appearance_Proxy( 
    IInkEdit * This,
    /* [in] */ AppearanceConstants pAppearance);


void __RPC_STUB IInkEdit_put_Appearance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_BorderStyle_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ BorderStyleConstants *pBorderStyle);


void __RPC_STUB IInkEdit_get_BorderStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_BorderStyle_Proxy( 
    IInkEdit * This,
    /* [in] */ BorderStyleConstants pBorderStyle);


void __RPC_STUB IInkEdit_put_BorderStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_Hwnd_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ OLE_HANDLE *pohHwnd);


void __RPC_STUB IInkEdit_get_Hwnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][bindable][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_Font_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ IFontDisp **ppFont);


void __RPC_STUB IInkEdit_get_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][bindable][propputref][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_putref_Font_Proxy( 
    IInkEdit * This,
    /* [in] */ IFontDisp *ppFont);


void __RPC_STUB IInkEdit_putref_Font_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_Text_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ BSTR *pbstrText);


void __RPC_STUB IInkEdit_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_Text_Proxy( 
    IInkEdit * This,
    /* [in] */ BSTR pbstrText);


void __RPC_STUB IInkEdit_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_MouseIcon_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ IPictureDisp **MouseIcon);


void __RPC_STUB IInkEdit_get_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_MouseIcon_Proxy( 
    IInkEdit * This,
    /* [in] */ IPictureDisp *MouseIcon);


void __RPC_STUB IInkEdit_put_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propputref][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_putref_MouseIcon_Proxy( 
    IInkEdit * This,
    /* [in] */ IPictureDisp *MouseIcon);


void __RPC_STUB IInkEdit_putref_MouseIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_MousePointer_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ InkMousePointer *MousePointer);


void __RPC_STUB IInkEdit_get_MousePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_MousePointer_Proxy( 
    IInkEdit * This,
    /* [in] */ InkMousePointer MousePointer);


void __RPC_STUB IInkEdit_put_MousePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_Locked_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IInkEdit_get_Locked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_Locked_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IInkEdit_put_Locked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_Enabled_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IInkEdit_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_Enabled_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IInkEdit_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_MaxLength_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ long *plMaxLength);


void __RPC_STUB IInkEdit_get_MaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_MaxLength_Proxy( 
    IInkEdit * This,
    /* [in] */ long lMaxLength);


void __RPC_STUB IInkEdit_put_MaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_MultiLine_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IInkEdit_get_MultiLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_MultiLine_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IInkEdit_put_MultiLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_ScrollBars_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ ScrollBarsConstants *pVal);


void __RPC_STUB IInkEdit_get_ScrollBars_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_ScrollBars_Proxy( 
    IInkEdit * This,
    /* [in] */ ScrollBarsConstants newVal);


void __RPC_STUB IInkEdit_put_ScrollBars_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_DisableNoScroll_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IInkEdit_get_DisableNoScroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_DisableNoScroll_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IInkEdit_put_DisableNoScroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelAlignment_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT *pvarSelAlignment);


void __RPC_STUB IInkEdit_get_SelAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelAlignment_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT pvarSelAlignment);


void __RPC_STUB IInkEdit_put_SelAlignment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelBold_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT *pvarSelBold);


void __RPC_STUB IInkEdit_get_SelBold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelBold_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT pvarSelBold);


void __RPC_STUB IInkEdit_put_SelBold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelItalic_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT *pvarSelItalic);


void __RPC_STUB IInkEdit_get_SelItalic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelItalic_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT pvarSelItalic);


void __RPC_STUB IInkEdit_put_SelItalic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelUnderline_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT *pvarSelUnderline);


void __RPC_STUB IInkEdit_get_SelUnderline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelUnderline_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT pvarSelUnderline);


void __RPC_STUB IInkEdit_put_SelUnderline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelColor_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT *pvarSelColor);


void __RPC_STUB IInkEdit_get_SelColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelColor_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT pvarSelColor);


void __RPC_STUB IInkEdit_put_SelColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelFontName_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT *pvarSelFontName);


void __RPC_STUB IInkEdit_get_SelFontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelFontName_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT pvarSelFontName);


void __RPC_STUB IInkEdit_put_SelFontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelFontSize_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT *pvarSelFontSize);


void __RPC_STUB IInkEdit_get_SelFontSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelFontSize_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT pvarSelFontSize);


void __RPC_STUB IInkEdit_put_SelFontSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelCharOffset_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ VARIANT *pvarSelCharOffset);


void __RPC_STUB IInkEdit_get_SelCharOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelCharOffset_Proxy( 
    IInkEdit * This,
    /* [in] */ VARIANT pvarSelCharOffset);


void __RPC_STUB IInkEdit_put_SelCharOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][defaultbind][displaybind][bindable][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_TextRTF_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ BSTR *pbstrTextRTF);


void __RPC_STUB IInkEdit_get_TextRTF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][displaybind][bindable][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_TextRTF_Proxy( 
    IInkEdit * This,
    /* [in] */ BSTR pbstrTextRTF);


void __RPC_STUB IInkEdit_put_TextRTF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelStart_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ long *plSelStart);


void __RPC_STUB IInkEdit_get_SelStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelStart_Proxy( 
    IInkEdit * This,
    /* [in] */ long plSelStart);


void __RPC_STUB IInkEdit_put_SelStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelLength_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ long *plSelLength);


void __RPC_STUB IInkEdit_get_SelLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelLength_Proxy( 
    IInkEdit * This,
    /* [in] */ long plSelLength);


void __RPC_STUB IInkEdit_put_SelLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelText_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ BSTR *pbstrSelText);


void __RPC_STUB IInkEdit_get_SelText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelText_Proxy( 
    IInkEdit * This,
    /* [in] */ BSTR pbstrSelText);


void __RPC_STUB IInkEdit_put_SelText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_get_SelRTF_Proxy( 
    IInkEdit * This,
    /* [retval][out] */ BSTR *pbstrSelRTF);


void __RPC_STUB IInkEdit_get_SelRTF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_put_SelRTF_Proxy( 
    IInkEdit * This,
    /* [in] */ BSTR pbstrSelRTF);


void __RPC_STUB IInkEdit_put_SelRTF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkEdit_Refresh_Proxy( 
    IInkEdit * This);


void __RPC_STUB IInkEdit_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkEdit_INTERFACE_DEFINED__ */


#ifndef ___IInkEditEvents_DISPINTERFACE_DEFINED__
#define ___IInkEditEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IInkEditEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IInkEditEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E3B0B797-A72E-46DB-A0D7-6C9EBA8E9BBC")
    _IInkEditEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IInkEditEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IInkEditEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IInkEditEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IInkEditEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IInkEditEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IInkEditEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IInkEditEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IInkEditEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IInkEditEventsVtbl;

    interface _IInkEditEvents
    {
        CONST_VTBL struct _IInkEditEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IInkEditEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IInkEditEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IInkEditEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IInkEditEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IInkEditEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IInkEditEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IInkEditEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IInkEditEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_InkEdit;

#ifdef __cplusplus

class DECLSPEC_UUID("E5CA59F5-57C4-4DD8-9BD6-1DEEEDD27AF4")
InkEdit;
#endif
#endif /* __INKEDLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


