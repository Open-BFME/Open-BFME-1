// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of the 0x0059AB00 parser body.

struct FieldParse;

class INI
{
public:
	void initFromINI( void *object, const FieldParse *table );
};

class BfmeAttackNuggetBase
{
public:
	BfmeAttackNuggetBase();
	virtual void handle();
};

class Gen_00489270
{
public:
	void m( int nugget );
};

extern const FieldParse Rva0059AB00FieldParse;

class Rva0059AB00 : public BfmeAttackNuggetBase
{
public:
	static void parse( INI *ini, Gen_00489270 *list );

	__forceinline Rva0059AB00()
	{
		m_24 = 0;
		m_04 = 0x11;
		m_0C = 0;
		m_20 = -1;
		m_09 = 1;
	}

private:
	int m_04;
	char m_08;
	char m_09;
	int m_0C;
	char m_gap[ 0x10 ];
	int m_20;
	int m_24;
};

// ?parse@Rva0059AB00@@SAXPAVINI@@PAVRva0059AB00List@@@Z
void Rva0059AB00::parse( INI *ini, Gen_00489270 *list )
{
	Rva0059AB00 *nugget = new Rva0059AB00;
	ini->initFromINI( nugget, &Rva0059AB00FieldParse );
	list->m( (int)nugget );
}
