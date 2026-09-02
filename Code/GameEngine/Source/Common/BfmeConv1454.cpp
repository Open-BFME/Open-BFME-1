// Open-BFME5 conversions.

class BfmeSvcVMO;

class BfmeListVMO
{
public:
	void bfmeAddVMO(BfmeSvcVMO *p);
	void bfmeRemoveVMO(BfmeSvcVMO *p);
};

struct BfmeOwnVMO
{
	char m_bfmePad00[0xc];
	BfmeListVMO *m_bfme0c;
};

class BfmeSvcVMO
{
public:
	void bfmeSetVMO(int n);
	int m_bfme00;
	BfmeOwnVMO *m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
};

void BfmeSvcVMO::bfmeSetVMO(int n)
{
	if (n > 0 && m_bfme10 == 0)
	{
		m_bfme04->m_bfme0c->bfmeAddVMO(this);
		m_bfme10 = n;
		return;
	}
	if (n == 0 && m_bfme10 > 0)
		m_bfme04->m_bfme0c->bfmeRemoveVMO(this);
	m_bfme10 = n;
}
