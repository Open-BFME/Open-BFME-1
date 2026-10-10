// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/toolchains/vs2003/PROG~FBU/MICR~2RR.NET/Vc7/PLAT~MIB/Include
// Open-BFME5 conversions.

// Retail COM error helper at RVA00AFD550 is the vendored comsupp body.
#include <objbase.h>
extern void __stdcall _com_issue_errorex(HRESULT, IUnknown *, const IID &);
// The interface UUID is witnessed by DX8WebBrowserInitialize.cpp and its retail
// 16-byte constant at VA0113DF00; let VC7.1 emit its native UUID symbol.
struct __declspec(uuid("ee883b17-0778-4b18-a12b-e44c0d298412")) IFEBrowserEngine2;

class BfmeThingULA;

struct BfmeVtULA
{
	void *m_bfmeSlot0;
	void *m_bfmeSlot1;
	void *m_bfmeSlot2;
	void *m_bfmeSlot3;
	void *m_bfmeSlot4;
	void *m_bfmeSlot5;
	void *m_bfmeSlot6;
	void *m_bfmeSlot7;
	void *m_bfmeSlot8;
	void *m_bfmeSlot9;
	void *m_bfmeSlot10;
	void *m_bfmeSlot11;
	void *m_bfmeSlot12;
	void *m_bfmeSlot13;
	long (__stdcall *m_bfmeCallULA)(BfmeThingULA *self, void *a);
};

class BfmeThingULA
{
public:
	long bfmeGoULA(void *a);
	BfmeVtULA *m_bfmeVt;
};

long BfmeThingULA::bfmeGoULA(void *a)
{
	long hr = m_bfmeVt->m_bfmeCallULA(this, a);
	if (hr < 0)
		_com_issue_errorex(hr, reinterpret_cast<IUnknown *>(this), __uuidof(IFEBrowserEngine2));
	return hr;
}

class BfmeResULD
{
public:
	char m_bfmePad[4];
	unsigned short m_bfmeRefs;
};

// Retail releases the outgoing resource through the shared counted-texture base
// leaf ?Release_Ref@TextureBaseClass@@QAEXXZ (0x009EB7A0), out of line.
class TextureBaseClass
{
public:
	void Release_Ref();
};

class BfmeThingULD
{
public:
	void bfmeSetULD(BfmeResULD *r);
	TextureBaseClass *m_bfmeCur;
};

void BfmeThingULD::bfmeSetULD(BfmeResULD *r)
{
	if (!r)
		return;
	++r->m_bfmeRefs;
	if (m_bfmeCur)
		m_bfmeCur->Release_Ref();
	m_bfmeCur = (TextureBaseClass *)r;
}
