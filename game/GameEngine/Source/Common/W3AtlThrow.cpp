// cl: /DNDEBUG /MD /EHsc
// ATL-style HRESULT throw helper shared by the recovered conversion routines.
// __TI1?AVCAtlException@ATL@@: recorded as __TI1?AVCAtlException@@ at 0x011DF9A0

#include "../../Include/Common/ScalarTypes/Win32/HRESULT.h"

class CAtlException
{
public:
	CAtlException(HRESULT hr) { m_hr = hr; }
	HRESULT m_hr;
};

extern "C" __declspec(noreturn) void __stdcall W3AtlThrow(HRESULT hr)
{
	throw CAtlException(hr);
}
