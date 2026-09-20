// ?d_0018a470@@YAXXZ
// partial score=0.97 date=2026-09-20
class BfmeThingEBE;

class BfmeSubEBE
{
public:
	virtual void bfmeSlot00EBE();
	virtual void bfmeSlot01EBE();
	virtual void bfmeSlot02EBE();
	virtual void bfmeSlot03EBE();
	virtual void bfmeSlot04EBE();
	virtual void bfmeSlot05EBE();
	virtual void bfmeSlot06EBE();
	virtual void bfmeSlot07EBE();
	virtual void bfmeSlot08EBE();
	virtual void bfmeSlot09EBE();
	virtual void bfmeSlot10EBE();
	virtual void bfmeSlot11EBE();
	virtual void bfmeSlot12EBE();
	virtual void bfmeSlot13EBE();
	virtual void bfmeAttachEBE(BfmeThingEBE *thing);
};

class BfmeStateEBE
{
public:
	virtual void bfmeVSlot00EBE();
	virtual void bfmeVSlot01EBE();
	virtual void bfmeVSlot02EBE();
	virtual void bfmeVSlot03EBE();
	virtual int bfmeRunEBE();

	BfmeStateEBE(void *owner, int a, int b, int c, void *data);

	unsigned char m_bfmeHeadEBE[0x18];
	BfmeSubEBE *m_bfmeSubEBE;
	unsigned char m_bfmeTailEBE[0x34];
};

class BfmeOwnerEBE
{
public:
	unsigned char m_bfmeHeadEBE[0x50];
	int m_bfmeKeyEBE;
};

struct Rva00367E30Logic
{
	BfmeThingEBE *bfmeFindEBE(int key);

	unsigned char m_bfmeHeadEBE[0x3c];
	int m_bfmeFrameEBE;
};

class AI
{
public:
	unsigned char m_bfmeHeadEBE[0x14];
	AI *m_bfmeSubEBE;
	unsigned char m_bfmePadEBE[0x24];
	int m_bfmeDelayEBE;
};

extern Rva00367E30Logic *TheBfmeGameLogic;
extern AI *TheAI;

class BfmeHostEBE
{
public:
	int bfmeStartEBE();

	unsigned char m_bfmeHeadEBE[0x1c];
	BfmeOwnerEBE *m_bfmeOwnerEBE;
	unsigned char m_bfmePadAEBE[4];
	int m_bfmeDataEBE;
	int m_bfmeTimeEBE;
	unsigned char m_bfmePadBEBE[4];
	BfmeStateEBE *m_bfmeStateEBE;
};

int BfmeHostEBE::bfmeStartEBE()
{
	Rva00367E30Logic *logic = TheBfmeGameLogic;
	int key = m_bfmeOwnerEBE->m_bfmeKeyEBE;

	BfmeThingEBE *thing = logic->bfmeFindEBE(key);

	if (thing == 0)
		return -1;

	AI *ai = TheAI->m_bfmeSubEBE;
	int frame = logic->m_bfmeFrameEBE;
	int delay = ai->m_bfmeDelayEBE;

	m_bfmeTimeEBE = delay + frame;

	m_bfmeStateEBE = new BfmeStateEBE(m_bfmeOwnerEBE, 0, 1, 0, &m_bfmeDataEBE);

	m_bfmeStateEBE->m_bfmeSubEBE->bfmeAttachEBE(thing);

	return m_bfmeStateEBE->bfmeRunEBE() != 0 ? -1 : 0;
}

// The delay local reduces the register residue to five non-relocation bytes.
// Generated callers still do not prove a production owner or method name.
