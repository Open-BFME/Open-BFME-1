// ?bfmeMarkAB@BfmeOwnAB@@QAEXPAXABVBfmeRoomAB@@@Z (identity unknown)
// partial score=0.86 date=2026-09-06
// 65/76 at exact size and exact structure (a four-term && chain sharing one
// exit, then a byte store through the result). Two residues:
//   - esi/edi are swapped: retail puts `this` in edi and the first parameter
//     in esi, MSVC the other way round. Tried hoisting the parameter into a
//     local declared before everything, and splitting the first guard into an
//     early return so the parameter local is declared later. No effect.
//   - +0x28: retail emits the esp marker BEFORE `mov ecx,esp`, MSVC after --
//     the same swap that blocks 0x0034C710.
// The room copy ctor is the string_base alias pinned at 0x00887B60.
class BfmeRoomAB
{
public:
	BfmeRoomAB(const BfmeRoomAB &other);
	~BfmeRoomAB();

	int m_bfmeHandleAB;
};

class ClientRoot4120
{
public:
	virtual void bfmeCrSlot00AB(void);
	virtual void bfmeCrSlot01AB(void);
	virtual void bfmeCrSlot02AB(void);
	virtual void bfmeCrSlot03AB(void);
	virtual void bfmeCrSlot04AB(void);
	virtual void bfmeCrSlot05AB(void);
	virtual void bfmeCrSlot06AB(void);
	virtual void bfmeCrSlot07AB(void);
	virtual void bfmeCrSlot08AB(void);
	virtual void bfmeCrSlot09AB(void);
	virtual void bfmeCrSlot10AB(void);
	virtual int bfmeCheckAB(void *first);
};

extern ClientRoot4120 *TheGameClient;

class BfmeNodeAB
{
public:
	unsigned char m_bfmeHeadAB[0x95];
	char m_bfmeMarkAB;
};

class BfmeOwnAB
{
public:
	void bfmeMarkAB(void *first, const BfmeRoomAB &room);
	BfmeNodeAB *bfmeFindAB(void *first, BfmeRoomAB room);

	unsigned char m_bfmeHeadAB[0x28];
	char m_bfmeFlagAB;
};

void BfmeOwnAB::bfmeMarkAB(void *first, const BfmeRoomAB &room)
{
	ClientRoot4120 *client = TheGameClient;

	if (client == 0)
		return;

	void *target = first;
	BfmeNodeAB *node;

	if (client->bfmeCheckAB(target) && m_bfmeFlagAB
		&& (node = bfmeFindAB(target, room)) != 0)
		node->m_bfmeMarkAB = 1;
}
