// cl: /Ob2 /EHsc /DNDEBUG /MD /Iinputs/toolchains/vs2003/Vc7/PlatformSDK/Include
#include <oaidl.h>
// Authored from retail and the MSVC 7.1 invkerr.obj symbol identities.
// SDK headers supply declarations only; no implementation source was read.
// [BFME 2 donor] B1 original invkerr.obj owns both complete bodies (26+248B).
// Shared ComError.h reconciles the existing authored canonical declaration with
// native B1 CodeView char* storage at12. Only the static API is defined here;
// constructors/destructors and all class metadata retain their native providers.
#include "ComError.h"
typedef char ComErrorSize[sizeof(_com_error)==16?1:-1];
inline long _com_error::WCodeToHRESULT(unsigned short code) {
 return code>=0xfe00 ? (long)0x8004ffff : (long)(0x80040200+(unsigned int)code);
}

HRESULT __stdcall _com_handle_excepinfo(EXCEPINFO& excep,IErrorInfo **out) {
 if(excep.pfnDeferredFillIn)excep.pfnDeferredFillIn(&excep);
 ICreateErrorInfo *created=0;
 if(out && CreateErrorInfo(&created)>=0) {
  created->SetGUID(__uuidof(IDispatch));
  if(excep.bstrSource)created->SetSource(excep.bstrSource);
  if(excep.bstrDescription)created->SetDescription(excep.bstrDescription);
  if(excep.bstrHelpFile)created->SetHelpFile(excep.bstrHelpFile);
  created->SetHelpContext(excep.dwHelpContext);
  if(created->QueryInterface(__uuidof(IErrorInfo),(void**)out)<0)*out=0;
  created->Release();
 }
 if(excep.bstrSource)SysFreeString(excep.bstrSource);
 if(excep.bstrDescription)SysFreeString(excep.bstrDescription);
 if(excep.bstrHelpFile)SysFreeString(excep.bstrHelpFile);
 if(excep.wCode)return _com_error::WCodeToHRESULT(excep.wCode);
 return excep.scode;
}
