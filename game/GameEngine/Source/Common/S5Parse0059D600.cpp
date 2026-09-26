// Parse the BfmeB1140 definition, then register the populated record.
// The vtable at 0x0110C814 matches BfmeB1140 and the sibling constructor at
// 0x0059D570.  Volatile fields preserve the retail store order around m_14.

struct FieldParse;

class INI
{
public:
	void initFromINI( void *what, const FieldParse *table );
};

struct Gen_00489270
{
	void m( int value );
};

class Rva00489210
{
public:
	Rva00489210();
	volatile int *volatile m_00;
	int m_04;
	char m_08, m_09, m_0A;
	int m_0C;
};

extern "C" int g_bfmeV1140B;
extern const FieldParse s5Table0059D600;

struct S5Built0059D600 : public Rva00489210
{
	volatile int m_10;
	volatile int m_14;
	volatile int m_18;
	volatile int m_1C;
	volatile int m_20;
	volatile int m_24;
	int m_28;
	int m_2C;

	S5Built0059D600()
	{
		m_14 = 30;
		m_00 = &g_bfmeV1140B;
		m_10 = 0;
		m_18 = 0;
		m_1C = 0;
		m_20 = 0;
		m_24 = 0;
		m_28 = 0;
		m_2C = -1;
		m_04 = m_14;
		m_0C = 0;
		m_09 = 1;
	}
};

void s5parse0059D600( INI *ini, Gen_00489270 *sink )
{
	S5Built0059D600 *record = new S5Built0059D600;
	ini->initFromINI( record, &s5Table0059D600 );
	record->m_04 = record->m_14;
	sink->m( (int)record );
}
