// cl: /O2 /G6 /Ob2 /EHsc /GR /DNDEBUG /MD /Iinputs/toolchains/vs2003/Vc7/PlatformSDK/Include
// [BFME 2 donor] Authored five-function ComRaise section from official1e864b34.
// Original B1 comraise.obj defines the complete251B family and150B metadata.
// Ordinary inline preserves original SELECT_ANY provenance; the genuine throw,
// copy/destructor metadata and virtual table are the only emission anchors.
// The verified shared declaration is reused unchanged; no Microsoft implementation
// body or private class copy is included.
#include "ComError.h"
#include <new>
#include <oaidl.h>

// Authored from retail and native MSVC7.1 comraise.obj identities.
// Shared ABI is recorded in class_contracts/_com_error.json; source uses
// canonical SDK declarations, not Microsoft implementation source.

inline _com_error::_com_error(long value,IErrorInfo *error,bool addRef)
 :result(value),info(error),message(0)
{
 if(info && addRef)info->AddRef();
}

inline _com_error::_com_error(const _com_error& other)
 :result(other.result),info(other.info),message(0)
{
 if(info)info->AddRef();
}

inline _com_error::~_com_error()
{
 if(info)info->Release();
 if(message)LocalFree((HLOCAL)message);
}

void __stdcall _com_raise_error(long value,IErrorInfo *error)
{
 throw _com_error(value,error,false);
}

