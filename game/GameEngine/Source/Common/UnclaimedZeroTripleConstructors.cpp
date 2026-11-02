// cl: /O2 /DNDEBUG /MD /EHsc
//
// Eighty-eight 15-byte thiscall constructors with identical bytes, each its own
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

// 0x001957F0 (15 bytes): reached through ILT stub 0x00048806
class Rva001957F0
{
public:
	Rva001957F0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001957F0::Rva001957F0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001B69A0 (15 bytes): reached through ILT stub 0x0003484C
class Rva001B69A0
{
public:
	Rva001B69A0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001B69A0::Rva001B69A0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001B6B70 (15 bytes): reached through ILT stub 0x000462F9
class Rva001B6B70
{
public:
	Rva001B6B70( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001B6B70::Rva001B6B70( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001C4AD0 (15 bytes): reached through ILT stub 0x00027F9D
class Rva001C4AD0
{
public:
	Rva001C4AD0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001C4AD0::Rva001C4AD0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001D7130 (15 bytes): reached through ILT stub 0x00023AB5
class Rva001D7130
{
public:
	Rva001D7130( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001D7130::Rva001D7130( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001D71B0 (15 bytes): reached through ILT stub 0x0004356D
class Rva001D71B0
{
public:
	Rva001D71B0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001D71B0::Rva001D71B0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001DF8A0 (15 bytes): reached through ILT stub 0x0002B8E1
class Rva001DF8A0
{
public:
	Rva001DF8A0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001DF8A0::Rva001DF8A0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001E5040 (15 bytes): reached through ILT stub 0x00021210
class Rva001E5040
{
public:
	Rva001E5040( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001E5040::Rva001E5040( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001E5060 (15 bytes): reached through ILT stub 0x000262EC
class Rva001E5060
{
public:
	Rva001E5060( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001E5060::Rva001E5060( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001E5100 (15 bytes): reached through ILT stub 0x0002978F
class Rva001E5100
{
public:
	Rva001E5100( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001E5100::Rva001E5100( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001F9580 (15 bytes): reached through ILT stub 0x00046790
class Rva001F9580
{
public:
	Rva001F9580( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001F9580::Rva001F9580( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x001F95A0 (15 bytes): reached through ILT stub 0x0001A311
class Rva001F95A0
{
public:
	Rva001F95A0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva001F95A0::Rva001F95A0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x002061D0 (15 bytes): reached through ILT stub 0x00037A47
class Rva002061D0
{
public:
	Rva002061D0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva002061D0::Rva002061D0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00208540 (15 bytes): reached through ILT stub 0x0004382E
class Rva00208540
{
public:
	Rva00208540( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00208540::Rva00208540( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x0020EFE0 (15 bytes): reached through ILT stub 0x00045188
class Rva0020EFE0
{
public:
	Rva0020EFE0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva0020EFE0::Rva0020EFE0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00230270 (15 bytes): reached through ILT stub 0x0002CBE2
class Rva00230270
{
public:
	Rva00230270( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00230270::Rva00230270( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00235EE0 (15 bytes): reached through ILT stub 0x00043027
class Rva00235EE0
{
public:
	Rva00235EE0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00235EE0::Rva00235EE0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00235F40 (15 bytes): reached through ILT stub 0x0003378A
class Rva00235F40
{
public:
	Rva00235F40( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00235F40::Rva00235F40( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00235FA0 (15 bytes): reached through ILT stub 0x0002A626
class Rva00235FA0
{
public:
	Rva00235FA0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00235FA0::Rva00235FA0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00236160 (15 bytes): reached through ILT stub 0x00005ABF
class Rva00236160
{
public:
	Rva00236160( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00236160::Rva00236160( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x002361C0 (15 bytes): reached through ILT stub 0x00042451
class Rva002361C0
{
public:
	Rva002361C0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva002361C0::Rva002361C0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00236200 (15 bytes): reached through ILT stub 0x0001D877
class Rva00236200
{
public:
	Rva00236200( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00236200::Rva00236200( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00236260 (15 bytes): reached through ILT stub 0x00016301
class Rva00236260
{
public:
	Rva00236260( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00236260::Rva00236260( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00236280 (15 bytes): reached through ILT stub 0x0003472A
class Rva00236280
{
public:
	Rva00236280( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00236280::Rva00236280( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x002523C0 (15 bytes): reached through ILT stub 0x000454D5
class Rva002523C0
{
public:
	Rva002523C0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva002523C0::Rva002523C0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00258AB0 (15 bytes): reached through ILT stub 0x0003FD96
class Rva00258AB0
{
public:
	Rva00258AB0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00258AB0::Rva00258AB0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x0025BC20 (15 bytes): reached through ILT stub 0x0000B78A
class Rva0025BC20
{
public:
	Rva0025BC20( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva0025BC20::Rva0025BC20( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x0025DC90 (15 bytes): reached through ILT stub 0x0000E156
class Rva0025DC90
{
public:
	Rva0025DC90( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva0025DC90::Rva0025DC90( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x002612C0 (15 bytes): reached through ILT stub 0x00026986
class Rva002612C0
{
public:
	Rva002612C0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva002612C0::Rva002612C0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x002612E0 (15 bytes): reached through ILT stub 0x00017922
class Rva002612E0
{
public:
	Rva002612E0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva002612E0::Rva002612E0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00262EA0 (15 bytes): reached through ILT stub 0x00047B0E
class Rva00262EA0
{
public:
	Rva00262EA0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00262EA0::Rva00262EA0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00272EA0 (15 bytes): reached through ILT stub 0x0000D198
class Rva00272EA0
{
public:
	Rva00272EA0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00272EA0::Rva00272EA0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00281EC0 (15 bytes): reached through ILT stub 0x00011B85
class Rva00281EC0
{
public:
	Rva00281EC0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00281EC0::Rva00281EC0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00283B20 (15 bytes): reached through ILT stub 0x0002957D
class Rva00283B20
{
public:
	Rva00283B20( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00283B20::Rva00283B20( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00283B80 (15 bytes): reached through ILT stub 0x0002FFC2
class Rva00283B80
{
public:
	Rva00283B80( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00283B80::Rva00283B80( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00283BE0 (15 bytes): reached through ILT stub 0x00008A94
class Rva00283BE0
{
public:
	Rva00283BE0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00283BE0::Rva00283BE0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00288310 (15 bytes): reached through ILT stub 0x000449C2
class Rva00288310
{
public:
	Rva00288310( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00288310::Rva00288310( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x0028D890 (15 bytes): reached through ILT stub 0x000303FF
class Rva0028D890
{
public:
	Rva0028D890( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva0028D890::Rva0028D890( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x0028F780 (15 bytes): reached through ILT stub 0x0000A5CE
class Rva0028F780
{
public:
	Rva0028F780( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva0028F780::Rva0028F780( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x0028F7E0 (15 bytes): reached through ILT stub 0x00043C34
class Rva0028F7E0
{
public:
	Rva0028F7E0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva0028F7E0::Rva0028F7E0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00293910 (15 bytes): reached through ILT stub 0x0001BC1B
class Rva00293910
{
public:
	Rva00293910( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00293910::Rva00293910( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x00299DA0 (15 bytes): reached through ILT stub 0x0003698A
class Rva00299DA0
{
public:
	Rva00299DA0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva00299DA0::Rva00299DA0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x0029C790 (15 bytes): reached through ILT stub 0x00024B90
class Rva0029C790
{
public:
	Rva0029C790( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva0029C790::Rva0029C790( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x002DB590 (15 bytes): reached through ILT stub 0x0000C1E4
class Rva002DB590
{
public:
	Rva002DB590( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva002DB590::Rva002DB590( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x002E0510 (15 bytes): reached through ILT stub 0x0000940D
class Rva002E0510
{
public:
	Rva002E0510( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva002E0510::Rva002E0510( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x002E5690 (15 bytes): reached through ILT stub 0x0002DA06
class Rva002E5690
{
public:
	Rva002E5690( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva002E5690::Rva002E5690( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x002E56B0 (15 bytes): reached through ILT stub 0x00041E89
class Rva002E56B0
{
public:
	Rva002E56B0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva002E56B0::Rva002E56B0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}

// 0x002E56D0 (15 bytes): reached through ILT stub 0x0001A6DB
class Rva002E56D0
{
public:
	Rva002E56D0( const int &unused );

	void *m_0;
	void *m_4;
	void *m_8;
};

Rva002E56D0::Rva002E56D0( const int & )
{
	m_0 = 0;
	m_4 = 0;
	m_8 = 0;
}
