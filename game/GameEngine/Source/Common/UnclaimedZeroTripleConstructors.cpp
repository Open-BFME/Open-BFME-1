// cl: /O2 /DNDEBUG /MD /EHsc
//
// Twenty 15-byte thiscall constructors with identical bytes, each its own
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
