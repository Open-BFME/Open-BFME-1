// Open-BFME5 conversions.

class BfmeSink1018
{
public:
	void bfmeReset1018(int n);
	void bfmeSet1018(int v, int f);
};

struct BfmeK1018
{
	char m_bfmePad[0x24];
	int m_bfmeB;
	char m_bfmePad2[4];
	int m_bfmeA;
	char m_bfmePad3[8];
	char m_bfmeFlag;
};

class BfmeI1018
{
public:
	void bfmeGo1018I(void);

	char m_bfmePad[4];
	BfmeK1018 *m_bfmeK;
	BfmeSink1018 *m_bfmeSink;
};

class Gen001C9A10
{
public:
	void handle(int n);
};

class Object
{
public:
	void setWeaponLock(int a, int b);
};

void BfmeI1018::bfmeGo1018I(void)
{
	BfmeK1018 *k = m_bfmeK;

	((Gen001C9A10 *)m_bfmeSink)->handle(0);

	if (k->m_bfmeFlag != 0)
		((Object *)m_bfmeSink)->setWeaponLock(k->m_bfmeA, 1);
	else
		((Object *)m_bfmeSink)->setWeaponLock(k->m_bfmeB, 1);
}
