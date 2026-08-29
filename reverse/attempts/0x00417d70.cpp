// ?d_00417d70@@YAXXZ
// partial score=0.72 date=2026-08-29
// A clear-then-zero from the 0x0041xxxx run.  Identity is not recovered.
//
// The walk is the same shape as the two owner-list scans landed at 0x00413770:
// a null-terminated array of owners, each asked for its target, advanced by
// cursor rather than by index.
//
// The two ten-dword runs afterwards are each written through a MATERIALISED
// base -- `lea ecx,[edi+0x2a0]` and `add edi,0x278` -- which needs no coaxing
// here: the offsets are past 0x80, so a base register plus a byte displacement
// is shorter than the full displacement and MSVC picks it on its own.  (Two
// bodies banked earlier fail on exactly the opposite case, where retail
// materialises a base for SMALL offsets and this toolchain will not.)

class Open2417D70Target
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
	virtual void slot48( void *what );
};

class Open2417D70Owner
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
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual Open2417D70Target *slot9C();
};

class Rva00417D70
{
public:
	void clear( void *what );

	char m_pad[ 0x150 ];
	Open2417D70Owner **m_owners;
	char m_pad2[ 0x278 - 0x154 ];
	int m_firstRun[ 10 ];
	int m_secondRun[ 10 ];
};

// @?clear@Rva00417D70@@QAEXPAX@Z 0x00417D70
void Rva00417D70::clear( void *what )
{
	Open2417D70Owner **cursor = m_owners;
	Open2417D70Owner *owner = *cursor;

	while( owner != 0 )
	{
		Open2417D70Target *target = owner->slot9C();
		if( target != 0 )
			target->slot48( what );

		++cursor;
		owner = *cursor;
	}

	int *second = m_secondRun;
	second[ 0 ] = 0;
	second[ 1 ] = 0;
	second[ 2 ] = 0;
	second[ 3 ] = 0;
	second[ 4 ] = 0;
	second[ 5 ] = 0;
	second[ 6 ] = 0;
	second[ 7 ] = 0;
	second[ 8 ] = 0;
	second[ 9 ] = 0;

	int *first = m_firstRun;
	first[ 0 ] = 0;
	first[ 1 ] = 0;
	first[ 2 ] = 0;
	first[ 3 ] = 0;
	first[ 4 ] = 0;
	first[ 5 ] = 0;
	first[ 6 ] = 0;
	first[ 7 ] = 0;
	first[ 8 ] = 0;
	first[ 9 ] = 0;
}
