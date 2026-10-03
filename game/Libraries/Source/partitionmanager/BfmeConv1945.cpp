// Retail 0x009F2B20 is the chain-record constructor BfmeChainRecord::BfmeChainRecord
// (matched in game/GameEngine/Source/Common/Bfme/BfmeChainRecord.cpp) and
// 0x009F4D80 is Gen009F5040::linkNode_009F4D80 (matched in
// game/Libraries/Source/partitionmanager/Gen009F5040Handle.cpp), so both calls
// below are spelled with those names to link.

struct Gen009F5040Node;

class BfmeChainRecord
{
public:
	BfmeChainRecord(void *first, void *second, BfmeChainRecord **ownerLink);

	unsigned char m_bfmeBody[0x30];
};

class BfmeThingEQR
{
public:
	virtual void bfmeSlot0EQR();
	virtual void bfmeSlot1EQR();
	virtual void bfmeSlot2EQR();
	virtual void bfmeSlot3EQR();
	virtual void bfmeSlot4EQR();
	virtual void bfmeSlot5EQR(BfmeChainRecord *rec);
	virtual void *bfmeSlot6EQR();
};

class Gen009F5040
{
public:
	void linkNode_009F4D80(Gen009F5040Node *node);
};

class BfmeHostEQR
{
public:
	void bfmeAddEQR(BfmeThingEQR *thing);

	unsigned char m_bfmeHeadEQR[0xe4];
	BfmeChainRecord *m_bfmeListEQR;
};

void BfmeHostEQR::bfmeAddEQR(BfmeThingEQR *thing)
{
	if (thing == 0)
		return;

	if (thing->bfmeSlot6EQR() != 0)
		return;

	BfmeChainRecord *rec = new BfmeChainRecord(this, thing, &m_bfmeListEQR);

	thing->bfmeSlot5EQR(rec);
	((Gen009F5040 *)this)->linkNode_009F4D80(
		reinterpret_cast<Gen009F5040Node *>(rec));
}
