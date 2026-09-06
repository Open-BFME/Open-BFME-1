// ?bfmeFetchBI@BfmeOwnBI@@QAEXPAPAVBfmeRefBI@@@Z (identity unknown)
// partial score=0.87 date=2026-09-06
// 40/46 at exact size and exact structure, including the dead zeroed frame
// slot (a volatile local, per dead-zeroed-local-is-volatile), the dirty-flag
// guard, the out-parameter store and the 16-bit refcount increment.
// Residue: retail holds the fetched pointer in ecx and the out parameter in
// eax; MSVC swaps them. Tried both declaration orders for the two locals and
// the fully inlined form (51 bytes, worse). Systematic scratch-register flip.
class BfmeRefBI
{
public:
	unsigned char m_bfmeHeadBI[4];
	unsigned short m_bfmeCountBI;
};

class BfmeOwnBI
{
public:
	void bfmeFetchBI(BfmeRefBI **out);
	void bfmeSyncBI(void);

	unsigned char m_bfmeHeadBI[0x18];
	BfmeRefBI *m_bfmeRefBI;
	char m_bfmeDirtyBI;
};

void BfmeOwnBI::bfmeFetchBI(BfmeRefBI **out)
{
	volatile int guard = 0;

	if (m_bfmeDirtyBI)
		bfmeSyncBI();

	BfmeRefBI *ref = m_bfmeRefBI;

	*out = ref;

	if (ref)
		++ref->m_bfmeCountBI;
}
