// Four bodies from the 0x002xxxxx run.  Identity is not recovered; the padding
// virtuals exist only to place the slots these bodies call.

// ---------------------------------------------------------------------------
// 0x0020C140 -- a latch that clears itself, then two more reasons to say no.
//
//     mov al,[ecx+0x4c] / test al,al / je no / ... test eax,0x200000 / je rest
//     cmp byte [edx+0x14],1 / jne rest / mov [ecx+0x4c],0 / no: xor al,al
//     rest: test al,4 / jne no / test eax,0x80000 / jne no / mov al,1
//
// `test al,4` in the second half is NOT the latch byte read again: `mov
// eax,[ecx+8]` has already overwritten al, so it is the low byte of the flags
// dword, and the last two tests are both on flags -- one narrow, one wide.

class Open20C140Other
{
public:
	char m_pad[ 0x14 ];
	unsigned char m_kind;
};

class Open20C140Object
{
public:
	char m_pad[ 0x90 ];
	unsigned int m_flags;
};

class Rva0020C140
{
public:
	bool check( void );

	char m_pad[ 4 ];
	Open20C140Other *m_other;
	Open20C140Object *m_object;
	char m_pad2[ 0x40 ];
	unsigned char m_latch;
};

// @?check@Rva0020C140@@QAE_NXZ 0x0020C140
bool Rva0020C140::check( void )
{
	if( m_latch == 0 )
		return false;

	unsigned int flags = m_object->m_flags;
	if( ( flags & 0x200000 ) != 0 && m_other->m_kind == 1 )
	{
		m_latch = 0;
		return false;
	}

	if( ( flags & 4 ) == 0 && ( flags & 0x80000 ) == 0 )
		return true;
	return false;
}

// ---------------------------------------------------------------------------
// 0x0029BF00 -- walk a chain of items looking for one that matches.
//
// The walk is two virtuals -- one to start, one to advance -- and the argument
// is only read once the first item exists, which is why its load sits inside
// the guard rather than in the prologue.

class Open29BF00Item
{
public:
	char m_pad[ 4 ];
	int m_kind;
	char m_pad2[ 4 ];
	void *m_data;
};

class Rva0029BF00
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
	virtual Open29BF00Item *slot48();
	virtual Open29BF00Item *slot4C( Open29BF00Item *after );

	bool contains( void *want );
};

// @?contains@Rva0029BF00@@QAE_NPAX@Z 0x0029BF00
bool Rva0029BF00::contains( void *want )
{
	Open29BF00Item *item = slot48();
	while( item != 0 )
	{
		if( item->m_kind == 2 && item->m_data == want )
			return true;
		item = slot4C( item );
	}
	return false;
}

// ---------------------------------------------------------------------------
// 0x002B4490 -- two float readings compared for equality.
//
// `fucompp / fnstsw / test ah,0x44 / jp` is MSVC's `==` over two x87 values:
// equal leaves 0x40 in the masked byte, whose odd parity clears PF, so the
// jump is the not-equal arm.

class Open2B4490Meter
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual float slot10();
	virtual void slot14();
	virtual float slot18();
};

class Open2B4490Holder
{
public:
	char m_pad[ 0x200 ];
	Open2B4490Meter *m_meter;
};

// @?Rva002B4490@@YG_NPAVOpen2B4490Holder@@@Z 0x002B4490
bool __stdcall Rva002B4490( Open2B4490Holder *holder )
{
	Open2B4490Meter *meter = holder->m_meter;
	if( meter != 0 )
	{
		float first = meter->slot10();
		if( first == meter->slot18() )
			return true;
	}
	return false;
}
