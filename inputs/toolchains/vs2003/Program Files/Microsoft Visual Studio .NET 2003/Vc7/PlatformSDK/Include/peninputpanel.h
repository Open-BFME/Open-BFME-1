//+------------------------------------------------------------------------- 
// 
//  Microsoft Windows 
//  Copyright (C) Microsoft Corporation, 2003. 
// 
//  File: peninputpanel.h 
//      Microsoft Tablet PC API definitions 
// 
//-------------------------------------------------------------------------- 
	
 	
 	

#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __peninputpanel_h__
#define __peninputpanel_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPenInputPanel_FWD_DEFINED__
#define __IPenInputPanel_FWD_DEFINED__
typedef interface IPenInputPanel IPenInputPanel;
#endif 	/* __IPenInputPanel_FWD_DEFINED__ */


#ifndef ___IPenInputPanelEvents_FWD_DEFINED__
#define ___IPenInputPanelEvents_FWD_DEFINED__
typedef interface _IPenInputPanelEvents _IPenInputPanelEvents;
#endif 	/* ___IPenInputPanelEvents_FWD_DEFINED__ */


#ifndef __PenInputPanel_FWD_DEFINED__
#define __PenInputPanel_FWD_DEFINED__

#ifdef __cplusplus
typedef class PenInputPanel PenInputPanel;
#else
typedef struct PenInputPanel PenInputPanel;
#endif /* __cplusplus */

#endif 	/* __PenInputPanel_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __PenInputPanelLib_LIBRARY_DEFINED__
#define __PenInputPanelLib_LIBRARY_DEFINED__

/* library PenInputPanelLib */
/* [helpcontext][helpstring][helpfile][version][uuid] */ 

#define MICROSOFT_PENINPUT_PANEL_PROPERTY_T	L"Microsoft PenInputPanel 1.5"
typedef /* [hidden] */ 
enum DISPID_PenInputPanel
    {	DISPID_PIPAttachedEditWindow	= DISPID_VALUE,
	DISPID_PIPFactoid	= DISPID_PIPAttachedEditWindow + 1,
	DISPID_PIPCurrentPanel	= DISPID_PIPFactoid + 1,
	DISPID_PIPDefaultPanel	= DISPID_PIPCurrentPanel + 1,
	DISPID_PIPVisible	= DISPID_PIPDefaultPanel + 1,
	DISPID_PIPTop	= DISPID_PIPVisible + 1,
	DISPID_PIPLeft	= DISPID_PIPTop + 1,
	DISPID_PIPWidth	= DISPID_PIPLeft + 1,
	DISPID_PIPHeight	= DISPID_PIPWidth + 1,
	DISPID_PIPMoveTo	= DISPID_PIPHeight + 1,
	DISPID_PIPCommitPendingInput	= DISPID_PIPMoveTo + 1,
	DISPID_PIPRefresh	= DISPID_PIPCommitPendingInput + 1,
	DISPID_PIPBusy	= DISPID_PIPRefresh + 1,
	DISPID_PIPVerticalOffset	= DISPID_PIPBusy + 1,
	DISPID_PIPHorizontalOffset	= DISPID_PIPVerticalOffset + 1,
	DISPID_PIPEnableTsf	= DISPID_PIPHorizontalOffset + 1,
	DISPID_PIPAutoShow	= DISPID_PIPEnableTsf + 1
    } 	DISPID_PenInputPanel;

typedef /* [hidden] */ 
enum DISPID_PenInputPanelEvents
    {	DISPID_PIPEVisibleChanged	= 0,
	DISPID_PIPEPanelChanged	= DISPID_PIPEVisibleChanged + 1,
	DISPID_PIPEInputFailed	= DISPID_PIPEPanelChanged + 1,
	DISPID_PIPEPanelMoving	= DISPID_PIPEInputFailed + 1
    } 	DISPID_PenInputPanelEvents;


EXTERN_C const IID LIBID_PenInputPanelLib;

#ifndef __IPenInputPanel_INTERFACE_DEFINED__
#define __IPenInputPanel_INTERFACE_DEFINED__

/* interface IPenInputPanel */
/* [helpcontext][helpstring][unique][dual][uuid][object] */ 

typedef /* [helpcontext][helpstring] */ 
enum PanelType
    {	PT_Default	= 0,
	PT_Inactive	= PT_Default + 1,
	PT_Handwriting	= PT_Inactive + 1,
	PT_Keyboard	= PT_Handwriting + 1
    } 	PanelType;


EXTERN_C const IID IID_IPenInputPanel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("fa7a4083-5747-4040-a182-0b0e9fd4fac7")
    IPenInputPanel : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Busy( 
            /* [retval][out] */ VARIANT_BOOL *Busy) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Factoid( 
            /* [retval][out] */ BSTR *Factoid) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Factoid( 
            /* [in] */ BSTR Factoid) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AttachedEditWindow( 
            /* [retval][out] */ LONG_PTR *AttachedEditWindow) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_AttachedEditWindow( 
            /* [in] */ LONG_PTR AttachedEditWindow) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CurrentPanel( 
            /* [retval][out] */ PanelType *CurrentPanel) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_CurrentPanel( 
            /* [in] */ PanelType CurrentPanel) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_DefaultPanel( 
            /* [retval][out] */ PanelType *pDefaultPanel) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_DefaultPanel( 
            /* [in] */ PanelType DefaultPanel) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL *Visible) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL Visible) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long *Top) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long *Left) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long *Width) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long *Height) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_VerticalOffset( 
            /* [retval][out] */ long *VerticalOffset) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_VerticalOffset( 
            /* [in] */ long VerticalOffset) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HorizontalOffset( 
            /* [retval][out] */ long *HorizontalOffset) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_HorizontalOffset( 
            /* [in] */ long HorizontalOffset) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AutoShow( 
            /* [retval][out] */ VARIANT_BOOL *pAutoShow) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_AutoShow( 
            /* [in] */ VARIANT_BOOL AutoShow) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ long Left,
            /* [in] */ long Top) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE CommitPendingInput( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableTsf( 
            /* [in] */ VARIANT_BOOL Enable) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPenInputPanelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPenInputPanel * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPenInputPanel * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPenInputPanel * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPenInputPanel * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPenInputPanel * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPenInputPanel * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPenInputPanel * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Busy )( 
            IPenInputPanel * This,
            /* [retval][out] */ VARIANT_BOOL *Busy);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Factoid )( 
            IPenInputPanel * This,
            /* [retval][out] */ BSTR *Factoid);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Factoid )( 
            IPenInputPanel * This,
            /* [in] */ BSTR Factoid);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AttachedEditWindow )( 
            IPenInputPanel * This,
            /* [retval][out] */ LONG_PTR *AttachedEditWindow);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_AttachedEditWindow )( 
            IPenInputPanel * This,
            /* [in] */ LONG_PTR AttachedEditWindow);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentPanel )( 
            IPenInputPanel * This,
            /* [retval][out] */ PanelType *CurrentPanel);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_CurrentPanel )( 
            IPenInputPanel * This,
            /* [in] */ PanelType CurrentPanel);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_DefaultPanel )( 
            IPenInputPanel * This,
            /* [retval][out] */ PanelType *pDefaultPanel);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_DefaultPanel )( 
            IPenInputPanel * This,
            /* [in] */ PanelType DefaultPanel);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Visible )( 
            IPenInputPanel * This,
            /* [retval][out] */ VARIANT_BOOL *Visible);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_Visible )( 
            IPenInputPanel * This,
            /* [in] */ VARIANT_BOOL Visible);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Top )( 
            IPenInputPanel * This,
            /* [retval][out] */ long *Top);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Left )( 
            IPenInputPanel * This,
            /* [retval][out] */ long *Left);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IPenInputPanel * This,
            /* [retval][out] */ long *Width);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IPenInputPanel * This,
            /* [retval][out] */ long *Height);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_VerticalOffset )( 
            IPenInputPanel * This,
            /* [retval][out] */ long *VerticalOffset);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_VerticalOffset )( 
            IPenInputPanel * This,
            /* [in] */ long VerticalOffset);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_HorizontalOffset )( 
            IPenInputPanel * This,
            /* [retval][out] */ long *HorizontalOffset);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_HorizontalOffset )( 
            IPenInputPanel * This,
            /* [in] */ long HorizontalOffset);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_AutoShow )( 
            IPenInputPanel * This,
            /* [retval][out] */ VARIANT_BOOL *pAutoShow);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE *put_AutoShow )( 
            IPenInputPanel * This,
            /* [in] */ VARIANT_BOOL AutoShow);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MoveTo )( 
            IPenInputPanel * This,
            /* [in] */ long Left,
            /* [in] */ long Top);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CommitPendingInput )( 
            IPenInputPanel * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IPenInputPanel * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableTsf )( 
            IPenInputPanel * This,
            /* [in] */ VARIANT_BOOL Enable);
        
        END_INTERFACE
    } IPenInputPanelVtbl;

    interface IPenInputPanel
    {
        CONST_VTBL struct IPenInputPanelVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPenInputPanel_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPenInputPanel_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPenInputPanel_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPenInputPanel_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPenInputPanel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPenInputPanel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPenInputPanel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPenInputPanel_get_Busy(This,Busy)	\
    (This)->lpVtbl -> get_Busy(This,Busy)

#define IPenInputPanel_get_Factoid(This,Factoid)	\
    (This)->lpVtbl -> get_Factoid(This,Factoid)

#define IPenInputPanel_put_Factoid(This,Factoid)	\
    (This)->lpVtbl -> put_Factoid(This,Factoid)

#define IPenInputPanel_get_AttachedEditWindow(This,AttachedEditWindow)	\
    (This)->lpVtbl -> get_AttachedEditWindow(This,AttachedEditWindow)

#define IPenInputPanel_put_AttachedEditWindow(This,AttachedEditWindow)	\
    (This)->lpVtbl -> put_AttachedEditWindow(This,AttachedEditWindow)

#define IPenInputPanel_get_CurrentPanel(This,CurrentPanel)	\
    (This)->lpVtbl -> get_CurrentPanel(This,CurrentPanel)

#define IPenInputPanel_put_CurrentPanel(This,CurrentPanel)	\
    (This)->lpVtbl -> put_CurrentPanel(This,CurrentPanel)

#define IPenInputPanel_get_DefaultPanel(This,pDefaultPanel)	\
    (This)->lpVtbl -> get_DefaultPanel(This,pDefaultPanel)

#define IPenInputPanel_put_DefaultPanel(This,DefaultPanel)	\
    (This)->lpVtbl -> put_DefaultPanel(This,DefaultPanel)

#define IPenInputPanel_get_Visible(This,Visible)	\
    (This)->lpVtbl -> get_Visible(This,Visible)

#define IPenInputPanel_put_Visible(This,Visible)	\
    (This)->lpVtbl -> put_Visible(This,Visible)

#define IPenInputPanel_get_Top(This,Top)	\
    (This)->lpVtbl -> get_Top(This,Top)

#define IPenInputPanel_get_Left(This,Left)	\
    (This)->lpVtbl -> get_Left(This,Left)

#define IPenInputPanel_get_Width(This,Width)	\
    (This)->lpVtbl -> get_Width(This,Width)

#define IPenInputPanel_get_Height(This,Height)	\
    (This)->lpVtbl -> get_Height(This,Height)

#define IPenInputPanel_get_VerticalOffset(This,VerticalOffset)	\
    (This)->lpVtbl -> get_VerticalOffset(This,VerticalOffset)

#define IPenInputPanel_put_VerticalOffset(This,VerticalOffset)	\
    (This)->lpVtbl -> put_VerticalOffset(This,VerticalOffset)

#define IPenInputPanel_get_HorizontalOffset(This,HorizontalOffset)	\
    (This)->lpVtbl -> get_HorizontalOffset(This,HorizontalOffset)

#define IPenInputPanel_put_HorizontalOffset(This,HorizontalOffset)	\
    (This)->lpVtbl -> put_HorizontalOffset(This,HorizontalOffset)

#define IPenInputPanel_get_AutoShow(This,pAutoShow)	\
    (This)->lpVtbl -> get_AutoShow(This,pAutoShow)

#define IPenInputPanel_put_AutoShow(This,AutoShow)	\
    (This)->lpVtbl -> put_AutoShow(This,AutoShow)

#define IPenInputPanel_MoveTo(This,Left,Top)	\
    (This)->lpVtbl -> MoveTo(This,Left,Top)

#define IPenInputPanel_CommitPendingInput(This)	\
    (This)->lpVtbl -> CommitPendingInput(This)

#define IPenInputPanel_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IPenInputPanel_EnableTsf(This,Enable)	\
    (This)->lpVtbl -> EnableTsf(This,Enable)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_Busy_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ VARIANT_BOOL *Busy);


void __RPC_STUB IPenInputPanel_get_Busy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_Factoid_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ BSTR *Factoid);


void __RPC_STUB IPenInputPanel_get_Factoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_put_Factoid_Proxy( 
    IPenInputPanel * This,
    /* [in] */ BSTR Factoid);


void __RPC_STUB IPenInputPanel_put_Factoid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_AttachedEditWindow_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ LONG_PTR *AttachedEditWindow);


void __RPC_STUB IPenInputPanel_get_AttachedEditWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_put_AttachedEditWindow_Proxy( 
    IPenInputPanel * This,
    /* [in] */ LONG_PTR AttachedEditWindow);


void __RPC_STUB IPenInputPanel_put_AttachedEditWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_CurrentPanel_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ PanelType *CurrentPanel);


void __RPC_STUB IPenInputPanel_get_CurrentPanel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_put_CurrentPanel_Proxy( 
    IPenInputPanel * This,
    /* [in] */ PanelType CurrentPanel);


void __RPC_STUB IPenInputPanel_put_CurrentPanel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_DefaultPanel_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ PanelType *pDefaultPanel);


void __RPC_STUB IPenInputPanel_get_DefaultPanel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_put_DefaultPanel_Proxy( 
    IPenInputPanel * This,
    /* [in] */ PanelType DefaultPanel);


void __RPC_STUB IPenInputPanel_put_DefaultPanel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_Visible_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ VARIANT_BOOL *Visible);


void __RPC_STUB IPenInputPanel_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_put_Visible_Proxy( 
    IPenInputPanel * This,
    /* [in] */ VARIANT_BOOL Visible);


void __RPC_STUB IPenInputPanel_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_Top_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ long *Top);


void __RPC_STUB IPenInputPanel_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_Left_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ long *Left);


void __RPC_STUB IPenInputPanel_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_Width_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ long *Width);


void __RPC_STUB IPenInputPanel_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_Height_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ long *Height);


void __RPC_STUB IPenInputPanel_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_VerticalOffset_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ long *VerticalOffset);


void __RPC_STUB IPenInputPanel_get_VerticalOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_put_VerticalOffset_Proxy( 
    IPenInputPanel * This,
    /* [in] */ long VerticalOffset);


void __RPC_STUB IPenInputPanel_put_VerticalOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_HorizontalOffset_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ long *HorizontalOffset);


void __RPC_STUB IPenInputPanel_get_HorizontalOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_put_HorizontalOffset_Proxy( 
    IPenInputPanel * This,
    /* [in] */ long HorizontalOffset);


void __RPC_STUB IPenInputPanel_put_HorizontalOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_get_AutoShow_Proxy( 
    IPenInputPanel * This,
    /* [retval][out] */ VARIANT_BOOL *pAutoShow);


void __RPC_STUB IPenInputPanel_get_AutoShow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_put_AutoShow_Proxy( 
    IPenInputPanel * This,
    /* [in] */ VARIANT_BOOL AutoShow);


void __RPC_STUB IPenInputPanel_put_AutoShow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_MoveTo_Proxy( 
    IPenInputPanel * This,
    /* [in] */ long Left,
    /* [in] */ long Top);


void __RPC_STUB IPenInputPanel_MoveTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_CommitPendingInput_Proxy( 
    IPenInputPanel * This);


void __RPC_STUB IPenInputPanel_CommitPendingInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_Refresh_Proxy( 
    IPenInputPanel * This);


void __RPC_STUB IPenInputPanel_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IPenInputPanel_EnableTsf_Proxy( 
    IPenInputPanel * This,
    /* [in] */ VARIANT_BOOL Enable);


void __RPC_STUB IPenInputPanel_EnableTsf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPenInputPanel_INTERFACE_DEFINED__ */


#ifndef ___IPenInputPanelEvents_DISPINTERFACE_DEFINED__
#define ___IPenInputPanelEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IPenInputPanelEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IPenInputPanelEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("b7e489da-3719-439f-848f-e7acbd820f17")
    _IPenInputPanelEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPenInputPanelEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IPenInputPanelEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IPenInputPanelEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IPenInputPanelEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IPenInputPanelEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IPenInputPanelEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IPenInputPanelEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IPenInputPanelEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IPenInputPanelEventsVtbl;

    interface _IPenInputPanelEvents
    {
        CONST_VTBL struct _IPenInputPanelEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPenInputPanelEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IPenInputPanelEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IPenInputPanelEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IPenInputPanelEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IPenInputPanelEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IPenInputPanelEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IPenInputPanelEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPenInputPanelEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PenInputPanel;

#ifdef __cplusplus

class DECLSPEC_UUID("f744e496-1b5a-489e-81dc-fbd7ac6298a8")
PenInputPanel;
#endif
#endif /* __PenInputPanelLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


