// cl: /DNDEBUG /MD /EHsc
// ?s5parse005A0720@@YAXPAVINI@@PAUGen_00489270@@@Z at retail 0x005A0720.
//
// Retail allocates a 0x38-byte virtual definition record, fills its fields,
// parses its INI table, and registers it with the shared definition sink.
// The virtual base layout reproduces the vtable store at object offset zero.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

struct Gen_00489270
{
	void m(int value);
};

class Rva00489210
{
public:
	virtual void slot();
	Rva00489210();
	int m_04;
	char m_08;
	char m_09;
	char m_0A;
	int m_0C;
};

struct S5ZeroPair
{
	int m_a;
	int m_b;
	S5ZeroPair() : m_a(0), m_b(0) {}
};

struct S5Built005A0720 : public Rva00489210
{
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	S5ZeroPair m_2C;
	int m_34;

	S5Built005A0720()
	{
		m_10 = 0;
		m_14 = 30;
		m_04 = m_14;
		m_0C = 0;
		m_28 = -1;
		m_09 = 1;
		m_34 = 0;
	}
};

extern const FieldParse s5Table005A0720;

void s5parse005A0720(INI *ini, Gen_00489270 *sink)
{
	S5Built005A0720 *record = new S5Built005A0720;
	ini->initFromINI(record, &s5Table005A0720);
	record->m_04 = record->m_14;
	sink->m((int)record);
}
