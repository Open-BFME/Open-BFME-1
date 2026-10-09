// Open-BFME5 conversions.

class BfmeE1280
{
public:
	void bfmeClose1280();
	BfmeE1280 *m_bfme00;
};

struct BfmeR1280
{
	char m_bfmePad00[0x10];
	BfmeE1280 *m_bfme10;
};


class BfmeA1280
{
public:
	void bfmeRemove1280(int i);
	void bfmeNotify1280(int i);
	char m_bfmePad00[0x0c];
	BfmeR1280 *m_bfme0c;
};

// Matched callee rows (callees.py, via ILT): Rva00354A00Node, Rva00359330StringRecordTable::release, operator delete.
class Rva00354A00Node
{
public:
	~Rva00354A00Node();
};

class Rva00359330StringRecordTable
{
public:
	void release(int i);
};

void BfmeA1280::bfmeRemove1280(int i)
{
	BfmeE1280 *e;
	BfmeR1280 *r;

	r = &m_bfme0c[i];
	e = r->m_bfme10;
	r->m_bfme10 = e->m_bfme00;
	((Rva00354A00Node *)e)->~Rva00354A00Node();
	operator delete(e);
	((Rva00359330StringRecordTable *)this)->release(i);
}
