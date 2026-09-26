// Two bodies from the 0x004xxxxx run.  Identity is not recovered; names are
// address-derived and the padding virtuals exist only to place the slots each
// body calls.

// ---------------------------------------------------------------------------
// 0x0045B700 -- hand ten member addresses to a visitor, one slot per field
// kind.
//
// The visitor is re-read from its own vptr before every call, so it is a
// virtual dispatch each time rather than one hoisted table; and the last two
// fields are one byte apart (+0x2c and +0x2d), which is what the `add edi,0x2d`
// says about the second of them.

class Open245B700Visitor
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60( void *field );
	virtual void slot64();
	virtual void slot68( void *field );
	virtual void slot6C( void *field );
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C( void *field );
};

class Rva0045B700
{
public:
	void visit( Open245B700Visitor *visitor );

	char m_pad0[ 4 ];
	int m_first;
	int m_second;
	char m_pad1[ 8 ];
	int m_third;
	int m_fourth;
	int m_fifth;
	int m_sixth;
	int m_seventh;
	int m_eighth;
	unsigned char m_ninth;
	unsigned char m_tenth;
};

// @?visit@Rva0045B700@@QAEXPAVOpen245B700Visitor@@@Z 0x0045B700
void Rva0045B700::visit( Open245B700Visitor *visitor )
{
	visitor->slot68( &m_first );
	visitor->slot60( &m_second );
	visitor->slot6C( &m_third );
	visitor->slot6C( &m_fourth );
	visitor->slot6C( &m_fifth );
	visitor->slot6C( &m_sixth );
	visitor->slot6C( &m_seventh );
	visitor->slot6C( &m_eighth );
	visitor->slot8C( &m_ninth );
	visitor->slot8C( &m_tenth );
}

