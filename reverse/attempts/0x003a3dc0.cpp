// ?bfmeGoFK@BfmeOwnerFK@@QAEXPAX@Z (identity unknown)
// partial score=0.95 date=2026-09-06
// 47/48; retail widens the byte member with xor ecx,ecx + mov cl (5 bytes),
// MSVC uses movzx ecx,byte ptr (4). Everything else matches.
// Pins: find 0x00009615, apply 0x0003D893, global 0x00EF706C.
class BfmeThingFK
{
public:
	void bfmeApplyFK(void *first, void *second, void *third, int flag);
};

class BfmeGameFK
{
public:
	BfmeThingFK *bfmeFindFK(void *key);
};

extern BfmeGameFK *g_bfmeGameFK;

class BfmeOwnerFK
{
public:
	void bfmeGoFK(void *key);

	unsigned char m_bfmeHeadFK[4];
	unsigned char m_bfmeAFK[8];
	unsigned char m_bfmeBFK[0x11];
	unsigned char m_bfmeFlagFK;
	unsigned char m_bfmeMidFK[0x2a];
	unsigned char m_bfmeCFK[4];
};

void BfmeOwnerFK::bfmeGoFK(void *key)
{
	BfmeThingFK *thing = g_bfmeGameFK->bfmeFindFK(key);
	thing->bfmeApplyFK(m_bfmeAFK, m_bfmeBFK, m_bfmeCFK, m_bfmeFlagFK);
}
