// Open-BFME5 conversions.

class BfmeStrVMX
{
public:
	void bfmeSetVMX(const BfmeStrVMX &o);
	char *m_bfme00;
};

class BfmeOwnedVMX
{
public:
	virtual void bfmeReleaseVMX(int f);
};

class BfmeRecVMX
{
public:
	void bfmeAssignVMX(BfmeRecVMX *o);
	int m_bfme00;
	BfmeStrVMX m_bfme04;
	BfmeStrVMX m_bfme08;
	BfmeStrVMX m_bfme0c;
	int m_bfme10;
	char m_bfme14;
	char m_bfme15;
	char m_bfme16;
	char m_bfme17;
	char m_bfme18;
	char m_bfme19;
	char m_bfme1a;
	char m_bfmePad1b;
	BfmeOwnedVMX *m_bfme1c;
	BfmeOwnedVMX *m_bfme20;
	BfmeOwnedVMX *m_bfme24;
};

void BfmeRecVMX::bfmeAssignVMX(BfmeRecVMX *o)
{
	m_bfme04.bfmeSetVMX(o->m_bfme04);
	m_bfme08.bfmeSetVMX(o->m_bfme08);
	m_bfme0c.bfmeSetVMX(o->m_bfme0c);
	m_bfme14 = o->m_bfme14;
	m_bfme15 = o->m_bfme15;
	m_bfme17 = o->m_bfme17;
	m_bfme10 = o->m_bfme10;
	m_bfme16 = o->m_bfme16;
	m_bfme18 = o->m_bfme18;
	m_bfme19 = o->m_bfme19;
	m_bfme1a = o->m_bfme1a;
	if (m_bfme1c != 0)
		m_bfme1c->bfmeReleaseVMX(1);
	m_bfme1c = o->m_bfme1c;
	o->m_bfme1c = 0;
	if (m_bfme20 != 0)
		m_bfme20->bfmeReleaseVMX(1);
	m_bfme20 = o->m_bfme20;
	o->m_bfme20 = 0;
	if (m_bfme24 != 0)
		m_bfme24->bfmeReleaseVMX(1);
	m_bfme24 = o->m_bfme24;
	o->m_bfme24 = 0;
}
