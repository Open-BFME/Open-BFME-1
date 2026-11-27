// cl: /Ob2 /EHsc /DNDEBUG /MD /Iinputs/toolchains/vs2003/Vc7/PlatformSDK/Include
// [BFME 2 donor] 147fd3e52b36ee0306aaeef5b316beb09f7c7671.
// Authored from retail and the existing MSVC 7.1 comsupp.obj identities.
// Implementation provenance: authored BFME 2 ComSupp.cpp; no _com_error body is copied.
// Original native COFF/CV independently establishes the six-routine member.
// The existing generated _com_issue_error owner is retained unchanged because
// the native admission API refuses its move; the other five bodies are here.
// Native data and relocations independently establish the callback and GUID.
// IUnknown slots 0..2 and ISupportErrorInfo slot 3 are proven by these calls.
#include <stdarg.h>
// Canonical toolchain SDK interface declarations; function bodies below are authored.
#include <oaidl.h>
void __stdcall _com_raise_error(HRESULT,IErrorInfo*);
typedef void (__stdcall *ErrorHandler)(HRESULT,IErrorInfo*);
ErrorHandler __errorPfn=_com_raise_error;
HRESULT __cdecl _com_invoke_helper(IDispatch*,long,unsigned short,unsigned short,void*,const wchar_t*,char*,IErrorInfo**);

void __stdcall _com_issue_errorex(HRESULT hr,IUnknown *unknown,const _GUID& iid) {
 IErrorInfo *error=0;
 if(unknown && unknown->QueryInterface(__uuidof(ISupportErrorInfo),(void**)&unknown)>=0) {
  HRESULT support=((ISupportErrorInfo*)unknown)->InterfaceSupportsErrorInfo(iid);
  unknown->Release();
  if(support==0 && GetErrorInfo(0,&error)!=0)error=0;
 }
 __errorPfn(hr,error);
}

void __stdcall _set_com_error_handler(ErrorHandler callback) {__errorPfn=callback;}

HRESULT __cdecl _com_dispatch_method(IDispatch *dispatch,long id,unsigned short flags,unsigned short type,void *result,const wchar_t *types,...) {
 va_list args;va_start(args,types);
 IErrorInfo *error;
 HRESULT hr=_com_invoke_helper(dispatch,id,flags,type,result,types,args,&error);
 if(hr<0)__errorPfn(hr,error);
 return hr;
}

HRESULT __stdcall _com_dispatch_propget(IDispatch *dispatch,long id,unsigned short type,void *result) {
 return _com_dispatch_method(dispatch,id,2,type,result,0);
}

HRESULT __cdecl _com_dispatch_propput(IDispatch *dispatch,long id,unsigned short type,...) {
 wchar_t types[2]={type,0};
 unsigned short flags=(type==9 || type==13)?8:4;
 va_list args;va_start(args,type);
 IErrorInfo *error;
 HRESULT hr=_com_invoke_helper(dispatch,id,flags,0,0,types,args,&error);
 if(hr<0)__errorPfn(hr,error);
 return hr;
}
