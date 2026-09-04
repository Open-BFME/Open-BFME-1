// Open-BFME5 conversions.

void __cdecl operator delete[](void *block);

class BfmeElemVVE
{
public:
	~BfmeElemVVE();
	int m_bfme00;
};

class BfmeBaseVVE
{
public:
	~BfmeBaseVVE() { }
	virtual void bfmeSlot0VVE();
};

class BfmeOwnVVE : public BfmeBaseVVE
{
public:
	~BfmeOwnVVE();
	char m_bfmePad04[4];
	BfmeElemVVE *m_bfme08;
};

BfmeOwnVVE::~BfmeOwnVVE()
{
	delete [] m_bfme08;
}
