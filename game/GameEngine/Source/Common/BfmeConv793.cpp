// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep
#include <stdio.h>
#include "windows.h"
#include "oleauto.h"
#include "Mss.H"

// retail 0x009F68C6 is the matched body
// ?RemoveAll@Rva009F68C6PointerArray@@QAEXXZ; this call site reaches it
// through the same address, so the call is spelled with its defining name.
class Rva009F68C6PointerArray
{
public:
	void RemoveAll();
};

struct BfmeThingDXB
{
	void bfmeGoDXB();
	unsigned char m_bfmeHead[0x18];
	CRITICAL_SECTION m_bfmeCs;
	Rva009F68C6PointerArray m_bfmeSub;
};

void BfmeThingDXB::bfmeGoDXB()
{
	DeleteCriticalSection(&m_bfmeCs);
	m_bfmeSub.RemoveAll();
}

struct BfmeThingDXC
{
	void bfmeGoDXC();
	void bfmeTailDXC();
	unsigned char m_bfmeHead[0x48];
	FILE *m_bfmeP;
};

void BfmeThingDXC::bfmeGoDXC()
{
	fclose(m_bfmeP);
	bfmeTailDXC();
}

extern "C" __declspec(dllimport) S32 __stdcall AIL_3D_sample_status(H3DSAMPLE h);

struct BfmeThingDXD
{
	bool bfmeGoDXD();
	unsigned char m_bfmeHead[4];
	H3DSAMPLE m_bfmeH;
};

bool BfmeThingDXD::bfmeGoDXD()
{
	void *h = m_bfmeH;
	if (!h)
		return true;
	return AIL_3D_sample_status(h) != 4;
}

extern "C" __declspec(dllimport) HRESULT __stdcall VariantClear(VARIANT *what);
extern VARIANT g_bfmeArgDXE;
// comutil.h declares `void __stdcall _com_issue_error(HRESULT)`; the sweep
// comutil.h shim does not, so the declaration is repeated here under its exact
// defining spelling (?_com_issue_error@@YGXJ@Z).
extern void __stdcall _com_issue_error(long);

void bfmeGoDXE()
{
	int r = VariantClear(&g_bfmeArgDXE);
	if (r < 0)
		_com_issue_error((long)r);
}

extern "C" __declspec(dllimport) DWORD WINAPI GetFileType(HANDLE a);

bool bfmeGoDXF(void *a)
{
	return (GetFileType(a) & 0xffff7fff) == 1;
}
