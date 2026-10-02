// Open-BFME5 conversions.

class BfmeE1222
{
public:
	virtual void bfmeV1222A();
	virtual void bfmeV1222B();
};

// 0x0089C880 is matched in functions.csv as Gen0089C880::handle(); the only
// declaration of that class lives in a TU, so it is redeclared here.
class Gen0089C880
{
public:
	void handle(void);
};

class BfmeSub1222
{
public:
	int m_bfme00;
};

class BfmeA1222
{
public:
	void bfmeRelease1222();
	char m_bfmePad00[8];
	BfmeSub1222 m_bfme08;
	char m_bfmePad0c[0x20 - 0x0c];
	BfmeE1222 *m_bfme20;
	int m_bfme24;
	BfmeE1222 *m_bfme28;
	BfmeE1222 *m_bfme2c;
};

void BfmeA1222::bfmeRelease1222()
{
	if (m_bfme20)
		m_bfme20->bfmeV1222B();
	m_bfme20 = 0;
	m_bfme28->bfmeV1222B();
	m_bfme28 = 0;
	m_bfme2c->bfmeV1222B();
	m_bfme2c = 0;
	((Gen0089C880 *)&m_bfme08)->handle();
}
