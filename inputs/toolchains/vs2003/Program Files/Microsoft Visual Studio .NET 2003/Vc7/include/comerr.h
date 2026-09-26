#include <comdef.h>

#ifndef _PCEH_DEFINED
typedef void (__stdcall * _PCEH)(HRESULT, IUnknown *, REFIID);
#define _PCEH_DEFINED
#endif

_PCEH __stdcall _query_com_error_handler();
_PCEH __stdcall _set_com_error_handler(_PCEH);
void  __stdcall _call_com_error_handler(HRESULT, IUnknown *, REFIID);
