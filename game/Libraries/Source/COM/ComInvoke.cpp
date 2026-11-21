// cl: /O2 /G6 /Ob2 /EHsc /GR /DNDEBUG /MD /Iinputs/toolchains/vs2003/Vc7/PlatformSDK/Include
// [BFME 2 donor] Authored INVKPRXY recovery; original B1 member owns all four routines.
// Donor 147fd3e52b36ee0306aaeef5b316beb09f7c7671, current _com_error.cpp,
// historical Code/Libraries/Source/COM/ComInvoke.cpp; no _com_error class is copied.
// The original compiler GUID symbol and its 16 zero bytes establish __uuidof(0).
#include <oaidl.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>
HRESULT __stdcall _com_handle_excepinfo(EXCEPINFO&,IErrorInfo**);

HRESULT __cdecl _com_invoke_helper(IDispatch *dispatch,long id,unsigned short flags,unsigned short retType,void *result,const wchar_t *types,char *args,IErrorInfo **out) {
 if(!dispatch)return E_POINTER;
 if(out)*out=0;
 DISPPARAMS dp;memset(&dp,0,sizeof(dp));
 if(types)dp.cArgs=lstrlenW((LPCWSTR)types);
 DISPID named=DISPID_PROPERTYPUT;
 if(flags & (DISPATCH_PROPERTYPUT|DISPATCH_PROPERTYPUTREF)) {
  if(!dp.cArgs)return E_INVALIDARG;
  dp.cNamedArgs=1;dp.rgdispidNamedArgs=&named;
 }
 if(dp.cArgs>0) {
  VARIANTARG *base;
  __try {base=(VARIANTARG*)_alloca(dp.cArgs*sizeof(VARIANTARG));}
  __except(1) {return HRESULT_FROM_WIN32(GetLastError());}
  memset(base,0,dp.cArgs*sizeof(VARIANTARG));
  dp.rgvarg=base;
  const wchar_t *type=types;
  VARIANTARG *vARIANTARG=base+dp.cArgs-1;
  for(;*type;--vARIANTARG,++type) {
   vARIANTARG->vt=*type & 0xF7FF;
   switch(vARIANTARG->vt) {
   case VT_I2: case VT_UI2: vARIANTARG->iVal=va_arg(args,short);break;
   case VT_I4: case VT_ERROR: case VT_UI4: case VT_HRESULT: vARIANTARG->lVal=va_arg(args,long);break;
   case VT_BSTR: vARIANTARG->bstrVal=va_arg(args,BSTR);break;
   case VT_DISPATCH: vARIANTARG->pdispVal=va_arg(args,IDispatch*);break;
   case VT_UNKNOWN: vARIANTARG->punkVal=va_arg(args,IUnknown*);break;
   case VT_INT: vARIANTARG->intVal=va_arg(args,int);break;
   case VT_UINT: vARIANTARG->uintVal=va_arg(args,unsigned);break;
   case VT_RECORD: vARIANTARG->byref=va_arg(args,void*);break;
   case VT_R4: vARIANTARG->vt=VT_R8;
   case VT_R8: case VT_DATE: memcpy(&vARIANTARG->dblVal,&va_arg(args,double),sizeof(double));break;
   case VT_I8: vARIANTARG->llVal=va_arg(args,LONGLONG);break;
   case VT_UI8: vARIANTARG->ullVal=va_arg(args,ULONGLONG);break;
   case VT_CY: vARIANTARG->cyVal=*va_arg(args,CY*);break;
   case VT_BOOL: vARIANTARG->boolVal=va_arg(args,short)?VARIANT_TRUE:VARIANT_FALSE;break;
   case VT_VARIANT: *vARIANTARG=*va_arg(args,VARIANT*);break;
   case VT_DECIMAL: vARIANTARG->decVal=*va_arg(args,DECIMAL*);vARIANTARG->vt=VT_DECIMAL;break;
   case VT_I1: case VT_UI1: vARIANTARG->bVal=va_arg(args,BYTE);break;
#define REF(T) case VT_BYREF|T:
   REF(VT_I2) REF(VT_I4) REF(VT_R4) REF(VT_R8) REF(VT_CY) REF(VT_DATE)
   REF(VT_BSTR) REF(VT_DISPATCH) REF(VT_ERROR) REF(VT_BOOL) REF(VT_VARIANT)
   REF(VT_UNKNOWN) REF(VT_DECIMAL) REF(VT_I1) REF(VT_UI1) REF(VT_UI2)
   REF(VT_UI4) REF(VT_I8) REF(VT_UI8) REF(VT_INT) REF(VT_UINT) REF(VT_HRESULT) REF(VT_RECORD)
    vARIANTARG->byref=va_arg(args,void*);break;
#undef REF
   default: if(vARIANTARG->vt&VT_ARRAY)vARIANTARG->parray=va_arg(args,SAFEARRAY*);else return E_INVALIDARG;
   }
  }
  vARIANTARG=base+dp.cNamedArgs;
  const wchar_t *tailType=types+dp.cArgs-dp.cNamedArgs-1;
  unsigned removed=0;
  for(;tailType>=types;++vARIANTARG,--tailType) {
   if((*tailType & ~VT_BYREF)!=0x080C)break;
   VARIANT *probe=(*tailType & VT_BYREF)?vARIANTARG->pvarVal:vARIANTARG;
   if(probe->vt!=VT_ERROR || probe->scode!=DISP_E_PARAMNOTFOUND)break;
   ++removed;
  }
  if(removed>0) {
   for(unsigned i=0;i<dp.cNamedArgs;++i)base[i+removed]=base[i];
   dp.cArgs-=removed;dp.rgvarg+=removed;
  }
 }
 VARIANT value;VariantInit(&value);
 EXCEPINFO ex;memset(&ex,0,sizeof(ex));unsigned argerr=-1;
 HRESULT hr=dispatch->Invoke(id,__uuidof(0),0,flags,&dp,retType?&value:0,&ex,&argerr);
 if(hr<0) {
  VariantClear(&value);
  if(hr==DISP_E_EXCEPTION)return _com_handle_excepinfo(ex,out);
  return hr;
 }
 if(retType && result) {
  if(retType!=VT_VARIANT && retType!=value.vt) {
   hr=VariantChangeType(&value,&value,0,retType);
   if(hr<0) {VariantClear(&value);return hr;}
  }
  // Keep the native type-list order and one success exit. In particular,
  // HRESULT is the SCODE copy, and RECORD plus its BYREF extension cases
  // copy the opaque pointer bits. Retail's tables prove these shared paths.
  switch(retType) {
  case VT_I2: *(short*)result=value.iVal;goto done;
  case VT_I4: *(long*)result=value.lVal;goto done;
  case VT_R4: *(float*)result=value.fltVal;goto done;
  case VT_R8: *(double*)result=value.dblVal;goto done;
  case VT_DATE: *(DATE*)result=value.date;goto done;
  case VT_CY: *(CY*)result=value.cyVal;goto done;
  case VT_BSTR: *(BSTR*)result=value.bstrVal;goto done;
  case VT_DISPATCH: *(IDispatch**)result=value.pdispVal;goto done;
  case VT_HRESULT: case VT_ERROR: *(SCODE*)result=value.scode;goto done;
  case VT_BOOL: *(VARIANT_BOOL*)result=value.boolVal;goto done;
  case VT_VARIANT: *(VARIANT*)result=value;goto done;
  case VT_UNKNOWN: *(IUnknown**)result=value.punkVal;goto done;
  case VT_DECIMAL: *(DECIMAL*)result=value.decVal;goto done;
  case VT_I1: *(char*)result=value.cVal;goto done;
  case VT_UI1: *(BYTE*)result=value.bVal;goto done;
  case VT_UI2: *(unsigned short*)result=value.uiVal;goto done;
  case VT_UI4: *(unsigned long*)result=value.ulVal;goto done;
  case VT_INT: *(int*)result=value.intVal;goto done;
  case VT_UINT: *(unsigned*)result=value.uintVal;goto done;
  case VT_I8: *(LONGLONG*)result=value.llVal;goto done;
  case VT_UI8: *(ULONGLONG*)result=value.ullVal;goto done;
  case VT_BYREF|VT_HRESULT: case VT_BYREF|VT_RECORD: case VT_RECORD: *(void**)result=value.pvRecord;goto done;
#define REF(T,F,P) case VT_BYREF|T: *(P**)result=value.F;goto done;
  REF(VT_I2,piVal,short)
  REF(VT_I4,plVal,long)
  REF(VT_R4,pfltVal,float)
  REF(VT_R8,pdblVal,double)
  REF(VT_DATE,pdate,DATE)
  REF(VT_CY,pcyVal,CY)
  REF(VT_BSTR,pbstrVal,BSTR)
  REF(VT_DISPATCH,ppdispVal,IDispatch*)
  REF(VT_ERROR,pscode,SCODE)
  REF(VT_BOOL,pboolVal,VARIANT_BOOL)
  REF(VT_VARIANT,pvarVal,VARIANT)
  REF(VT_UNKNOWN,ppunkVal,IUnknown*)
  REF(VT_DECIMAL,pdecVal,DECIMAL)
  REF(VT_I1,pcVal,char)
  REF(VT_UI1,pbVal,BYTE)
  REF(VT_UI2,puiVal,unsigned short)
  REF(VT_UI4,pulVal,unsigned long)
  REF(VT_INT,pintVal,int)
  REF(VT_UINT,puintVal,unsigned)
  REF(VT_I8,pllVal,LONGLONG)
  REF(VT_UI8,pullVal,ULONGLONG)
#undef REF
  default:
   if(retType&VT_ARRAY)*(SAFEARRAY**)result=value.parray;
   else {VariantClear(&value);return E_INVALIDARG;}
  }
 }
 done:
 return hr;
}

HRESULT __cdecl _com_dispatch_raw_method(IDispatch *dispatch,long id,unsigned short flags,unsigned short type,void *result,const wchar_t *types,...) {
 va_list args;va_start(args,types);IErrorInfo *error;
 HRESULT hr=_com_invoke_helper(dispatch,id,flags,type,result,types,args,&error);
 if(hr<0)SetErrorInfo(0,error);return hr;
}

HRESULT __stdcall _com_dispatch_raw_propget(IDispatch *dispatch,long id,unsigned short type,void *result) {
 return _com_dispatch_raw_method(dispatch,id,2,type,result,0);
}

HRESULT __cdecl _com_dispatch_raw_propput(IDispatch *dispatch,long id,unsigned short type,...) {
 wchar_t types[2]={type,0};unsigned short flags=(type==9 || type==13)?8:4;
 va_list args;va_start(args,type);IErrorInfo *error;
 HRESULT hr=_com_invoke_helper(dispatch,id,flags,0,0,types,args,&error);
 if(hr<0)SetErrorInfo(0,error);return hr;
}
