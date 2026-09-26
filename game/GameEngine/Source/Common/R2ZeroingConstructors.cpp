// Thirty-five tiny __thiscall constructors, all one shape:
//
//     mov eax,ecx / xor ecx,ecx / <four or five member stores> / ret
//
// WHAT THE BYTES SHOW.  `mov eax,ecx` defines eax, is never read again inside
// the body, and the function ends in a bare `ret`: that is the __thiscall
// CONSTRUCTOR TAIL returning `this`, and it is why these are written as
// constructors rather than as void members.  `xor ecx,ecx` materialises the
// zero ONCE and every zero store then spells it `mov [eax+K],ecx` (or `,cl`
// for a byte), so the compiler saw two or more zero initialisers.
//
// THE STORE ORDER IS SOURCE ORDER.  MSVC 7.1 emits member initialisation in
// the order it is written, and four of the thirty-five prove it by NOT being
// in ascending offset order: 0x0015C490 stores +4 before +0, 0x00670130 stores
// +8 before +4 before +0, 0x00740940 stores +0xC first, and 0x007D3580 stores
// its +0 pointer LAST.  Each is transcribed in the order retail emits.
//
// NONE OF THE LEADING DWORD STORES IS A VPTR.  MSVC always writes the vptr
// before any member initialiser, so 0x007D3580 -- whose +0 store comes last --
// structurally cannot be one; and since that member proves the family holds an
// ordinary pointer-valued member at +0, the identical store at the FRONT of the
// others is written the same way rather than asserting a polymorphic class.
// The bytes do not distinguish the two for the leading case.  The addresses
// those stores hold are DIR32 sites the patcher fills from retail; the extern
// names below are address-derived placeholders and carry no type information.
//
// FIELD WIDTH IS READ FROM THE OPCODE: `mov [eax+K],ecx` is four bytes and
// `mov [eax+K],cl` is one.  Non-zero initialisers are transcribed as written:
// -1, 2, 4, 0x7F7FFFFF, 1.0f and -1.0f.  Whether 0x7F7FFFFF is a float in the
// source is not decidable from a `mov` of a plain immediate, so it is spelled
// as the integer the bytes actually contain.
//
// IDENTITY IS NOT RECOVERED.  Every class, member and extern name is derived
// from an address.  Members that share a layout are still separate rows at
// separate addresses and are instantiated separately.

extern int R2Data01075520;
extern int R2Data01083CFC;
extern int R2Data01085DBC;
extern int R2Data01088838;
extern int R2Data0109FB98;
extern int R2Data010BA790;
extern int R2Data010EC760;
extern int R2Data010EC768;
extern int R2Data01112ABC;
extern int R2Data01126B2C;
extern int R2Data011289D4;
extern int R2Data01128A2C;
extern int R2Data0109608C;
extern int R2Data0109F0F4;
extern int R2Data010E1F3C;
extern int R2Data010EC784;
extern int R2Data010F0540;
extern int R2Data010F0FA0;
extern int R2Data01126AFC;
extern int R2Data010C0D90;

class Rva000659C0
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva000659C0();
};
Rva000659C0::Rva000659C0()
{
	m_at00 = &R2Data01075520;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva0007BDF0
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	float m_at0C;
	Rva0007BDF0();
};
Rva0007BDF0::Rva0007BDF0()
{
	m_at00 = 0;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 1.0f;
}

class Rva000CBA50
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva000CBA50();
};
Rva000CBA50::Rva000CBA50()
{
	m_at00 = &R2Data01083CFC;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva000EC1E0
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	char m_at0C;
	Rva000EC1E0();
};
Rva000EC1E0::Rva000EC1E0()
{
	m_at00 = &R2Data01085DBC;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva00106B40
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva00106B40();
};
Rva00106B40::Rva00106B40()
{
	m_at00 = &R2Data01088838;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = -1;
}

class Rva0014FE90
{
public:
	int m_at00;
	char m_at04;
	char m_pad05[ 0x3 ];
	int m_at08;
	int m_at0C;
	Rva0014FE90();
};
Rva0014FE90::Rva0014FE90()
{
	m_at00 = 0;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva001DDC70
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva001DDC70();
};
Rva001DDC70::Rva001DDC70()
{
	m_at00 = &R2Data0109FB98;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva0027EE90
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva0027EE90();
};
Rva0027EE90::Rva0027EE90()
{
	m_at00 = &R2Data010BA790;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva0029BC80
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	char m_at0C;
	Rva0029BC80();
};
Rva0029BC80::Rva0029BC80()
{
	m_at00 = 0;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva003B7160
{
public:
	void * m_at00;
	int m_at04;
	char m_at08;
	char m_pad09[ 0x3 ];
	int m_at0C;
	Rva003B7160();
};
Rva003B7160::Rva003B7160()
{
	m_at00 = &R2Data010EC760;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva003B7720
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	char m_at0C;
	Rva003B7720();
};
Rva003B7720::Rva003B7720()
{
	m_at00 = &R2Data010EC768;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva005CBCC0
{
public:
	char m_pad00[ 0x4 ];
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva005CBCC0();
};
Rva005CBCC0::Rva005CBCC0()
{
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
}

class Rva005CBD00
{
public:
	char m_pad00[ 0x4 ];
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva005CBD00();
};
Rva005CBD00::Rva005CBD00()
{
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
}

class Rva005CC640
{
public:
	char m_pad00[ 0x8 ];
	int m_at08;
	int m_at0C;
	int m_at10;
	int m_at14;
	Rva005CC640();
};
Rva005CC640::Rva005CC640()
{
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
	m_at14 = 0;
}

class Rva005CC680
{
public:
	char m_pad00[ 0x8 ];
	int m_at08;
	int m_at0C;
	int m_at10;
	int m_at14;
	Rva005CC680();
};
Rva005CC680::Rva005CC680()
{
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
	m_at14 = 0;
}

class Rva005FD120
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	char m_at0C;
	Rva005FD120();
};
Rva005FD120::Rva005FD120()
{
	m_at00 = &R2Data01112ABC;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
}

class Rva007876D0
{
public:
	void * m_at00;
	char m_pad04[ 0x8 ];
	int m_at0C;
	int m_at10;
	int m_at14;
	Rva007876D0();
};
Rva007876D0::Rva007876D0()
{
	m_at00 = &R2Data01126B2C;
	m_at0C = 0;
	m_at10 = 0;
	m_at14 = 0;
}

class Rva007D2360
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva007D2360();
};
Rva007D2360::Rva007D2360()
{
	m_at00 = &R2Data011289D4;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 2;
}

class Rva007D3580
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva007D3580();
};
Rva007D3580::Rva007D3580()
{
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 2;
	m_at00 = &R2Data01128A2C;
}

class Rva007E3430
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva007E3430();
};
Rva007E3430::Rva007E3430()
{
	m_at00 = 0;
	m_at04 = 0;
	m_at08 = 4;
	m_at0C = 0;
}

class Rva00098430
{
public:
	char m_pad00[ 0x20 ];
	int m_at20;
	char m_pad24[ 0x4 ];
	int m_at28;
	char m_pad2C[ 0x4 ];
	int m_at30;
	char m_pad34[ 0x10 ];
	int m_at44;
	int m_at48;
	Rva00098430();
};
Rva00098430::Rva00098430()
{
	m_at20 = 0;
	m_at28 = 0;
	m_at30 = 0;
	m_at44 = 0;
	m_at48 = 0;
}

class Rva000C9180
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva000C9180();
};
Rva000C9180::Rva000C9180()
{
	m_at00 = 0;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0x7F7FFFFF;
}

class Rva0015C490
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva0015C490();
};
Rva0015C490::Rva0015C490()
{
	m_at04 = 0;
	m_at00 = &R2Data0109608C;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
}

class Rva001D5F00
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva001D5F00();
};
Rva001D5F00::Rva001D5F00()
{
	m_at00 = &R2Data0109F0F4;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
}

class Rva00322050
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva00322050();
};
Rva00322050::Rva00322050()
{
	m_at00 = &R2Data010E1F3C;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
}

class Rva003B85D0
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	char m_at10;
	Rva003B85D0();
};
Rva003B85D0::Rva003B85D0()
{
	m_at00 = &R2Data010EC784;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
}

class Rva00409520
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva00409520();
};
Rva00409520::Rva00409520()
{
	m_at00 = &R2Data010F0540;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
}

class Rva00410000
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva00410000();
};
Rva00410000::Rva00410000()
{
	m_at00 = &R2Data010F0FA0;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
}

class Rva005888D0
{
public:
	char m_at00;
	char m_pad01[ 0x3 ];
	int m_at04;
	char m_at08;
	char m_pad09[ 0x3 ];
	int m_at0C;
	float m_at10;
	Rva005888D0();
};
Rva005888D0::Rva005888D0()
{
	m_at00 = 0;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = -1.0f;
}

class Rva005889D0
{
public:
	char m_at00;
	char m_at01;
	char m_at02;
	char m_pad03[ 0x1 ];
	int m_at04;
	int m_at08;
	Rva005889D0();
};
Rva005889D0::Rva005889D0()
{
	m_at00 = 0;
	m_at01 = 0;
	m_at02 = 0;
	m_at04 = 0;
	m_at08 = 0;
}

class Rva005CD520
{
public:
	int m_at00;
	char m_pad04[ 0x8 ];
	int m_at0C;
	int m_at10;
	int m_at14;
	int m_at18;
	Rva005CD520();
};
Rva005CD520::Rva005CD520()
{
	m_at00 = 0;
	m_at0C = 0;
	m_at10 = 0;
	m_at14 = 0;
	m_at18 = 0;
}

class Rva005CD5C0
{
public:
	int m_at00;
	char m_pad04[ 0x8 ];
	int m_at0C;
	int m_at10;
	int m_at14;
	int m_at18;
	Rva005CD5C0();
};
Rva005CD5C0::Rva005CD5C0()
{
	m_at00 = 0;
	m_at0C = 0;
	m_at10 = 0;
	m_at14 = 0;
	m_at18 = 0;
}

class Rva00670130
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva00670130();
};
Rva00670130::Rva00670130()
{
	m_at08 = 0;
	m_at04 = 0;
	m_at00 = -1;
	m_at0C = 0;
	m_at10 = 0;
}

class Rva00740940
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva00740940();
};
Rva00740940::Rva00740940()
{
	m_at0C = 0;
	m_at00 = 0;
	m_at04 = 0;
	m_at08 = 0;
	m_at10 = 0;
}

class Rva00787380
{
public:
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	Rva00787380();
};
Rva00787380::Rva00787380()
{
	m_at00 = &R2Data01126AFC;
	m_at04 = 0;
	m_at08 = 0;
	m_at0C = 0;
	m_at10 = 0;
}
