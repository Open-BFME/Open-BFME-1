// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the guarded table walk at retail 0x00872680, 72 bytes.  Builds a
// four-word argument block on the stack and hands it to TableMap along with the
// per-entry callback that sits just below this body.

extern "C" void __cdecl TableMap(void *table, void *each, void *param);

class BfmeRoomXM;

extern "C" void __cdecl bfmeVisitXM(void *entry, void *param);

class BfmeRoomXM
{
public:
	int m_bfmeFirst;					// +0x000
	char m_bfmePad004[0x808];				// +0x004
	void *m_bfmeTable;					// +0x80C
};

struct BfmeWalkXM
{
	BfmeRoomXM *m_bfmeRoom;					// +0x00
	int m_bfmeA;						// +0x04
	int m_bfmeB;						// +0x08
	int m_bfmeC;						// +0x0C
};

// ?bfmeWalkXM@@YAXPAVBfmeRoomXM@@HH@Z
void __cdecl bfmeWalkXM(BfmeRoomXM *room, int a, int b)
{
	if (room == 0)
		return;

	if (room->m_bfmeFirst == 0)
		return;

	BfmeWalkXM walk;

	walk.m_bfmeA = a;
	walk.m_bfmeB = b;
	walk.m_bfmeC = 0;
	walk.m_bfmeRoom = room;

	TableMap(room->m_bfmeTable, (void *)&bfmeVisitXM, &walk);
}
