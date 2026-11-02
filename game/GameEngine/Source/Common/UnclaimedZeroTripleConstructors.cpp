// cl: /O2 /DNDEBUG /MD /EHsc
//
// Forty 15-byte thiscall constructors with identical bytes, each its own
// retail body (retail was linked without identical-COMDAT folding):
//     mov eax,ecx ; xor ecx,ecx ; mov [eax],ecx ; mov [eax+4],ecx ;
//     mov [eax+8],ecx ; ret 4
// i.e. a constructor that zeroes three dwords and ignores one stack argument
// (the shape of an STLport vector constructor taking its allocator by
// reference). Every one is reached through its own gen-thunk ILT stub (noted
// per body), so each is an external function whose real name is unknown. All
// were gen-alias placeholders borrowing a byte-identical COMDAT from
// GameAudio.cpp.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the
// argument is an unread reference of unknown type.

// 0x00067020 (15 bytes): reached through ILT stub 0x000360E8
class Rva00067020
{
public:
	Rva00067020( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00067020::Rva00067020( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00068EE0 (15 bytes): reached through ILT stub 0x0001B829
class Rva00068EE0
{
public:
	Rva00068EE0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00068EE0::Rva00068EE0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00076250 (15 bytes): reached through ILT stub 0x00003887
class Rva00076250
{
public:
	Rva00076250( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00076250::Rva00076250( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000762D0 (15 bytes): reached through ILT stub 0x0004692F
class Rva000762D0
{
public:
	Rva000762D0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000762D0::Rva000762D0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00076330 (15 bytes): reached through ILT stub 0x0002344D
class Rva00076330
{
public:
	Rva00076330( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00076330::Rva00076330( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00076390 (15 bytes): reached through ILT stub 0x0003CF0B
class Rva00076390
{
public:
	Rva00076390( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00076390::Rva00076390( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00095A30 (15 bytes): reached through ILT stub 0x00026D87
class Rva00095A30
{
public:
	Rva00095A30( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00095A30::Rva00095A30( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00095AC0 (15 bytes): reached through ILT stub 0x00032C2C
class Rva00095AC0
{
public:
	Rva00095AC0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00095AC0::Rva00095AC0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000A0EC0 (15 bytes): reached through ILT stub 0x0003FCB5
class Rva000A0EC0
{
public:
	Rva000A0EC0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000A0EC0::Rva000A0EC0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000A7930 (15 bytes): reached through ILT stub 0x0002C05C
class Rva000A7930
{
public:
	Rva000A7930( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000A7930::Rva000A7930( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000A7950 (15 bytes): reached through ILT stub 0x0001E984
class Rva000A7950
{
public:
	Rva000A7950( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000A7950::Rva000A7950( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000B0320 (15 bytes): reached through ILT stub 0x0000D6A7
class Rva000B0320
{
public:
	Rva000B0320( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000B0320::Rva000B0320( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000B0340 (15 bytes): reached through ILT stub 0x00026B07
class Rva000B0340
{
public:
	Rva000B0340( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000B0340::Rva000B0340( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000CE870 (15 bytes): reached through ILT stub 0x00030567
class Rva000CE870
{
public:
	Rva000CE870( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000CE870::Rva000CE870( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000D0170 (15 bytes): reached through ILT stub 0x000493FF
class Rva000D0170
{
public:
	Rva000D0170( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000D0170::Rva000D0170( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000D01F0 (15 bytes): reached through ILT stub 0x0000D1D9
class Rva000D01F0
{
public:
	Rva000D01F0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000D01F0::Rva000D01F0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000D04D0 (15 bytes): reached through ILT stub 0x00035062
class Rva000D04D0
{
public:
	Rva000D04D0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000D04D0::Rva000D04D0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000E17F0 (15 bytes): reached through ILT stub 0x0002EF5F
class Rva000E17F0
{
public:
	Rva000E17F0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000E17F0::Rva000E17F0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000E50F0 (15 bytes): reached through ILT stub 0x000290F0
class Rva000E50F0
{
public:
	Rva000E50F0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000E50F0::Rva000E50F0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000E5110 (15 bytes): reached through ILT stub 0x00032961
class Rva000E5110
{
public:
	Rva000E5110( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000E5110::Rva000E5110( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000E7720 (15 bytes): reached through ILT stub 0x00001794
class Rva000E7720
{
public:
	Rva000E7720( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000E7720::Rva000E7720( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000EB8E0 (15 bytes): reached through ILT stub 0x000226A6
class Rva000EB8E0
{
public:
	Rva000EB8E0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000EB8E0::Rva000EB8E0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000FA370 (15 bytes): reached through ILT stub 0x000471B8
class Rva000FA370
{
public:
	Rva000FA370( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000FA370::Rva000FA370( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000FD760 (15 bytes): reached through ILT stub 0x00044CDD
class Rva000FD760
{
public:
	Rva000FD760( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000FD760::Rva000FD760( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x000FD780 (15 bytes): reached through ILT stub 0x00024A4B
class Rva000FD780
{
public:
	Rva000FD780( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva000FD780::Rva000FD780( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00127380 (15 bytes): reached through ILT stub 0x0000C338
class Rva00127380
{
public:
	Rva00127380( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00127380::Rva00127380( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00127540 (15 bytes): reached through ILT stub 0x00019F4C
class Rva00127540
{
public:
	Rva00127540( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00127540::Rva00127540( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00127560 (15 bytes): reached through ILT stub 0x00041326
class Rva00127560
{
public:
	Rva00127560( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00127560::Rva00127560( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00127580 (15 bytes): reached through ILT stub 0x0001E187
class Rva00127580
{
public:
	Rva00127580( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00127580::Rva00127580( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001401F0 (15 bytes): reached through ILT stub 0x00021742
class Rva001401F0
{
public:
	Rva001401F0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001401F0::Rva001401F0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00140210 (15 bytes): reached through ILT stub 0x0003CBB4
class Rva00140210
{
public:
	Rva00140210( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00140210::Rva00140210( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00140230 (15 bytes): reached through ILT stub 0x000254E1
class Rva00140230
{
public:
	Rva00140230( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00140230::Rva00140230( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001402F0 (15 bytes): reached through ILT stub 0x00009B56
class Rva001402F0
{
public:
	Rva001402F0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001402F0::Rva001402F0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00140490 (15 bytes): reached through ILT stub 0x00033537
class Rva00140490
{
public:
	Rva00140490( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00140490::Rva00140490( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001406D0 (15 bytes): reached through ILT stub 0x00009859
class Rva001406D0
{
public:
	Rva001406D0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001406D0::Rva001406D0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00140A40 (15 bytes): reached through ILT stub 0x0001D2AA
class Rva00140A40
{
public:
	Rva00140A40( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00140A40::Rva00140A40( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00151A60 (15 bytes): reached through ILT stub 0x00033474
class Rva00151A60
{
public:
	Rva00151A60( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00151A60::Rva00151A60( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00195710 (15 bytes): reached through ILT stub 0x0002AECD
class Rva00195710
{
public:
	Rva00195710( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00195710::Rva00195710( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00195770 (15 bytes): reached through ILT stub 0x0003397E
class Rva00195770
{
public:
	Rva00195770( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00195770::Rva00195770( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00195790 (15 bytes): reached through ILT stub 0x00042C76
class Rva00195790
{
public:
	Rva00195790( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00195790::Rva00195790( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}
