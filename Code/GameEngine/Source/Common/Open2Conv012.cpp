// Four bodies from the 0x004xxxxx run.  Identity is not recovered; names are
// address-derived and the padding virtuals exist only to place the slots each
// body calls.

// ---------------------------------------------------------------------------
// 0x00413770 and 0x004137E0 -- walk a null-terminated array of owners and ask
// each one's target whether it accepts three arguments.
//
// The three arguments are hoisted into callee-saved registers BEFORE the loop
// and pushed unchanged on every turn, which is what a loop-invariant argument
// list looks like; the array is walked by advancing the cursor and re-reading,
// not by indexing.  The two bodies differ only in which slot they ask, 0x90
// against 0x94.

class Open2413770Target
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
	virtual char slot90( void *first, void *second, void *third );
	virtual char slot94( void *first, void *second, void *third );
};

class Open2413770Owner
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
	virtual Open2413770Target *slot9C();
};

class Rva00413770
{
public:
	char anyAccepts( void *first, void *second, void *third );

	char m_pad[ 0x150 ];
	Open2413770Owner **m_owners;
};

// @?anyAccepts@Rva00413770@@QAEDPAX00@Z 0x00413770
char Rva00413770::anyAccepts( void *first, void *second, void *third )
{
	Open2413770Owner **cursor = m_owners;
	Open2413770Owner *owner = *cursor;

	while( owner != 0 )
	{
		Open2413770Target *target = owner->slot9C();
		if( target != 0 && target->slot90( first, second, third ) )
			return 1;

		++cursor;
		owner = *cursor;
	}
	return 0;
}

class Rva004137E0
{
public:
	char anyAccepts( void *first, void *second, void *third );

	char m_pad[ 0x150 ];
	Open2413770Owner **m_owners;
};

// @?anyAccepts@Rva004137E0@@QAEDPAX00@Z 0x004137E0
char Rva004137E0::anyAccepts( void *first, void *second, void *third )
{
	Open2413770Owner **cursor = m_owners;
	Open2413770Owner *owner = *cursor;

	while( owner != 0 )
	{
		Open2413770Target *target = owner->slot9C();
		if( target != 0 && target->slot94( first, second, third ) )
			return 1;

		++cursor;
		owner = *cursor;
	}
	return 0;
}

