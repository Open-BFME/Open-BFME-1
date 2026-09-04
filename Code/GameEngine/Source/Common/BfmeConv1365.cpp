// Open-BFME5 conversions.

bool __cdecl _bfme_debugReportingEnabled();
void __cdecl bfmeRecordVHJ(int n);

class BfmeMsgVHJ
{
public:
	virtual void bfmeSlot00VHJ();
	virtual void bfmeSlot04VHJ();
	virtual void bfmeSlot08VHJ();
	virtual void bfmeSlot0CVHJ();
	virtual void bfmeSlot10VHJ();
	virtual void bfmeSlot14VHJ();
	virtual void bfmeSlot18VHJ();
	virtual void bfmeSlot1CVHJ();
	virtual void bfmeSlot20VHJ();
	virtual void bfmeSlot24VHJ();
	virtual void bfmeSlot28VHJ();
	virtual void bfmeSlot2CVHJ();
	virtual void bfmeSlot30VHJ();
	virtual void bfmeSlot34VHJ();
	virtual class BfmeMsgVHJ *bfmeSlot38VHJ(const char *t);
	virtual void bfmeSlot3CVHJ();
	virtual void bfmeSlot40VHJ();
	virtual void bfmeSlot44VHJ();
	virtual void bfmeSlot48VHJ();
	virtual void bfmeSlot4cVHJ(int n);
	virtual void bfmeSlot50VHJ();
	virtual void bfmeSlot54VHJ();
	virtual void bfmeSlot58VHJ();
	virtual void bfmeSlot5CVHJ();
	virtual void bfmeSlot60VHJ();
	virtual void bfmeSlot64VHJ();
	virtual void bfmeSlot68VHJ();
	virtual void bfmeSlot6CVHJ();
};

class BfmeLogVHJ
{
public:
	virtual void bfmeOwn00VHJ();
	virtual void bfmeOwn04VHJ();
	virtual void bfmeOwn08VHJ();
	virtual void bfmeOwn0CVHJ();
	virtual void bfmeOwn10VHJ();
	virtual void bfmeOwn14VHJ();
	virtual void bfmeOwn18VHJ();
	virtual void bfmeOwn1CVHJ();
	virtual void bfmeOwn20VHJ();
	virtual void bfmeOwn24VHJ();
	virtual void bfmeOwn28VHJ();
	virtual void bfmeOwn2CVHJ();
	virtual void bfmeOwn30VHJ();
	virtual void bfmeOwn34VHJ();
	virtual void bfmeOwn38VHJ();
	virtual void bfmeOwn3CVHJ();
	virtual void bfmeOwn40VHJ();
	virtual void bfmeOwn44VHJ();
	virtual void bfmeOwn48VHJ();
	virtual void bfmeOwn4CVHJ();
	virtual void bfmeOwn50VHJ();
	virtual void bfmeOwn54VHJ();
	virtual void bfmeOwn58VHJ();
	virtual void bfmeOwn5CVHJ();
	virtual void bfmeOwn60VHJ();
	virtual void bfmeOwn64VHJ();
	virtual void bfmeOwn68VHJ();
	virtual class BfmeMsgVHJ *bfmeOwn6cVHJ(int a, int b);
};

extern BfmeLogVHJ *g_bfmeLogVHJ;

class BfmeNameVHN
{
public:
	char bfmeIsRawVHN();
};

class BfmeTexVHN
{
public:
	virtual void bfmeTex00VHN();
	virtual void bfmeTex04VHN();
	virtual void bfmeTex08VHN();
	virtual void bfmeTex0CVHN();
	virtual void bfmeTex10VHN();
	virtual void bfmeTex14VHN();
	virtual void bfmeTex18VHN();
	virtual void bfmeTex1CVHN();
	virtual void bfmeTex20VHN();
	virtual void bfmeTex24VHN();
	virtual char bfmeTex28VHN();
	virtual void bfmeTex2CVHN();
	virtual void bfmeTex30VHN();
	char m_bfmePad[0x10];
	BfmeNameVHN *m_bfme14;
	const char *m_bfme18;
	char m_bfmePad2[0x18];
	int m_bfme34;
};

class BfmeThingVHN
{
public:
	void bfmeGoVHN(int code);
	BfmeTexVHN *m_bfmeTex;
};

void BfmeThingVHN::bfmeGoVHN(int code)
{
	BfmeTexVHN *t = m_bfmeTex;
	bool ok = (code >= 0x3c && code <= 0x40);
	if (!t)
		return;
	t->m_bfme34 = code;
	if (!ok)
		return;
	if (!m_bfmeTex)
		return;
	if (!m_bfmeTex->bfmeTex28VHN())
		return;
	if (t->m_bfme14->bfmeIsRawVHN())
		return;
	if (_bfme_debugReportingEnabled())
	{
		bfmeRecordVHJ(1);
		g_bfmeLogVHJ->bfmeOwn60VHJ();
		g_bfmeLogVHJ->bfmeOwn6cVHJ(0, 0)->bfmeSlot38VHJ("Texture '")->bfmeSlot38VHJ(t->m_bfme18)->bfmeSlot38VHJ("' is not a bump map format. Use run/art/textures/_convert_textures.bat to save as a v8u8 dds format to eliminate redundant loads.")->bfmeSlot4cVHJ(2);
	}
	t->bfmeTex30VHN();
}
