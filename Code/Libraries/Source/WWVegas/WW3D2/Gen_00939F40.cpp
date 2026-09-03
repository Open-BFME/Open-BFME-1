// cl: /DNDEBUG /MD /EHsc
// Constructor of the 0x288-byte owner that prefixes Rva00906340 with three
// zeroed pointers. Unwind constructs eight 4-byte cells at +0x14 via the
// same ILT ctor/dtor as Rva00906340 (0x004110D6 / 0x00430652).

class Gen_00939F40_Cell
{
public:
	Gen_00939F40_Cell(void);
	~Gen_00939F40_Cell(void);

	void *m_value;
};

class Gen_00939F40_Base
{
public:
	Gen_00939F40_Base(void);
	~Gen_00939F40_Base(void);

	void *m_p0;
	void *m_p1;
	void *m_p2;
};

inline Gen_00939F40_Base::Gen_00939F40_Base(void)
	: m_p0(0),
	  m_p1(0),
	  m_p2(0)
{
}

class Gen_00939F40 : public Gen_00939F40_Base
{
public:
	Gen_00939F40(void);

	int m_tag;
	int m_zero;
	Gen_00939F40_Cell m_cells[8];
	unsigned char m_pad[0x238];
	void *m_260;
	void *m_264;
	void *m_268;
};

Gen_00939F40::Gen_00939F40(void)
	: m_tag(0x0010441B),
	  m_zero(0)
{
	m_268 = 0;
	m_260 = 0;
	m_264 = 0;
}
