struct BfmeEntryYW
{
	unsigned char m_bfmeHeadYW[0x1c];
	unsigned char m_bfmeFieldYW[8];
};

struct BfmeVecYW
{
	unsigned char m_bfmeHeadYW[0x2c];
	BfmeEntryYW *m_bfmeBeginYW;
	BfmeEntryYW *volatile m_bfmeEndYW;
};

void __cdecl bfmeParseAsciiYW(void *ini, void *inst, void *field, const void *extra);

void __cdecl bfmeParseYW(void *ini, void *inst, BfmeVecYW *store)
{
	if (store->m_bfmeEndYW - store->m_bfmeBeginYW != 0)
		bfmeParseAsciiYW(ini, inst, store->m_bfmeEndYW[-1].m_bfmeFieldYW, 0);
}
