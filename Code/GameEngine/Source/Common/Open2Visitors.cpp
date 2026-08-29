// Two more "hand every member address to a visitor" bodies, the same shape as
// the one landed at 0x0045B700: this in ecx, the visitor as the single stack
// argument, and one `lea / push / mov ecx,visitor / call [vptr+SLOT]` per
// field with the visitor's vptr re-read before every call.
//
// The field OFFSETS and the slot each one goes to are what the bytes fix; the
// member types are not observable, since only an address is ever passed.

class Open2Visitor
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
	virtual void slot50( void *field );
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68( void *field );
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74( void *field );
	virtual void slot78( void *field );
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C( void *field );
};


// -------------------------------------------------------------------------
// 0x003BBAA0 -- 49 bytes, 3 fields
class Rva3BBAA0
{
public:
	void visit( Open2Visitor *visitor );

	char m_pad0[ 0x4 ];
	int m_at04;
	int m_at08;
	int m_at0c;
};

// @?visit@Rva3BBAA0@@QAEXPAVOpen2Visitor@@@Z 0x003BBAA0
void Rva3BBAA0::visit( Open2Visitor *visitor )
{
	visitor->slot74( &m_at04 );
	visitor->slot8C( &m_at08 );
	visitor->slot74( &m_at0c );
}

// -------------------------------------------------------------------------
// 0x003BC770 -- 68 bytes, 5 fields
class Rva3BC770
{
public:
	void visit( Open2Visitor *visitor );

	int m_at00;
	char m_pad0[ 0x4 ];
	int m_at08;
	int m_at0c;
	int m_at10;
	int m_at14;
};

// @?visit@Rva3BC770@@QAEXPAVOpen2Visitor@@@Z 0x003BC770
void Rva3BC770::visit( Open2Visitor *visitor )
{
	visitor->slot50( &m_at00 );
	visitor->slot78( &m_at08 );
	visitor->slot68( &m_at0c );
	visitor->slot68( &m_at10 );
	visitor->slot8C( &m_at14 );
}
