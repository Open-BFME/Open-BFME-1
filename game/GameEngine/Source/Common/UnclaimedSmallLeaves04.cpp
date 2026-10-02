// cl: /O2 /DNDEBUG /MD /EHsc
//
// Unclaimed call-free leaf bodies, each alone in a .text gap no ledger row
// covered: a 16-byte-aligned start directly after an int3 pad run, a terminal
// ret / ret N followed by int3 padding or the next matched row, and no call,
// ILT stub, table slot, code immediate, pin or dir32 name at the address.
// Each body gets its own address-derived class (or free function); members
// before an accessed field are spelled as a lead array because only their
// total size is witnessed, and member names say only what the bytes do.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#pragma pack( push, 1 )

// 0x007F0980 (7 bytes): 64-bit value at +8
class Rva007F0980
{
public:
	__int64 get() const;

	char m_lead[ 0x8 ];
	__int64 m_8;
};

__int64 Rva007F0980::get() const
{
	return m_8;
}

// 0x007F49D0 (5 bytes): returns zero and pops 1 dword(s)
class Rva007F49D0
{
public:
	int value( int ) const;

};

int Rva007F49D0::value( int ) const
{
	return 0;
}

// 0x007F8DB0 (3 bytes): ret 8 only
class Rva007F8DB0
{
public:
	void body( int, int );

};

void Rva007F8DB0::body( int, int )
{

}

// 0x007FBBC0 (5 bytes): returns zero and pops 3 dword(s)
class Rva007FBBC0
{
public:
	int value( int, int, int ) const;

};

int Rva007FBBC0::value( int, int, int ) const
{
	return 0;
}

// 0x007FD020 (5 bytes): returns zero and pops 3 dword(s)
class Rva007FD020
{
public:
	int value( int, int, int ) const;

};

int Rva007FD020::value( int, int, int ) const
{
	return 0;
}

// 0x008021A0 (7 bytes): 64-bit value at +8
class Rva008021A0
{
public:
	__int64 get() const;

	char m_lead[ 0x8 ];
	__int64 m_8;
};

__int64 Rva008021A0::get() const
{
	return m_8;
}

// 0x00849950 (7 bytes): dword at +0x8 of the object at +4
class Rva00849950
{
public:
	int get() const;

	int m_0;
	struct Inner { char m_lead[ 0x8 ]; int m_value; } *m_inner;
};

int Rva00849950::get() const
{
	return m_inner->m_value;
}

// 0x0087DCB0 (7 bytes): pointer at +0x4 minus 36
class Rva0087DCB0
{
public:
	char *adjusted() const;

	char m_lead[ 0x4 ];
	char *m_4;
};

char *Rva0087DCB0::adjusted() const
{
	return m_4 - 36;
}

// 0x008918D0 (7 bytes): mask 0x3F of +0x4
class Rva008918D0
{
public:
	unsigned int flag() const;

	char m_lead[ 0x4 ];
	unsigned int m_4;
};

unsigned int Rva008918D0::flag() const
{
	return m_4 & 0x3F;
}

// 0x00891B30 (7 bytes): word at +2 of the block at +0
class Rva00891B30
{
public:
	int length() const;

	struct Header { unsigned short m_refs; unsigned short m_length; } *m_header;
};

int Rva00891B30::length() const
{
	return m_header->m_length;
}

// 0x00894C70 (6 bytes): pre-increments +0 and returns it
class Rva00894C70
{
public:
	int step();

	int m_0;
};

int Rva00894C70::step()
{
	return ++m_0;
}

// 0x00894C80 (6 bytes): pre-decrements +0 and returns it
class Rva00894C80
{
public:
	int step();

	int m_0;
};

int Rva00894C80::step()
{
	return --m_0;
}

// 0x00894D70 (7 bytes): word at +2 of the block at +0
class Rva00894D70
{
public:
	int length() const;

	struct Header { unsigned short m_refs; unsigned short m_length; } *m_header;
};

int Rva00894D70::length() const
{
	return m_header->m_length;
}

// 0x00899310 (7 bytes): mask 0xFFFFFFFE of +0x8
class Rva00899310
{
public:
	unsigned int flag() const;

	char m_lead[ 0x8 ];
	unsigned int m_8;
};

unsigned int Rva00899310::flag() const
{
	return m_8 & 0xFFFFFFFE;
}

// 0x00899370 (7 bytes): mask 0xFFFFFFFE of +0xC
class Rva00899370
{
public:
	unsigned int flag() const;

	char m_lead[ 0xC ];
	unsigned int m_c;
};

unsigned int Rva00899370::flag() const
{
	return m_c & 0xFFFFFFFE;
}

// 0x0089C740 (7 bytes): mask 0x1 of +0x8
class Rva0089C740
{
public:
	unsigned int flag() const;

	char m_lead[ 0x8 ];
	unsigned int m_8;
};

unsigned int Rva0089C740::flag() const
{
	return m_8 & 0x1;
}

// 0x0089C770 (7 bytes): mask 0x1 of +0xC
class Rva0089C770
{
public:
	unsigned int flag() const;

	char m_lead[ 0xC ];
	unsigned int m_c;
};

unsigned int Rva0089C770::flag() const
{
	return m_c & 0x1;
}

// 0x0089E270 (5 bytes): returns zero and pops 1 dword(s)
class Rva0089E270
{
public:
	int value( int ) const;

};

int Rva0089E270::value( int ) const
{
	return 0;
}

// 0x0089E280 (5 bytes): returns zero and pops 1 dword(s)
class Rva0089E280
{
public:
	int value( int ) const;

};

int Rva0089E280::value( int ) const
{
	return 0;
}

// 0x0089E290 (5 bytes): returns zero and pops 2 dword(s)
class Rva0089E290
{
public:
	int value( int, int ) const;

};

int Rva0089E290::value( int, int ) const
{
	return 0;
}

// 0x0089E2A0 (5 bytes): returns zero and pops 2 dword(s)
class Rva0089E2A0
{
public:
	int value( int, int ) const;

};

int Rva0089E2A0::value( int, int ) const
{
	return 0;
}

// 0x008BF0E0 (5 bytes): adds 64 to +4
class Rva008BF0E0
{
public:
	void advance();

	int m_0;
	int m_4;
};

void Rva008BF0E0::advance()
{
	m_4 += 64;
}

// 0x008BF0F0 (5 bytes): adds -64 to +4
class Rva008BF0F0
{
public:
	void advance();

	int m_0;
	int m_4;
};

void Rva008BF0F0::advance()
{
	m_4 += -64;
}

// 0x008FEDA0 (7 bytes): pointer at +0x4 minus 12
class Rva008FEDA0
{
public:
	char *adjusted() const;

	char m_lead[ 0x4 ];
	char *m_4;
};

char *Rva008FEDA0::adjusted() const
{
	return m_4 - 12;
}

// 0x008FEDB0 (7 bytes): pointer at +0x4 minus 12
class Rva008FEDB0
{
public:
	char *adjusted() const;

	char m_lead[ 0x4 ];
	char *m_4;
};

char *Rva008FEDB0::adjusted() const
{
	return m_4 - 12;
}

// 0x00903420 (5 bytes): word at +0x10
class Rva00903420
{
public:
	short get() const;

	char m_lead[ 0x10 ];
	short m_10;
};

short Rva00903420::get() const
{
	return m_10;
}

// 0x00918820 (7 bytes): mask 0x1 of +0x44
class Rva00918820
{
public:
	unsigned int flag() const;

	char m_lead[ 0x44 ];
	unsigned int m_44;
};

unsigned int Rva00918820::flag() const
{
	return m_44 & 0x1;
}

// 0x00918830 (7 bytes): mask 0x2 of +0x44
class Rva00918830
{
public:
	unsigned int flag() const;

	char m_lead[ 0x44 ];
	unsigned int m_44;
};

unsigned int Rva00918830::flag() const
{
	return m_44 & 0x2;
}

// 0x00918840 (7 bytes): mask 0x4 of +0x44
class Rva00918840
{
public:
	unsigned int flag() const;

	char m_lead[ 0x44 ];
	unsigned int m_44;
};

unsigned int Rva00918840::flag() const
{
	return m_44 & 0x4;
}

// 0x00918850 (7 bytes): mask 0x8 of +0x44
class Rva00918850
{
public:
	unsigned int flag() const;

	char m_lead[ 0x44 ];
	unsigned int m_44;
};

unsigned int Rva00918850::flag() const
{
	return m_44 & 0x8;
}

// 0x0091CD90 (5 bytes): word at +0x4
class Rva0091CD90
{
public:
	short get() const;

	char m_lead[ 0x4 ];
	short m_4;
};

short Rva0091CD90::get() const
{
	return m_4;
}

// 0x00923B70 (7 bytes): +0x10 shifted left 2
class Rva00923B70
{
public:
	unsigned int scaled() const;

	char m_lead[ 0x10 ];
	unsigned int m_10;
};

unsigned int Rva00923B70::scaled() const
{
	return m_10 << 2;
}

// 0x00923B80 (7 bytes): +0x10 shifted left 4
class Rva00923B80
{
public:
	unsigned int scaled() const;

	char m_lead[ 0x10 ];
	unsigned int m_10;
};

unsigned int Rva00923B80::scaled() const
{
	return m_10 << 4;
}

// 0x0092C9A0 (5 bytes): sign-extended byte at +0x1C
class Rva0092C9A0
{
public:
	int get() const;

	char m_lead[ 0x1C ];
	signed char m_1c;
};

int Rva0092C9A0::get() const
{
	return m_1c;
}

// 0x0092D6A0 (7 bytes): dword at +0xC of the object at +4
class Rva0092D6A0
{
public:
	int get() const;

	int m_0;
	struct Inner { char m_lead[ 0xC ]; int m_value; } *m_inner;
};

int Rva0092D6A0::get() const
{
	return m_inner->m_value;
}

// 0x0093BE60 (5 bytes): returns false and pops 1 dword(s)
class Rva0093BE60
{
public:
	bool value( int ) const;

};

bool Rva0093BE60::value( int ) const
{
	return false;
}

// 0x0093BE70 (5 bytes): returns false and pops 1 dword(s)
class Rva0093BE70
{
public:
	bool value( int ) const;

};

bool Rva0093BE70::value( int ) const
{
	return false;
}

// 0x00944C10 (6 bytes): dword at +0xC; pops one unused dword
class Rva00944C10
{
public:
	int get( int ) const;

	char m_lead[ 0xC ];
	int m_c;
};

int Rva00944C10::get( int ) const
{
	return m_c;
}

// 0x00944E30 (7 bytes): dword at +0xC of the object at +4
class Rva00944E30
{
public:
	int get() const;

	int m_0;
	struct Inner { char m_lead[ 0xC ]; int m_value; } *m_inner;
};

int Rva00944E30::get() const
{
	return m_inner->m_value;
}

// 0x00944E80 (7 bytes): dword at +0xC of the object at +4
class Rva00944E80
{
public:
	int get() const;

	int m_0;
	struct Inner { char m_lead[ 0xC ]; int m_value; } *m_inner;
};

int Rva00944E80::get() const
{
	return m_inner->m_value;
}

// 0x00944E90 (7 bytes): dword at +0xC of the object at +4
class Rva00944E90
{
public:
	int get() const;

	int m_0;
	struct Inner { char m_lead[ 0xC ]; int m_value; } *m_inner;
};

int Rva00944E90::get() const
{
	return m_inner->m_value;
}

// 0x00955960 (5 bytes): zero-extended byte at +0x20
class Rva00955960
{
public:
	int get() const;

	char m_lead[ 0x20 ];
	unsigned char m_20;
};

int Rva00955960::get() const
{
	return m_20;
}

// 0x0095C5D0 (7 bytes): mask 0x1 of +0x40
class Rva0095C5D0
{
public:
	unsigned int flag() const;

	char m_lead[ 0x40 ];
	unsigned int m_40;
};

unsigned int Rva0095C5D0::flag() const
{
	return m_40 & 0x1;
}

// 0x0095C5E0 (7 bytes): mask 0x2 of +0x40
class Rva0095C5E0
{
public:
	unsigned int flag() const;

	char m_lead[ 0x40 ];
	unsigned int m_40;
};

unsigned int Rva0095C5E0::flag() const
{
	return m_40 & 0x2;
}

// 0x0095C5F0 (7 bytes): mask 0x4 of +0x40
class Rva0095C5F0
{
public:
	unsigned int flag() const;

	char m_lead[ 0x40 ];
	unsigned int m_40;
};

unsigned int Rva0095C5F0::flag() const
{
	return m_40 & 0x4;
}

// 0x0095C6B0 (5 bytes): zero-extended byte at +0x43
class Rva0095C6B0
{
public:
	int get() const;

	char m_lead[ 0x43 ];
	unsigned char m_43;
};

int Rva0095C6B0::get() const
{
	return m_43;
}

// 0x0096A7A0 (7 bytes): +0x18 shifted right 31
class Rva0096A7A0
{
public:
	unsigned int field() const;

	char m_lead[ 0x18 ];
	unsigned int m_18;
};

unsigned int Rva0096A7A0::field() const
{
	return m_18 >> 31;
}

// 0x0097BC10 (3 bytes): ret 12 only
class Rva0097BC10
{
public:
	void body( int, int, int );

};

void Rva0097BC10::body( int, int, int )
{

}

// 0x009A1740 (6 bytes): pointer at +0x0 minus 8
class Rva009A1740
{
public:
	char *adjusted() const;

	char *m_0;
};

char *Rva009A1740::adjusted() const
{
	return m_0 - 8;
}

// 0x009A1750 (6 bytes): pointer at +0x0 minus 8
class Rva009A1750
{
public:
	char *adjusted() const;

	char *m_0;
};

char *Rva009A1750::adjusted() const
{
	return m_0 - 8;
}

// 0x009A1760 (6 bytes): moves the pointer at +0 back 8 bytes and returns this
class Rva009A1760
{
public:
	Rva009A1760 *back8();

	char *m_0;
};

Rva009A1760 *Rva009A1760::back8()
{
	m_0 -= 8;
	return this;
}

// 0x009D9100 (3 bytes): ret 12 only
class Rva009D9100
{
public:
	void body( int, int, int );

};

void Rva009D9100::body( int, int, int )
{

}

// 0x009DCCB0 (6 bytes): pointer at +0x0 minus 8
class Rva009DCCB0
{
public:
	char *adjusted() const;

	char *m_0;
};

char *Rva009DCCB0::adjusted() const
{
	return m_0 - 8;
}

// 0x009F2FD0 (7 bytes): pointer at +0x4 minus 8
class Rva009F2FD0
{
public:
	char *adjusted() const;

	char m_lead[ 0x4 ];
	char *m_4;
};

char *Rva009F2FD0::adjusted() const
{
	return m_4 - 8;
}

#pragma pack( pop )

// Seven more of the same evidence class, spelled by hand.
#pragma pack( push, 1 )

// 0x00891AD0 (6 bytes): bumps the word count at +0 of the block at +0.
class Rva00891AD0
{
public:
	void addRef();

	unsigned short *m_refs;
};

void Rva00891AD0::addRef()
{
	++*m_refs;
}

// 0x0089C7A0 (7 bytes): word at +6 of the block at +0.
class Rva0089C7A0
{
public:
	short get() const;

	struct Block { char m_lead[ 6 ]; short m_6; } *m_block;
};

short Rva0089C7A0::get() const
{
	return m_block->m_6;
}

// 0x008D5E50 (5 bytes): increments the word at +0x60.
class Rva008D5E50
{
public:
	void increment();

	char m_lead[ 0x60 ];
	short m_60;
};

void Rva008D5E50::increment()
{
	++m_60;
}

// 0x00921280 (5 bytes): returns true and pops one dword.
class Rva00921280
{
public:
	bool value( int ) const;
};

bool Rva00921280::value( int ) const
{
	return true;
}

// 0x009245F0 (7 bytes): dword at +0xC of the object at +0x60.
class Rva009245F0
{
public:
	int get() const;

	char m_lead[ 0x60 ];
	struct Inner { char m_lead[ 0xC ]; int m_c; } *m_inner;
};

int Rva009245F0::get() const
{
	return m_inner->m_c;
}

// 0x00945B00 (6 bytes): dword at +0x28 of the object at +0.
class Rva00945B00
{
public:
	int get() const;

	struct Inner { char m_lead[ 0x28 ]; int m_28; } *m_inner;
};

int Rva00945B00::get() const
{
	return m_inner->m_28;
}

// 0x00AFE6D0 (4 bytes): decrements the dword at +0x14.
class Rva00AFE6D0
{
public:
	void decrement();

	char m_lead[ 0x14 ];
	int m_14;
};

void Rva00AFE6D0::decrement()
{
	--m_14;
}

#pragma pack( pop )
