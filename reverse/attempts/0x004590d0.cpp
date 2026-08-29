// ?d_004590d0@@YAXXZ
// partial score=0.9 date=2026-08-29
// ---------------------------------------------------------------------------
// 0x004590D0 -- translate a bitfield into four separate flag words.
//
// The tests read the argument out of BL and BH, so the bits checked are 2, 3,
// 5 and 9 of a value held whole in one register across the body.  Only the
// first arm reaches a global, and only to compare one field against 0x17.

class Open24590D0Probe
{
public:
	char m_pad[ 0x10 ];
	int m_kind;
};

class Open24590D0Source
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
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void slotB4();
	virtual void slotB8();
	virtual Open24590D0Probe *slotBC();
};

class Open24590D0Out
{
public:
	int m_first;
	int m_second;
	int m_third;
	int m_fourth;
	int m_fifth;
};

extern Open24590D0Source *TheOpen24590D0Source;

// @?Rva004590D0@@YAXIPAVOpen24590D0Out@@@Z 0x004590D0
void Rva004590D0( unsigned int flags, Open24590D0Out *out )
{
	if( ( flags & 4 ) != 0 )
	{
		out->m_first |= 2;

		Open24590D0Probe *probe = TheOpen24590D0Source->slotBC();
		if( probe != 0 && probe->m_kind == 0x17 )
			out->m_second |= 0x8000000;
	}

	if( ( flags & 8 ) != 0 )
		out->m_first |= 0x40;

	if( ( flags & 0x200 ) != 0 )
	{
		out->m_fourth = out->m_fourth | 1;
		out->m_fifth = out->m_fifth | 0x80;
	}

	if( ( flags & 0x20 ) != 0 )
		out->m_third |= 8;
}

