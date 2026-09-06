// ?bfmeAtAP@BfmeOwnAP@@QAEPAXH@Z (identity unknown)
// partial score=0.9 date=2026-09-06
// 40/44 at exact size and exact structure. Two scratch-register flips, both
// in the same direction (retail prefers edx where MSVC prefers ecx):
//   +0x0b  retail `lea edx,[ecx+0x2b8]` / `push edx`, MSVC `add ecx,0x2b8` /
//          `push ecx` (ecx is dead either way);
//   +0x22  retail `mov ecx,[esi+0x28]` for the array base, MSVC `mov edx`.
// Tried a named local for the table pointer (17 diffs, worse), a named local
// for the item array, and a named int* for the argument. This is the
// systematic ecx/edx flip.
class BfmeTableAP
{
public:
	unsigned char m_bfmeHeadAP[0x2b8];
	int m_bfmeSlotAP;
};

int __stdcall bfmeLookupAP(int *table, int key);

class BfmeOwnAP
{
public:
	void *bfmeAtAP(int key);

	unsigned char m_bfmeHeadAP[4];
	BfmeTableAP *m_bfmeTableAP;
	unsigned char m_bfmeMidAP[0x20];
	void **m_bfmeItemsAP;
};

void *BfmeOwnAP::bfmeAtAP(int key)
{
	int index = bfmeLookupAP(&m_bfmeTableAP->m_bfmeSlotAP, key);

	if (index == -1)
		return 0;

	return m_bfmeItemsAP[index];
}
