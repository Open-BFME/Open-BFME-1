// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#ifndef __ATLEVENT_H__
#define __ATLEVENT_H__

#define __ATLEVENT_VER 3

#pragma once

#ifndef __cplusplus
		#error ATL requires C++ compilation (use a .cpp suffix)
#endif

struct __EventingCriticalSectionStub {
   void Lock() {}
   void Unlock() {}
};

struct __EventingCriticalSectionAuto {
	void EmitError(TCHAR* csError) {
		static const int nMax = 256;
		static const TCHAR szMessage[] = _T("cannot initialize critical section(Error ");
		static const int nMessageLen = sizeof(szMessage)/sizeof(szMessage[0]) - 1;
		TCHAR buf[nMax];
		lstrcpy( buf, szMessage ); // the buffer is large enough, no need to check the return value
		lstrcpyn( buf + nMessageLen, csError, nMax - nMessageLen );
		MessageBox(0, buf, 0, MB_OK | MB_ICONHAND);
	}
	void Lock() {
		__try {
			EnterCriticalSection(&m_sec);
		} __except(EXCEPTION_EXECUTE_HANDLER) {
			TCHAR* csError = (STATUS_NO_MEMORY == GetExceptionCode()) ? _T("E_OUTOFMEMORY") : _T("E_FAIL");
			EmitError(csError);
		}
	}
	void Unlock() {
		LeaveCriticalSection(&m_sec);
	}
	__EventingCriticalSectionAuto() {
		__try {
			InitializeCriticalSection(&m_sec);
		} __except(EXCEPTION_EXECUTE_HANDLER) {
			TCHAR* csError = (STATUS_NO_MEMORY == GetExceptionCode()) ? _T("E_OUTOFMEMORY") : _T("E_FAIL");
			EmitError(csError);
		}
	}
	~__EventingCriticalSectionAuto() { 
		DeleteCriticalSection(&m_sec); 
	}
	CRITICAL_SECTION m_sec;
};

template <class T>
struct __eventingGetAddr {
	typedef void (T::*pmfn_type) ();
	typedef void (*pgfn_type) ();
	union U {
		void *addr;
		void (T::*pmfn)();
		void (*pgfn)();
	};
	static pmfn_type __getMAddr(void *addr) {
		U u;
		u.addr = addr;
		return u.pmfn;
	}
	static void* __getVAddr(pmfn_type pmfn) {
		U u;
		u.pmfn = pmfn;
		return u.addr;
	}
	static pgfn_type __getSMAddr(void *addr) {
		U u;
		u.addr = addr;
		return u.pgfn;
	}
	static void* __getSVAddr(pgfn_type pgfn) {
		U u;
		u.pgfn = pgfn;
		return u.addr;
	}
};

struct __eventNode {
	virtual int __isEqual(void*, void*) = 0;
	virtual int __isEqual(void*) = 0;
	__eventNode* next;
};

struct __eventMainNode {
	int key;
	__eventNode* root_node;
	__eventMainNode* next_event;
};

//
// pvargSrc should only contain the memory for a VARIANT
//
inline HRESULT WINAPI __VariantChangeType(/*[in,out]*/VARIANTARG*& pvargDest, /*[in]*/VARIANTARG* pvargSrc, VARTYPE vt) {
	ATLASSERT(pvargDest != 0 && pvargSrc != 0);
	if( pvargDest == 0 || pvargSrc == 0 )
		return E_INVALIDARG;
	ATLTRACE(_T("ATLEVENT: __VariantChangeType(pvargDest->vt=%d,vt=%d)\n"), pvargDest->vt, vt);

	const static char okToConvert[] = {
		0, 0, 1, 1, 1, 1, 0, 1, 0, 0,   // VT_EMPTY,VT_NULL,VT_I2,VT_I4,VT_R4,VT_R8,VT_CY,VT_DATE,VT_BSTR,VT_DISPATCH
		1, 1, 0, 0, 0, 0, 1, 1, 1, 1,   // VT_ERROR,VT_BOOL,VT_VARIANT,VT_UNKNOWN,VT_DECIMAL,VT_I1,VT_UI1,VT_UI2,VT_UI4 
		1, 1, 1, 1, 0, 1, 0, 0, 0, 0,   // VT_I8,VT_UI8,VT_INT,VT_UINT,VT_VOID,VT_HRESULT,VT_PTR,VT_SAFEARRAY,VT_CARRAY,VT_USERDEFINED
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	const static char truncateTo[] = {
		0, 0, 2, 3, 3, 0, 0, 0, 0, 0,   // VT_EMPTY,VT_NULL,VT_I2,VT_I4,VT_R4,VT_R8,VT_CY,VT_DATE,VT_BSTR,VT_DISPATCH
		3, 2, 0, 0, 0, 0, 1, 1, 2, 3,   // VT_ERROR,VT_BOOL,VT_VARIANT,VT_UNKNOWN,VT_DECIMAL,VT_I1,VT_UI1,VT_UI2,VT_UI4
		0, 0, 3, 3, 0, 3, 0, 0, 0, 0,   // VT_I8,VT_UI8,VT_INT,VT_UINT,VT_VOID,VT_HRESULT,VT_PTR,VT_SAFEARRAY,VT_CARRAY,VT_USERDEFINED
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	ATLASSERT((pvargDest->vt & ~(VT_BYREF | VT_ARRAY)) < sizeof(okToConvert)/sizeof(okToConvert[0]));
	ATLASSERT((vt & ~(VT_BYREF | VT_ARRAY)) < sizeof(okToConvert)/sizeof(okToConvert[0]));

	const static unsigned __int64 masks[] = {
		0xFFFFFFFFFFFFFFFF,
		0x00000000000000FF,
		0x000000000000FFFF,
		0x00000000FFFFFFFF
	};

	if (pvargDest->vt == (VT_VARIANT | VT_BYREF)) {
		pvargDest = V_VARIANTREF(pvargDest);
	}

	if (((pvargDest->vt & VT_BYREF) ^ (vt & VT_BYREF)) && (vt & VT_ARRAY) == 0) {
		return DISP_E_TYPEMISMATCH;
	} else if ((vt & VT_ARRAY) == 0 && (pvargDest->vt & VT_ARRAY) == 0 
		&& okToConvert[vt & ~VT_BYREF] != 0 
		&& okToConvert[pvargDest->vt & ~VT_BYREF] != 0) {        
		if ((vt & VT_BYREF) == 0 && truncateTo[pvargDest->vt] != 0) {
			V_UI8(pvargDest) = V_UI8(pvargDest) & masks[truncateTo[pvargDest->vt]];
		}
		return S_OK;
	} else {
		::VariantInit(pvargSrc);
		HRESULT hr = ::VariantChangeType(pvargSrc, pvargDest, 0, vt);
		if (FAILED(hr)) {
			if (hr == DISP_E_TYPEMISMATCH && (vt & VT_ARRAY) != 0 && (pvargDest->vt & ~VT_BYREF) == (VT_ARRAY | VT_VARIANT)) {
				return S_OK; // you're on your own
			}
		} else {
			::VariantClear(pvargDest);
			*pvargDest = *pvargSrc;
		}
		return hr;
	}
}

HRESULT WINAPI _com_handle_excepinfo(EXCEPINFO& excepInfo, IErrorInfo** pperrinfo);

namespace ATL {
	inline HRESULT
	__ComInvokeEventHandler(IDispatch* pDispatch, DISPID id, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult) {
		if (pVarResult != 0) {
			::VariantInit(pVarResult);
		}
		EXCEPINFO excepInfo;
		memset(&excepInfo, 0, sizeof excepInfo);
		UINT nArgErr = (UINT)-1;
		HRESULT hr = pDispatch->Invoke(id, IID_NULL, LOCALE_USER_DEFAULT, wFlags, pDispParams, pVarResult, &excepInfo, &nArgErr);
		if (FAILED(hr)) {
			IErrorInfo* perrinfo = 0;
			if (SUCCEEDED(_com_handle_excepinfo(excepInfo, &perrinfo)))
			{
				SetErrorInfo(0, perrinfo);
				perrinfo->Release();
			}
		}
		return hr;
	}

	struct __EventHandlerProxy {
		virtual HRESULT CDECL __eventHandlerProxy(int idx, ...) = 0;
	};
	struct __EventHandlerNodeProxy {
		virtual int __Index(int i) = 0;
	};
	template <typename T /*super*/>
	class __ComEventingImpl : public __EventHandlerProxy {
		enum { __InvalidIndex = -1 };
		struct __ComEventingNode : __EventHandlerNodeProxy {
			__ComEventingNode(T* pThis = 0, IUnknown* pSource = 0, IUnknown* pSink = 0,
				const _GUID* pGuid = 0, int nSize = 0) {
				__pThis = pThis;
				__nHooks = 0;
				__dwAdvise = 0;
				__pSource = pSource;
				__pSink = pSink;
				__pNext = 0;
				__pGuid = const_cast<_GUID*> (pGuid);
				__nArraySize = nSize;
				__proxyIndex = NULL;
				__proxyIndex = new int[__nArraySize];
				memset(__proxyIndex, 0xff, __nArraySize*sizeof(int));
			}
			int __Index(int i) {
				return __proxyIndex[i];
			}
			T* __pThis;
			int *__proxyIndex;
			int __nArraySize;
			int __nHooks;
			unsigned long __dwAdvise;
			IUnknown* __pSource;
			IUnknown* __pSink;
			_GUID* __pGuid;
			__ComEventingNode* __pNext;
		};
		__ComEventingNode* __pFirst;
		__ComEventingNode* __pLast;
		__ComEventingNode* __pCurrent;
	public:
		__ComEventingImpl() {
			__pCurrent = __pFirst = __pLast = 0;
		}
		~__ComEventingImpl() {
			if (__pFirst != 0) {
				__pCurrent = __pFirst;
				while (__pCurrent != 0) {
					__pCurrent->__pSink->Release();
					delete [] __pCurrent->__proxyIndex;
					__pFirst = __pCurrent;
					__pCurrent = __pCurrent->__pNext;
					delete __pFirst;
				}
			}
		}
		template <typename U /*interface*/>
		HRESULT __WhichThis(IUnknown* pS, T* pThis, int nSize, bool bNext, int idx) {
			if (bNext) {
				 if (__pCurrent != 0) {
					 __pCurrent = __pCurrent->__pNext;
				 }
			} else {
				__pCurrent = __pFirst;
			}
			if (__pCurrent == 0
				|| __pCurrent->__pSource != pS
				|| __pCurrent->__pThis != pThis
				|| !IsEqualGUID(*U::Guid(), *__pCurrent->__pGuid)) {
				if (__pCurrent != 0) {
					__ComEventingNode* pTheOne = 0;
					while ((__pCurrent = __pCurrent->__pNext) != 0) {
						if (__pCurrent->__pSource == pS
							&& (__pCurrent->__pThis == pThis)
							&& IsEqualGUID(*U::Guid(), *__pCurrent->__pGuid)) {
							if (nSize > 0 || __pCurrent->__proxyIndex[idx] != __InvalidIndex) {
								pTheOne = __pCurrent;
								if (nSize > 0) {
									break;
								}
							}
						 }
					 }
					 if (pTheOne != 0) {
						 __pCurrent = pTheOne;
						 return S_OK;
					 }
				}
				if (nSize > 0) {
					CComObject<U>* pSink;
					HRESULT hr = CComObject<U>::CreateInstance(&pSink);
					if (FAILED(hr)) {
						return hr;
					}
					pSink->AddRef();
					pSink->__pThis = pThis;
					ATLTRY( pSink->__pThat = __pCurrent = new __ComEventingNode(pThis, pS, pSink, U::Guid(), nSize) );
					if( pSink->__pThat == NULL )
						return E_OUTOFMEMORY;
					if (__pLast != 0) {
						__pLast->__pNext = __pCurrent;
					} else {
						__pFirst = __pCurrent;
					}
					__pLast = __pCurrent;
				}
			}
			return S_OK;
		}
		template <typename U /*interface*/>
		HRESULT __AddHandler(T* pThis, int idxSink, IUnknown* pS, int idx, int nSize) {
			if (pS == 0 || pThis == 0) {
				return E_FAIL;
			}
			bool bNext = false;
			bool bDone = false;
			while (!bDone) {
				HRESULT hr = __WhichThis<U>(pS, pThis, nSize, bNext, idx);
				if (SUCCEEDED(hr)) {
					if (__pCurrent->__proxyIndex[idx] == __InvalidIndex) {
						__pCurrent->__proxyIndex[idx] = idxSink;
						++__pCurrent->__nHooks;
						__pCurrent->__pThis = pThis;
						bDone = true;
					}
					if (__pCurrent->__dwAdvise == 0) {
						return AtlAdvise(pS, __pCurrent->__pSink, *U::Guid(), &__pCurrent->__dwAdvise);
					}
					bNext = true;
				} else {
					return hr;
				}
			}
			return S_OK;
		}
		template <typename U /*interface*/>
		HRESULT __RemoveHandler(T* pThis, IUnknown* pS, int idx) {
			bool bNext = false;
			bool bDone = false;
			while (!bDone) {
				__WhichThis<U>(pS, pThis, 0, bNext, idx);
				if (__pCurrent == 0) {
					return E_FAIL;
				}
				if (__pCurrent->__proxyIndex[idx] != __InvalidIndex) {
					__pCurrent->__proxyIndex[idx] = __InvalidIndex;
					--__pCurrent->__nHooks;
					bDone = true;
				}
				if (__pCurrent->__dwAdvise != 0 && __pCurrent->__nHooks == 0) {
					HRESULT hr = AtlUnadvise(pS, *U::Guid(), __pCurrent->__dwAdvise);
					if (SUCCEEDED(hr)) {
						__pCurrent->__dwAdvise = 0;
					}
					return hr;
				}
				bNext = true;
			}
			return S_OK;
		}
		HRESULT __RemoveAllHandlers(IUnknown* pS, const _GUID* pIID) {
			HRESULT hr = E_FAIL;
			__pCurrent = __pFirst;
			while (1) {
				if (__pCurrent == 0) {
					return hr;
				} else if ((pS == 0 || __pCurrent->__pSource == pS
					&& (pIID == 0 || IsEqualGUID(*pIID, *__pCurrent->__pGuid)))
					&& __pCurrent->__dwAdvise != 0) {
					hr = AtlUnadvise(__pCurrent->__pSource, *__pCurrent->__pGuid, __pCurrent->__dwAdvise);
					if (SUCCEEDED(hr)) {
						__pCurrent->__dwAdvise = 0;
						memset(__pCurrent->__proxyIndex, 0xff, __pCurrent->__nArraySize*sizeof(int));
						__pCurrent->__nHooks = 0;
					}
				}
				__pCurrent = __pCurrent->__pNext;
			}
		}
	};

	class __ComEventingImpl_LD {
		struct __EventCookieNode {
			__EventCookieNode(IUnknown* pS = 0, const _GUID* pG = 0) {
				__nextCookie = 0;
				__dwAdvise = 0;
				__pSource = pS;
				__pGuid = const_cast<_GUID*> (pG);
			}
			__EventCookieNode* __nextCookie;
			unsigned long __dwAdvise;
			IUnknown* __pSource;
			_GUID* __pGuid;
		} *__EventCookies;
	public:
		HRESULT __Advise(IUnknown* pSrc, IUnknown* pSink, const IID& iid) {
			__EventCookieNode* pRoot = __EventCookies;
			while (pRoot != 0) {
				if (pSrc == pRoot->__pSource
					&& IsEqualGUID(iid, *pRoot->__pGuid)
					&& pRoot->__dwAdvise == 0) {
					break;
				}
				pRoot = pRoot->__nextCookie;
			}
			if (pRoot == 0) {
				ATLTRY( pRoot = new __EventCookieNode(pSrc, &iid) );
				if( pRoot == NULL )
					return E_OUTOFMEMORY;
				pRoot->__nextCookie = __EventCookies;
				__EventCookies = pRoot;
			}
			return AtlAdvise(pSrc, pSink, iid, &pRoot->__dwAdvise);
		}
		HRESULT __Unadvise(IUnknown* pSrc, const IID& iid) {
			__EventCookieNode* pRoot = __EventCookies;
			__EventCookieNode* pTheOne = 0;
			while (pRoot != 0) {
				if (pSrc == pRoot->__pSource
					&& IsEqualGUID(iid, *pRoot->__pGuid)
					&& pRoot->__dwAdvise != 0) {
					pTheOne = pRoot;
				}
				pRoot = pRoot->__nextCookie;
			}
			HRESULT hr = E_FAIL;
			if (pTheOne != 0) {
				hr = AtlUnadvise(pSrc, iid, pTheOne->__dwAdvise);
				if (SUCCEEDED(hr)) {
					pTheOne->__dwAdvise = 0;
				}
			}
			return hr;
		}
		__ComEventingImpl_LD() {
			__EventCookies = 0;
		}
		~__ComEventingImpl_LD() {
			while (__EventCookies != 0) {
				__EventCookieNode* pDead = __EventCookies;
				__EventCookies = __EventCookies->__nextCookie;
				delete pDead;
			}
		}
	};
}

#endif // __ATLEVENT_H__
