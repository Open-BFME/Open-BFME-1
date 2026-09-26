// cl: /O2
// 0x007FA990: thiscall constructor. A secondary-base vptr lands at +4,
// then the most-derived vptrs at +0 and +4, then four 16-byte cells at +8
// through a walking pointer, then the argument and trailing zeros.

class Rva007FA990Base0
{
public:
	virtual void v0();
};

class Rva007FA990Base4
{
public:
	virtual void v4();
};

struct Rva007FA990Cell
{
	void *a;
	void *b;
	void *c;
	void *d;

	Rva007FA990Cell() throw()
	{
		a = 0;
		b = 0;
		c = 0;
		d = 0;
	}
};

class Rva007FA990 : public Rva007FA990Base0, public Rva007FA990Base4
{
public:
	Rva007FA990(void *arg) throw();
	virtual void v0();
	virtual void v4();

private:
	Rva007FA990Cell m_cells[4];
	void *m_48;
	void *m_4C;
	unsigned char m_50;
	char m_pad51[0x3F];
	unsigned char m_90;
	char m_pad91[0x3F];
	void *m_D0;
	void *m_D4;
};

Rva007FA990::Rva007FA990(void *arg) throw()
{
	m_4C = arg;
	m_48 = 0;
	m_50 = 0;
	m_90 = 0;
	m_D4 = 0;
	m_D0 = 0;
}
