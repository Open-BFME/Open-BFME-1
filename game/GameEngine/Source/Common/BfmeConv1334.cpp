// Open-BFME5 conversions.

// Retail frees these arrays through operator delete[] (??_V@YAXPAX@Z,
// 0x00881EF0). Without the declaration cl falls back to scalar
// operator delete for the block, which is a different body at 0x00881EB0.
void __cdecl operator delete[](void *block);
class BfmeElemUJA
{
public:
	~BfmeElemUJA();
	char m_bfmePad[0x24];
};

class BfmeThingUJA
{
public:
	void bfmeClearUJA();
	void *m_bfmeVft;
	BfmeElemUJA *m_bfmeArray;
	int m_bfmeCount;
	char m_bfmePad;
	char m_bfmeOwned;
};

void BfmeThingUJA::bfmeClearUJA()
{
	if (m_bfmeArray && m_bfmeOwned) {
		delete [] m_bfmeArray;
		m_bfmeArray = 0;
	}
	m_bfmeOwned = 0;
	m_bfmeCount = 0;
}

struct BfmeStateUJC
{
	char m_bfmePad[0x108];
	int m_bfmeBusy;
};

struct BfmeConnUJC
{
	BfmeStateUJC *m_bfmeState;
};

void bfmeDisconnectUJC(BfmeConnUJC *c, int f);
void bfmeResetUJC(BfmeConnUJC *c);

void bfmeGoUJC(BfmeConnUJC *c)
{
	if (c && c->m_bfmeState && !c->m_bfmeState->m_bfmeBusy) {
		bfmeDisconnectUJC(c, 1);
		bfmeResetUJC(c);
	}
}
