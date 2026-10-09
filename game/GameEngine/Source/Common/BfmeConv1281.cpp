// Open-BFME5 conversions.

class BfmeE1281
{
public:
	void bfmeClose1281();
	BfmeE1281 *m_bfme00;
};

struct BfmeR1281
{
	char m_bfmePad00[0x10];
	BfmeE1281 *m_bfme10;
};


class BfmeA1281
{
public:
	void bfmeRemove1281(int i);
	void bfmeNotify1281(int i);
	char m_bfmePad00[0x0c];
	BfmeR1281 *m_bfme0c;
};

// Matched callee rows (callees.py, via ILT): Rva00354A60, Rva00359530StringRecordTable::release, operator delete.
class Rva00354A60
{
public:
	void invoke();
};

class Rva00359530StringRecordTable
{
public:
	void release(int i);
};

void BfmeA1281::bfmeRemove1281(int i)
{
	BfmeE1281 *e;
	BfmeR1281 *r;

	r = &m_bfme0c[i];
	e = r->m_bfme10;
	r->m_bfme10 = e->m_bfme00;
	((Rva00354A60 *)e)->invoke();
	operator delete(e);
	((Rva00359530StringRecordTable *)this)->release(i);
}
