// cl: /DNDEBUG /MD /EHsc
#include "../WWLib/wwstring.h"
#pragma intrinsic(strlen, memcpy)
extern "C" const char *__stdcall DXGetErrorString9A(long hresult);

class Debug
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual Debug &WriteInt(long);
	virtual void v12();
	virtual void v13();
	virtual Debug &WriteString(const char *);
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void SetPrefixAndRadix(const char *, int);
};

// Open BFME 2 donor: Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp.
// ?DX8ErrorTranslator@@YA_NAAVDebug@@JPAX@Z
bool __cdecl DX8ErrorTranslator(Debug &debug, long hresult, void *user)
{
    StringClass error(DXGetErrorString9A(hresult));
    Debug &first = debug.WriteString("0x");
    first.SetPrefixAndRadix("0x", 16);
    Debug &number = first.WriteInt(hresult);
    number.SetPrefixAndRadix("", 10);
    number.WriteString(" (").WriteString((const char *)error).WriteString(")");
    return true;
}
