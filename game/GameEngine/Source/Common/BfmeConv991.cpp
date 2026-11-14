// Open-BFME5 conversions.

void bfmeStepA991(void);
void bfmeStepB991(void);
void bfmeFinish991(void);

class BfmeA991
{
public:
	virtual void bfmeVA0991();
	virtual void bfmeVA1991();
	virtual void bfmeVA2991();
	virtual void bfmeVA3991();
	virtual void bfmeVA4991();
	virtual void bfmeStop991A();

	void bfmeGo991A();

	char m_bfmePad[0x1c0];
	char m_bfmeOn;
};

void BfmeA991::bfmeGo991A()
{
	if (m_bfmeOn) {
		bfmeStop991A();
		m_bfmeOn = 0;
	}

	bfmeStepA991();
	bfmeStepB991();
	bfmeFinish991();
}

class BfmeB991
{
public:
	virtual void bfmeVB0991();
	virtual void bfmeVB1991();
	virtual void bfmeTick991();

	void bfmeSet991(int a);

	char m_bfmePad[0x1c];
	int m_bfmeSlot;
};

// Retail 0x012F9D88: use the existing data owner; retain the local pointee view.
extern class SmudgeManager *TheSmudgeManager;
extern int g_bfmeVal991;

void bfmeGo991B(int a)
{
	if (!reinterpret_cast<BfmeB991 *>(TheSmudgeManager))
		return;

	reinterpret_cast<BfmeB991 *>(TheSmudgeManager)->bfmeSet991(a);
	reinterpret_cast<BfmeB991 *>(TheSmudgeManager)->bfmeTick991();
	reinterpret_cast<BfmeB991 *>(TheSmudgeManager)->m_bfmeSlot = g_bfmeVal991;
}

class BfmeDev991
{
public:
	virtual void bfmeVD0991();
	virtual void bfmeVD1991();
	virtual void bfmeVD2991();
	virtual void bfmeVD3991();
	virtual void bfmeVD4991();
	virtual void bfmeReset991(int a, int b);
};

class BfmeC991
{
public:
	char bfmeGo991C(int a, int b);
	char bfmeSend991(int a, int b);

	char m_bfmePad[4];
	BfmeDev991 *m_bfmeDev;
	int m_bfmeKind;
};

char BfmeC991::bfmeGo991C(int a, int b)
{
	if (m_bfmeKind == 6) {
		m_bfmeDev->bfmeReset991(0, 0);
		return bfmeSend991(a, b);
	}

	return 0;
}
