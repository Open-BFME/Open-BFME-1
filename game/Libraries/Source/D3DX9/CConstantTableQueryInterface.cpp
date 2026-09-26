// cl: /O1 /Oy- /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The retail D3DXShader::CConstantTable vtable at 0x0114D7C8 places this
// QueryInterface body in slot 0.  Twenty-one neighboring slots name the same
// class, resolving the older archive-order ambiguity for this address.

typedef unsigned long ULONG;
typedef long HRESULT;

struct _GUID
{
	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
};
typedef _GUID GUID;

extern "C" const GUID IID_IUnknown;
extern "C" const GUID IID_ID3DXBuffer;
extern "C" const GUID IID_ID3DXConstantTable;
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

__inline int IsEqualGUID(const GUID &left, const GUID &right)
{
	return memcmp(&left, &right, sizeof(GUID)) == 0;
}

__inline int operator==(const GUID &left, const GUID &right)
{
	return IsEqualGUID(left, right);
}

__inline int operator!=(const GUID &left, const GUID &right)
{
	return !(left == right);
}

namespace D3DXShader
{
	class CConstantTable
	{
	public:
		virtual HRESULT __stdcall QueryInterface(const GUID &iid, void **object);
		virtual ULONG __stdcall AddRef() = 0;
	};

	HRESULT __stdcall CConstantTable::QueryInterface(
		const GUID &iid, void **object)
	{
		*object = 0;
		if (iid == IID_IUnknown)
		{
			*object = this;
			AddRef();
			return 0;
		}
		if (iid == IID_ID3DXBuffer)
		{
			*object = this;
			AddRef();
			return 0;
		}
		if (iid == IID_ID3DXConstantTable)
		{
			*object = this;
			AddRef();
			return 0;
		}
		return (HRESULT)0x80004002L;
	}
}
