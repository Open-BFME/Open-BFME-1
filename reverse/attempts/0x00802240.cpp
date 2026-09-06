// ?bfmeLookupFJ@BfmeTableFJ@@QAEPAXPBD@Z (identity unknown)
// partial score=0.95 date=2026-09-06
// 43/44; sole residue is add eax,0x2b8 where retail uses lea edx,[ecx+0x2b8].
// Pin: ?bfmeFindFJ@@YGHPAUBfmeMapFJ@@PBD@Z,0x007F76F0
struct BfmeMapFJ
{
	unsigned char m_bfmeMapDataFJ[8];
};

int __stdcall bfmeFindFJ(BfmeMapFJ *map, const char *key);

class BfmeOwnerFJ
{
public:
	unsigned char m_bfmeHeadFJ[0x2b8];
	BfmeMapFJ m_bfmeMapFJ;
};

class BfmeTableFJ
{
public:
	void *bfmeLookupFJ(const char *key);

	unsigned char m_bfmeHeadFJ[4];
	BfmeOwnerFJ *m_bfmeOwnerFJ;
	unsigned char m_bfmeMidFJ[0x20];
	void **m_bfmeSlotsFJ;
};

void *BfmeTableFJ::bfmeLookupFJ(const char *key)
{
	BfmeMapFJ *map = &m_bfmeOwnerFJ->m_bfmeMapFJ;
	const char *name = key;
	int index = bfmeFindFJ(map, name);
	if (index == -1)
		return 0;

	return m_bfmeSlotsFJ[index];
}
