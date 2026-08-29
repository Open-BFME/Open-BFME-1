// Open-BFME5 conversions.

struct BfmeNodeIC;

class BfmeThingIC
{
public:
	void bfmeDoIC(void *v, BfmeNodeIC *n);
	void *m_bfmeVal;
};

struct BfmeNodeIC
{
	char m_bfmePad[0x28];
	BfmeNodeIC *m_bfmeNext;
};

void __stdcall bfmeGoIC(BfmeNodeIC *n, BfmeThingIC *t)
{
	while (n) {
		t->bfmeDoIC(t->m_bfmeVal, n);
		n = n->m_bfmeNext;
	}
}

struct BfmeNodeID
{
	int m_bfmePad;
	BfmeNodeID *m_bfmeNext;
};

class BfmeGlobID
{
public:
	virtual void bfmeSlotID0();
	virtual void bfmeSlotID1();
	virtual void bfmeSlotID2();
	virtual void bfmeSlotID3();
	virtual void *bfmeTailID();
	char m_bfmePad[4];
	BfmeNodeID *m_bfmeHead;
};

extern BfmeGlobID *g_bfmeGlobID;

class BfmeThingID
{
public:
	void *bfmeGoID();
	void bfmeDoID(BfmeNodeID *n, int f);
};

void *BfmeThingID::bfmeGoID()
{
	BfmeNodeID *n = g_bfmeGlobID->m_bfmeHead;
	while (n) {
		bfmeDoID(n, 0);
		n = n->m_bfmeNext;
	}
	return g_bfmeGlobID->bfmeTailID();
}

