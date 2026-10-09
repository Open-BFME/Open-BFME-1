// Open-BFME5 conversions.

// Callees (tools/callees.py 0x803030 70): 0x007EA550 Rva007EAServiceList::add,
// 0x007EA590 Rva007EAServiceList::remove.
class Rva00803080;

class Rva007EAServiceList
{
public:
	void add(Rva00803080 *p);
	void remove(Rva00803080 *p);
};

struct BfmeOwnVMO
{
	char m_bfmePad00[0xc];
	Rva007EAServiceList *m_bfme0c;
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
		m_bfme04->m_bfme0c->add((Rva00803080 *)this);
		m_bfme10 = n;
		return;
	}
	if (n == 0 && m_bfme10 > 0)
		m_bfme04->m_bfme0c->remove((Rva00803080 *)this);
	m_bfme10 = n;
}
