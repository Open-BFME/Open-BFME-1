
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* Compiler settings for msinkaut15.idl:
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


#ifndef __msinkaut15_h__
#define __msinkaut15_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IInkDivider_FWD_DEFINED__
#define __IInkDivider_FWD_DEFINED__
typedef interface IInkDivider IInkDivider;
#endif 	/* __IInkDivider_FWD_DEFINED__ */


#ifndef __IInkDivisionResult_FWD_DEFINED__
#define __IInkDivisionResult_FWD_DEFINED__
typedef interface IInkDivisionResult IInkDivisionResult;
#endif 	/* __IInkDivisionResult_FWD_DEFINED__ */


#ifndef __IInkDivisionUnit_FWD_DEFINED__
#define __IInkDivisionUnit_FWD_DEFINED__
typedef interface IInkDivisionUnit IInkDivisionUnit;
#endif 	/* __IInkDivisionUnit_FWD_DEFINED__ */


#ifndef __IInkDivisionUnits_FWD_DEFINED__
#define __IInkDivisionUnits_FWD_DEFINED__
typedef interface IInkDivisionUnits IInkDivisionUnits;
#endif 	/* __IInkDivisionUnits_FWD_DEFINED__ */


#ifndef __InkDivider_FWD_DEFINED__
#define __InkDivider_FWD_DEFINED__

#ifdef __cplusplus
typedef class InkDivider InkDivider;
#else
typedef struct InkDivider InkDivider;
#endif /* __cplusplus */

#endif 	/* __InkDivider_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "msinkaut.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_msinkaut15_0000 */
/* [local] */ 

#include <TPCError.h> // for Tablet PC Error codes




extern RPC_IF_HANDLE __MIDL_itf_msinkaut15_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_msinkaut15_0000_v0_0_s_ifspec;


#ifndef __MSINKDIVLib_LIBRARY_DEFINED__
#define __MSINKDIVLib_LIBRARY_DEFINED__

/* library MSINKDIVLib */
/* [helpcontext][helpstring][helpfile][version][uuid] */ 

typedef /* [helpcontext][helpstring] */ 
enum InkDivisionType
    {	IDT_Segment	= 0,
	IDT_Line	= 1,
	IDT_Paragraph	= 2,
	IDT_Drawing	= 3
    } 	InkDivisionType;

typedef /* [hidden] */ 
enum DISPID_InkDivider
    {	DISPID_IInkDivider_Strokes	= 1,
	DISPID_IInkDivider_RecognizerContext	= DISPID_IInkDivider_Strokes + 1,
	DISPID_IInkDivider_LineHeight	= DISPID_IInkDivider_RecognizerContext + 1,
	DISPID_IInkDivider_Divide	= DISPID_IInkDivider_LineHeight + 1
    } 	DISPID_InkDivider;

typedef /* [hidden] */ 
enum DISPID_InkDivisionResult
    {	DISPID_IInkDivisionResult_Strokes	= 1,
	DISPID_IInkDivisionResult_ResultByType	= DISPID_IInkDivisionResult_Strokes + 1
    } 	DISPID_InkDivisionResult;

typedef /* [hidden] */ 
enum DISPID_InkDivisionUnit
    {	DISPID_IInkDivisionUnit_Strokes	= 1,
	DISPID_IInkDivisionUnit_DivisionType	= DISPID_IInkDivisionUnit_Strokes + 1,
	DISPID_IInkDivisionUnit_RecognizedString	= DISPID_IInkDivisionUnit_DivisionType + 1,
	DISPID_IInkDivisionUnit_RotationTransform	= DISPID_IInkDivisionUnit_RecognizedString + 1
    } 	DISPID_InkDivisionUnit;

typedef /* [hidden] */ 
enum DISPID_InkDivisionUnits
    {	DISPID_IInkDivisionUnits_NewEnum	= DISPID_NEWENUM,
	DISPID_IInkDivisionUnits_Item	= DISPID_VALUE,
	DISPID_IInkDivisionUnits_Count	= 1
    } 	DISPID_InkDivisionUnits;


EXTERN_C const IID LIBID_MSINKDIVLib;

#ifndef __IInkDivider_INTERFACE_DEFINED__
#define __IInkDivider_INTERFACE_DEFINED__

/* interface IInkDivider */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkDivider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5DE00405-F9A4-4651-B0C5-C317DEFD58B9")
    IInkDivider : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Strokes( 
            /* [in] */ IInkStrokes *Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecognizerContext( 
            /* [retval][out] */ IInkRecognizerContext **RecognizerContext) = 0;
        
        virtual /* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_RecognizerContext( 
            /* [in] */ IInkRecognizerContext *RecognizerContext) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LineHeight( 
            /* [retval][out] */ LONG *LineHeight) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LineHeight( 
            /* [in] */ LONG LineHeight) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Divide( 
            /* [retval][out] */ IInkDivisionResult **InkDivisionResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkDividerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkDivider * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkDivider * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkDivider * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkDivider * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkDivider * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkDivider * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkDivider * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strokes )( 
            IInkDivider * This,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Strokes )( 
            IInkDivider * This,
            /* [in] */ IInkStrokes *Strokes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecognizerContext )( 
            IInkDivider * This,
            /* [retval][out] */ IInkRecognizerContext **RecognizerContext);
        
        /* [helpcontext][helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_RecognizerContext )( 
            IInkDivider * This,
            /* [in] */ IInkRecognizerContext *RecognizerContext);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LineHeight )( 
            IInkDivider * This,
            /* [retval][out] */ LONG *LineHeight);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LineHeight )( 
            IInkDivider * This,
            /* [in] */ LONG LineHeight);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Divide )( 
            IInkDivider * This,
            /* [retval][out] */ IInkDivisionResult **InkDivisionResult);
        
        END_INTERFACE
    } IInkDividerVtbl;

    interface IInkDivider
    {
        CONST_VTBL struct IInkDividerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkDivider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkDivider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkDivider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkDivider_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkDivider_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkDivider_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkDivider_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkDivider_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkDivider_putref_Strokes(This,Strokes)	\
    (This)->lpVtbl -> putref_Strokes(This,Strokes)

#define IInkDivider_get_RecognizerContext(This,RecognizerContext)	\
    (This)->lpVtbl -> get_RecognizerContext(This,RecognizerContext)

#define IInkDivider_putref_RecognizerContext(This,RecognizerContext)	\
    (This)->lpVtbl -> putref_RecognizerContext(This,RecognizerContext)

#define IInkDivider_get_LineHeight(This,LineHeight)	\
    (This)->lpVtbl -> get_LineHeight(This,LineHeight)

#define IInkDivider_put_LineHeight(This,LineHeight)	\
    (This)->lpVtbl -> put_LineHeight(This,LineHeight)

#define IInkDivider_Divide(This,InkDivisionResult)	\
    (This)->lpVtbl -> Divide(This,InkDivisionResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDivider_get_Strokes_Proxy( 
    IInkDivider * This,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkDivider_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkDivider_putref_Strokes_Proxy( 
    IInkDivider * This,
    /* [in] */ IInkStrokes *Strokes);


void __RPC_STUB IInkDivider_putref_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDivider_get_RecognizerContext_Proxy( 
    IInkDivider * This,
    /* [retval][out] */ IInkRecognizerContext **RecognizerContext);


void __RPC_STUB IInkDivider_get_RecognizerContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IInkDivider_putref_RecognizerContext_Proxy( 
    IInkDivider * This,
    /* [in] */ IInkRecognizerContext *RecognizerContext);


void __RPC_STUB IInkDivider_putref_RecognizerContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDivider_get_LineHeight_Proxy( 
    IInkDivider * This,
    /* [retval][out] */ LONG *LineHeight);


void __RPC_STUB IInkDivider_get_LineHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IInkDivider_put_LineHeight_Proxy( 
    IInkDivider * This,
    /* [in] */ LONG LineHeight);


void __RPC_STUB IInkDivider_put_LineHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDivider_Divide_Proxy( 
    IInkDivider * This,
    /* [retval][out] */ IInkDivisionResult **InkDivisionResult);


void __RPC_STUB IInkDivider_Divide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkDivider_INTERFACE_DEFINED__ */


#ifndef __IInkDivisionResult_INTERFACE_DEFINED__
#define __IInkDivisionResult_INTERFACE_DEFINED__

/* interface IInkDivisionResult */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkDivisionResult;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2DBEC0A7-74C7-4B38-81EB-AA8EF0C24900")
    IInkDivisionResult : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ResultByType( 
            /* [in] */ InkDivisionType divisionType,
            /* [retval][out] */ IInkDivisionUnits **InkDivisionUnits) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkDivisionResultVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkDivisionResult * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkDivisionResult * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkDivisionResult * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkDivisionResult * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkDivisionResult * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkDivisionResult * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkDivisionResult * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strokes )( 
            IInkDivisionResult * This,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ResultByType )( 
            IInkDivisionResult * This,
            /* [in] */ InkDivisionType divisionType,
            /* [retval][out] */ IInkDivisionUnits **InkDivisionUnits);
        
        END_INTERFACE
    } IInkDivisionResultVtbl;

    interface IInkDivisionResult
    {
        CONST_VTBL struct IInkDivisionResultVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkDivisionResult_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkDivisionResult_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkDivisionResult_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkDivisionResult_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkDivisionResult_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkDivisionResult_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkDivisionResult_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkDivisionResult_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkDivisionResult_ResultByType(This,divisionType,InkDivisionUnits)	\
    (This)->lpVtbl -> ResultByType(This,divisionType,InkDivisionUnits)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDivisionResult_get_Strokes_Proxy( 
    IInkDivisionResult * This,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkDivisionResult_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDivisionResult_ResultByType_Proxy( 
    IInkDivisionResult * This,
    /* [in] */ InkDivisionType divisionType,
    /* [retval][out] */ IInkDivisionUnits **InkDivisionUnits);


void __RPC_STUB IInkDivisionResult_ResultByType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkDivisionResult_INTERFACE_DEFINED__ */


#ifndef __IInkDivisionUnit_INTERFACE_DEFINED__
#define __IInkDivisionUnit_INTERFACE_DEFINED__

/* interface IInkDivisionUnit */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkDivisionUnit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("85AEE342-48B0-4244-9DD5-1ED435410FAB")
    IInkDivisionUnit : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Strokes( 
            /* [retval][out] */ IInkStrokes **Strokes) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DivisionType( 
            /* [retval][out] */ InkDivisionType *divisionType) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecognizedString( 
            /* [retval][out] */ BSTR *RecoString) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RotationTransform( 
            /* [retval][out] */ IInkTransform **RotationTransform) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkDivisionUnitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkDivisionUnit * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkDivisionUnit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkDivisionUnit * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkDivisionUnit * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkDivisionUnit * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkDivisionUnit * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkDivisionUnit * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Strokes )( 
            IInkDivisionUnit * This,
            /* [retval][out] */ IInkStrokes **Strokes);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DivisionType )( 
            IInkDivisionUnit * This,
            /* [retval][out] */ InkDivisionType *divisionType);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecognizedString )( 
            IInkDivisionUnit * This,
            /* [retval][out] */ BSTR *RecoString);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RotationTransform )( 
            IInkDivisionUnit * This,
            /* [retval][out] */ IInkTransform **RotationTransform);
        
        END_INTERFACE
    } IInkDivisionUnitVtbl;

    interface IInkDivisionUnit
    {
        CONST_VTBL struct IInkDivisionUnitVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkDivisionUnit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkDivisionUnit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkDivisionUnit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkDivisionUnit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkDivisionUnit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkDivisionUnit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkDivisionUnit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkDivisionUnit_get_Strokes(This,Strokes)	\
    (This)->lpVtbl -> get_Strokes(This,Strokes)

#define IInkDivisionUnit_get_DivisionType(This,divisionType)	\
    (This)->lpVtbl -> get_DivisionType(This,divisionType)

#define IInkDivisionUnit_get_RecognizedString(This,RecoString)	\
    (This)->lpVtbl -> get_RecognizedString(This,RecoString)

#define IInkDivisionUnit_get_RotationTransform(This,RotationTransform)	\
    (This)->lpVtbl -> get_RotationTransform(This,RotationTransform)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDivisionUnit_get_Strokes_Proxy( 
    IInkDivisionUnit * This,
    /* [retval][out] */ IInkStrokes **Strokes);


void __RPC_STUB IInkDivisionUnit_get_Strokes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDivisionUnit_get_DivisionType_Proxy( 
    IInkDivisionUnit * This,
    /* [retval][out] */ InkDivisionType *divisionType);


void __RPC_STUB IInkDivisionUnit_get_DivisionType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDivisionUnit_get_RecognizedString_Proxy( 
    IInkDivisionUnit * This,
    /* [retval][out] */ BSTR *RecoString);


void __RPC_STUB IInkDivisionUnit_get_RecognizedString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDivisionUnit_get_RotationTransform_Proxy( 
    IInkDivisionUnit * This,
    /* [retval][out] */ IInkTransform **RotationTransform);


void __RPC_STUB IInkDivisionUnit_get_RotationTransform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkDivisionUnit_INTERFACE_DEFINED__ */


#ifndef __IInkDivisionUnits_INTERFACE_DEFINED__
#define __IInkDivisionUnits_INTERFACE_DEFINED__

/* interface IInkDivisionUnits */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInkDivisionUnits;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1BB5DDC2-31CC-4135-AB82-2C66C9F00C41")
    IInkDivisionUnits : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *Count) = 0;
        
        virtual /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **_NewEnum) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ long Index,
            /* [retval][out] */ IInkDivisionUnit **InkDivisionUnit) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInkDivisionUnitsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IInkDivisionUnits * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IInkDivisionUnits * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IInkDivisionUnits * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IInkDivisionUnits * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IInkDivisionUnits * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IInkDivisionUnits * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IInkDivisionUnits * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IInkDivisionUnits * This,
            /* [retval][out] */ long *Count);
        
        /* [helpcontext][helpstring][restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IInkDivisionUnits * This,
            /* [retval][out] */ IUnknown **_NewEnum);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Item )( 
            IInkDivisionUnits * This,
            /* [in] */ long Index,
            /* [retval][out] */ IInkDivisionUnit **InkDivisionUnit);
        
        END_INTERFACE
    } IInkDivisionUnitsVtbl;

    interface IInkDivisionUnits
    {
        CONST_VTBL struct IInkDivisionUnitsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInkDivisionUnits_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInkDivisionUnits_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInkDivisionUnits_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInkDivisionUnits_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInkDivisionUnits_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInkDivisionUnits_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInkDivisionUnits_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInkDivisionUnits_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IInkDivisionUnits_get__NewEnum(This,_NewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,_NewEnum)

#define IInkDivisionUnits_Item(This,Index,InkDivisionUnit)	\
    (This)->lpVtbl -> Item(This,Index,InkDivisionUnit)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDivisionUnits_get_Count_Proxy( 
    IInkDivisionUnits * This,
    /* [retval][out] */ long *Count);


void __RPC_STUB IInkDivisionUnits_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IInkDivisionUnits_get__NewEnum_Proxy( 
    IInkDivisionUnits * This,
    /* [retval][out] */ IUnknown **_NewEnum);


void __RPC_STUB IInkDivisionUnits_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IInkDivisionUnits_Item_Proxy( 
    IInkDivisionUnits * This,
    /* [in] */ long Index,
    /* [retval][out] */ IInkDivisionUnit **InkDivisionUnit);


void __RPC_STUB IInkDivisionUnits_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInkDivisionUnits_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_InkDivider;

#ifdef __cplusplus

class DECLSPEC_UUID("8854F6A0-4683-4AE7-9191-752FE64612C3")
InkDivider;
#endif
#endif /* __MSINKDIVLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


