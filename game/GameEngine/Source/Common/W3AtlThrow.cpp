// cl: /DNDEBUG /MD /EHsc
// ATL-style HRESULT throw helper shared by the recovered conversion routines.

typedef long HRESULT;

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
