// ?bfmeLookupEQO@BfmeTableEQO@@QAEHPBD0@Z (identity unknown)
// partial score=0.9 date=2026-09-06
// 82/82 bytes, instruction order identical; residue is scratch-register choice only.
// Pins needed: ?bfmeFindEQO@@YGHPAUBfmeMapEQO@@PBD@Z,0x007F76F0 and
//              ?bfmeAppendEQO@BfmeSlotEQO@@QAEXPBD@Z,0x008002C0
struct BfmeSlotEQO
{
	void bfmeAppendEQO(const char *text);
	unsigned char m_bfmeSlotDataEQO[8];
};

struct BfmeMapEQO
{
	unsigned char m_bfmeMapDataEQO[8];
};

struct BfmeOwnerEQO
{
	BfmeMapEQO *bfmeFirstMapEQO(void) { return &m_bfmeFirstMapEQO; }
	BfmeMapEQO *bfmeSecondMapEQO(void) { return &m_bfmeSecondMapEQO; }
	unsigned char m_bfmeHeadEQO[0x2a8];
	BfmeMapEQO m_bfmeFirstMapEQO;
	BfmeMapEQO m_bfmeSecondMapEQO;
};

int __stdcall bfmeFindEQO(BfmeMapEQO *map, const char *key);

struct BfmeTableEQO
{
	int bfmeLookupEQO(const char *key, const char *text);
	unsigned char m_bfmeHeadEQO[4];
	BfmeOwnerEQO *m_bfmeOwnerEQO;
	unsigned char m_bfmeMidEQO[8];
	BfmeSlotEQO *m_bfmeSlotsEQO;
	int m_bfmeCountEQO;
};

int BfmeTableEQO::bfmeLookupEQO(const char *key, const char *text)
{
	int index = bfmeFindEQO(m_bfmeOwnerEQO->bfmeFirstMapEQO(), key);
	if (index == -1)
		return -106;
	BfmeSlotEQO *slot;
	if (index >= m_bfmeCountEQO)
		slot = 0;
	else
		slot = &m_bfmeSlotsEQO[index];
	slot->bfmeAppendEQO(text);
	return 0;
}
