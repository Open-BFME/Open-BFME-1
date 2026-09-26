// Open-BFME5 conversions.

class BfmeElemVVD
{
public:
	~BfmeElemVVD();
	char m_bfmePad00[0x20];
};

class BfmeBaseVVD
{
public:
	~BfmeBaseVVD() { }
	virtual void bfmeSlot0VVD();
};

class BfmeOwnVVD : public BfmeBaseVVD
{
public:
	~BfmeOwnVVD();
	char m_bfmePad04[0x44];
	BfmeElemVVD m_bfme48[8];
};

extern BfmeOwnVVD *g_bfmeSingletonVVD;

BfmeOwnVVD::~BfmeOwnVVD()
{
	if (g_bfmeSingletonVVD == this)
		g_bfmeSingletonVVD = 0;
}
