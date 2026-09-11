// cl: /O1 /Oy- /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The retail CD3DXSkinInfo vtable at 0x01149088 places this body in slot 0;
// twenty-four neighboring slots name CD3DXSkinInfo.  The original
// createmesh.obj body carries IID_IUnknown and IID_ID3DXSkinInfo relocations,
// independently separating this implementation from the masked-identical
// D3DX QueryInterface bodies.

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
extern "C" const GUID IID_ID3DXSkinInfo;
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

class CD3DXSkinInfo
{
public:
	virtual HRESULT __stdcall QueryInterface(const GUID &iid, void **object);
	virtual ULONG __stdcall AddRef() = 0;
};

HRESULT __stdcall CD3DXSkinInfo::QueryInterface(
	const GUID &iid, void **object)
{
	*object = 0;
	if (iid == IID_IUnknown)
	{
		*object = this;
		AddRef();
		return 0;
	}
	if (iid == IID_ID3DXSkinInfo)
	{
		*object = this;
		AddRef();
		return 0;
	}
	return (HRESULT)0x80004002L;
}
