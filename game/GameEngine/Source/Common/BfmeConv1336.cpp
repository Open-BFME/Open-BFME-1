// Open-BFME5 conversions.

struct BfmeGuidULA
{
	char m_bfmeBytes[16];
};

// Retail 0x0113DF00: the uuid attribute on IFEBrowserEngine2 (see
// DX8WebBrowserInitialize.cpp) makes the compiler reference this C-linkage
// GUID constant by its __GUID_<uuid> spelling, so that is the name used here.
extern "C" BfmeGuidULA __GUID_ee883b17_0778_4b18_a12b_e44c0d298412;

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

void __stdcall bfmeReportULA(long hr, BfmeThingULA *o, BfmeGuidULA *iid);

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
		bfmeReportULA(hr, this, &__GUID_ee883b17_0778_4b18_a12b_e44c0d298412);
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
