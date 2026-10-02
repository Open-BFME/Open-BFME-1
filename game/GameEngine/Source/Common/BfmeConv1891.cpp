// Retail ILT 0x000044C1 (targets/game/reverse/functions.csv, gen-thunk row
// ?j_000044c1@@YAXXZ) is a 5-byte `jmp 0x6b2080`, i.e. RVA 0x002B2080, which
// the ledger matches as
// ?handle@Gen002B2080@@QAEXPAVFlagPairTarget@@@Z
// (game/GameEngine/Source/GameLogic/AI/Gen002B2080Handle.cpp). Only the one
// member is spelled here, so no layout of that class is imported; the caller
// passes its own `this` and the same pointer the ILT took, exactly as retail
// does (ecx + one pushed argument, `ret 4` on the callee side).
class FlagPairTarget;

class Gen002B2080
{
public:
	void handle(FlagPairTarget *target);
};

struct BfmeMarkAC
{
	unsigned char m_bfmeOneAC;
	unsigned char m_bfmeTwoAC;
};

class BfmeItemAC
{
public:
	virtual void bfmeV0AC();
	virtual void bfmeV1AC();
	virtual void bfmeV2AC();
	virtual void bfmeV3AC();
	virtual char bfmeDoneAC();
	virtual void bfmeV5AC();
	virtual void bfmeV6AC();
	virtual void bfmeV7AC();
	virtual void bfmeV8AC();
	virtual void bfmeV9AC();
	virtual void bfmeMarkAC(BfmeMarkAC *mark);
};

// Retail callee Rva0010C3C0 (0x0010C3C0, MidVirtualSlot90Forwarders.cpp).
class MidVirtualSlot90Receiver;
void __cdecl Rva0010C3C0(MidVirtualSlot90Receiver *item, void *slot);

class BfmeOwnerAC
{
public:
	void bfmeDoAC(BfmeItemAC *item);

	unsigned char m_bfmeHeadAC[0xcc];
	void *m_bfmeSlotsAC[10];
};

void BfmeOwnerAC::bfmeDoAC(BfmeItemAC *item)
{
	BfmeMarkAC mark;
	unsigned char set = 1;

	mark.m_bfmeOneAC = set;
	mark.m_bfmeTwoAC = set;

	item->bfmeMarkAC(&mark);

	((Gen002B2080 *)this)->handle((FlagPairTarget *)item);

	if (item->bfmeDoneAC() != 0)
		return;

	for (int i = 0; i < 10; i++)
		Rva0010C3C0((MidVirtualSlot90Receiver *)item, &m_bfmeSlotsAC[i]);
}
