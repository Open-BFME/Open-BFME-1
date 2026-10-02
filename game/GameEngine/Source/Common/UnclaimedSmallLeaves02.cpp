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

// 0x007F0390 (11 bytes): zeroes the dword at +0x224
class Rva007F0390
{
public:
	void clear();

	char m_lead[ 0x224 ];
	int m_224;
};

void Rva007F0390::clear()
{
	m_224 = 0;
}

// 0x007F0BC0 (10 bytes): stores its byte argument at +0x1D
class Rva007F0BC0
{
public:
	void set( char value );

	char m_lead[ 0x1D ];
	char m_1d;
};

void Rva007F0BC0::set( char value )
{
	m_1d = value;
}

// 0x007F3580 (8 bytes): zeroes the dword at +0x58
class Rva007F3580
{
public:
	void clear();

	char m_lead[ 0x58 ];
	int m_58;
};

void Rva007F3580::clear()
{
	m_58 = 0;
}

// 0x007F5520 (11 bytes): +0x2C or else +0x28
class Rva007F5520
{
public:
	int get() const;

	char m_lead[ 0x28 ];
	int m_28;
	int m_2c;
};

int Rva007F5520::get() const
{
	int value = m_2c;
	if ( !value )
		value = m_28;
	return value;
}

// 0x007F90D0 (11 bytes): zeroes +4 +0 +8
class Rva007F90D0
{
public:
	void clear();

	int m_0;
	int m_4;
	int m_8;
};

void Rva007F90D0::clear()
{
	m_4 = 0;
	m_0 = 0;
	m_8 = 0;
}

// 0x007F9490 (8 bytes): pre-increments +0xC and returns it
class Rva007F9490
{
public:
	int increment();

	char m_lead[ 0xC ];
	int m_c;
};

int Rva007F9490::increment()
{
	return ++m_c;
}

// 0x00802180 (13 bytes): returns the 64-bit value at +0x90
class Rva00802180
{
public:
	__int64 get() const;

	char m_lead[ 0x90 ];
	__int64 m_90;
};

__int64 Rva00802180::get() const
{
	return m_90;
}

// 0x008021F0 (12 bytes): zeroes +4 +0x24 +0x28
class Rva008021F0
{
public:
	void clear();

	int m_0;
	int m_4;
	char m_lead[ 0x1C ];
	int m_24;
	int m_28;
};

void Rva008021F0::clear()
{
	m_4 = 0;
	m_24 = 0;
	m_28 = 0;
}

// 0x00803500 (12 bytes): zeroes +0xC +0x10 +0x14
class Rva00803500
{
public:
	void clear();

	char m_lead[ 0xC ];
	int m_c;
	int m_10;
	int m_14;
};

void Rva00803500::clear()
{
	m_c = 0;
	m_10 = 0;
	m_14 = 0;
}

// 0x00808A90 (8 bytes): post-increments the first dword
class Rva00808A90
{
public:
	int postIncrement();

	int m_0;
};

int Rva00808A90::postIncrement()
{
	return m_0++;
}

// 0x00808C10 (14 bytes): stdcall store of 0xC0000000 at +0x20 of its argument
struct Rva00808C10Record
{
	char m_lead[ 0x20 ];
	unsigned int m_20;
};

void __stdcall Rva00808C10( Rva00808C10Record *record )
{
	record->m_20 = 0xC0000000;
}

// 0x00808F50 (19 bytes): now minus +0x1C below 3000
class Rva00808F50
{
public:
	int isRecent( unsigned int now ) const;

	char m_lead[ 0x1C ];
	unsigned int m_1c;
};

int Rva00808F50::isRecent( unsigned int now ) const
{
	return now - m_1c < 3000;
}

// 0x008231C0 (13 bytes): cdecl count + count/2 + 0x20
unsigned int Rva008231C0( unsigned int count )
{
	return ( count >> 1 ) + count + 0x20;
}

// 0x008231F0 (13 bytes): cdecl count + count/2 + 0x20
unsigned int Rva008231F0( unsigned int count )
{
	return ( count >> 1 ) + count + 0x20;
}

// 0x0084DBA0 (8 bytes): cdecl byte at +0xA of its argument
char Rva0084DBA0( const char *record )
{
	return record[ 0xA ];
}

// 0x0084DBB0 (8 bytes): cdecl byte at +0xE of its argument
char Rva0084DBB0( const char *record )
{
	return record[ 0xE ];
}

// 0x0084DC00 (8 bytes): cdecl argument plus 0x18
char *Rva0084DC00( char *record )
{
	return record + 0x18;
}

// 0x0084DC10 (8 bytes): cdecl argument plus 0x1D
char *Rva0084DC10( char *record )
{
	return record + 0x1D;
}

// 0x0084DC20 (8 bytes): cdecl byte at +0xA of its argument
char Rva0084DC20( const char *record )
{
	return record[ 0xA ];
}

// 0x0084DC30 (8 bytes): cdecl byte at +0xE of its argument
char Rva0084DC30( const char *record )
{
	return record[ 0xE ];
}

// 0x0084DC60 (8 bytes): cdecl argument plus 0x28
char *Rva0084DC60( char *record )
{
	return record + 0x28;
}

// 0x0084DC70 (8 bytes): cdecl argument plus 0x23
char *Rva0084DC70( char *record )
{
	return record + 0x23;
}

// 0x0084DC80 (8 bytes): cdecl byte at +0x34 of its argument
char Rva0084DC80( const char *record )
{
	return record[ 0x34 ];
}

// 0x0084DC90 (8 bytes): cdecl byte at +0x30 of its argument
char Rva0084DC90( const char *record )
{
	return record[ 0x30 ];
}

// 0x00850E20 (10 bytes): element count of an 8-byte range at +8/+0xC
class Rva00850E20
{
public:
	int size() const;

	char m_lead[ 0x8 ];
	__int64 *m_begin;
	__int64 *m_end;
};

int Rva00850E20::size() const
{
	return m_end - m_begin;
}

// 0x00858140 (11 bytes): cdecl dword at +0x18D4 of its argument
struct Rva00858140Record
{
	char m_lead[ 0x18D4 ];
	int m_18d4;
};

int Rva00858140( const Rva00858140Record *record )
{
	return record->m_18d4;
}

// 0x008824A0 (8 bytes): cdecl argument minus 12
char *Rva008824A0( char *block )
{
	return block - 12;
}

// 0x008824D0 (8 bytes): text at +0xC plus the length at +8
class Rva008824D0
{
public:
	char *end();

	char m_lead[ 0x8 ];
	int m_length;
	char m_text[ 1 ];
};

char *Rva008824D0::end()
{
	return m_text + m_length;
}

// 0x008915F0 (10 bytes): bits 18-19 of +0x60
class Rva008915F0
{
public:
	unsigned int field() const;

	char m_lead[ 0x60 ];
	unsigned int m_60;
};

unsigned int Rva008915F0::field() const
{
	return ( m_60 >> 18 ) & 3;
}

// 0x00891600 (9 bytes): low word of +0x60
class Rva00891600
{
public:
	unsigned int field() const;

	char m_lead[ 0x60 ];
	unsigned int m_60;
};

unsigned int Rva00891600::field() const
{
	return m_60 & 0xFFFF;
}

// 0x00891790 (13 bytes): element i of the dword array at +8
class Rva00891790
{
public:
	int at( int index ) const;

	char m_lead[ 0x8 ];
	int *m_items;
};

int Rva00891790::at( int index ) const
{
	return m_items[ index ];
}

// 0x008918E0 (9 bytes): bit 15 of +4
class Rva008918E0
{
public:
	unsigned int bit15() const;

	char m_lead[ 0x4 ];
	unsigned int m_4;
};

unsigned int Rva008918E0::bit15() const
{
	return m_4 & 0x8000;
}

// 0x008919B0 (8 bytes): clears bit 30 of +4
class Rva008919B0
{
public:
	void clearBit30();

	char m_lead[ 0x4 ];
	unsigned int m_4;
};

void Rva008919B0::clearBit30()
{
	m_4 &= ~0x40000000u;
}

// 0x008919C0 (10 bytes): bit 30 of +4
class Rva008919C0
{
public:
	unsigned int bit30() const;

	char m_lead[ 0x4 ];
	unsigned int m_4;
};

unsigned int Rva008919C0::bit30() const
{
	return ( m_4 >> 30 ) & 1;
}

// 0x00892BF0 (13 bytes): zeroes the dword its argument points to
class Rva00892BF0
{
public:
	void clear( int *slot ) const;

};

void Rva00892BF0::clear( int *slot ) const
{
	*slot = 0;
}

// 0x00892C70 (9 bytes): 8-byte items at +8 plus the count at +0
class Rva00892C70
{
public:
	__int64 *end() const;

	int m_count;
	char m_lead[ 0x4 ];
	__int64 *m_items;
};

__int64 *Rva00892C70::end() const
{
	return m_items + m_count;
}

// 0x00894DA0 (12 bytes): cdecl pre-increment through its argument
int Rva00894DA0( int *counter )
{
	return ++*counter;
}

// 0x00895020 (13 bytes): zeroes the dword its argument points to
class Rva00895020
{
public:
	void clear( int *slot ) const;

};

void Rva00895020::clear( int *slot ) const
{
	*slot = 0;
}

// 0x00895040 (9 bytes): dword items at +8 plus the count at +0
class Rva00895040
{
public:
	int *end() const;

	int m_count;
	char m_lead[ 0x4 ];
	int *m_items;
};

int *Rva00895040::end() const
{
	return m_items + m_count;
}

// 0x00897170 (10 bytes): bit 14 of +4
class Rva00897170
{
public:
	unsigned int bit14() const;

	char m_lead[ 0x4 ];
	unsigned int m_4;
};

unsigned int Rva00897170::bit14() const
{
	return ( m_4 >> 14 ) & 1;
}

// 0x00897180 (12 bytes): bits 6-13 of +4
class Rva00897180
{
public:
	unsigned int field() const;

	char m_lead[ 0x4 ];
	unsigned int m_4;
};

unsigned int Rva00897180::field() const
{
	return ( m_4 >> 6 ) & 0xFF;
}

// 0x00897230 (8 bytes): cdecl argument minus 8
char *Rva00897230( char *block )
{
	return block - 8;
}

// 0x00897240 (8 bytes): cdecl dword before its argument
int Rva00897240( const int *block )
{
	return block[ -1 ];
}

// 0x00897250 (8 bytes): cdecl dword two before its argument
int Rva00897250( const int *block )
{
	return block[ -2 ];
}

// 0x008974B0 (8 bytes): cdecl clears bit 0
unsigned int Rva008974B0( unsigned int value )
{
	return value & ~1u;
}

// 0x008975C0 (10 bytes): bit 9 of +0x1C
class Rva008975C0
{
public:
	unsigned int bit9() const;

	char m_lead[ 0x1C ];
	unsigned int m_1c;
};

unsigned int Rva008975C0::bit9() const
{
	return ( m_1c >> 9 ) & 1;
}

// 0x008980F0 (12 bytes): low 12 bits of the word at +6
class Rva008980F0
{
public:
	unsigned int field() const;

	char m_lead[ 0x6 ];
	unsigned short m_6;
};

unsigned int Rva008980F0::field() const
{
	return m_6 & 0xFFF;
}

// 0x00898100 (8 bytes): sets bit 30 of +4
class Rva00898100
{
public:
	void setBit30();

	char m_lead[ 0x4 ];
	unsigned int m_4;
};

void Rva00898100::setBit30()
{
	m_4 |= 0x40000000;
}

// 0x00899CA0 (10 bytes): last dword of the array at +8 counted at +0
class Rva00899CA0
{
public:
	int back() const;

	int m_count;
	char m_lead[ 0x4 ];
	int *m_items;
};

int Rva00899CA0::back() const
{
	return m_items[ m_count - 1 ];
}

// 0x0089C820 (14 bytes): copies a handle and bumps its word count
class Rva0089C820
{
public:
	void share( const Rva0089C820 &other );

	unsigned short *m_handle;
};

void Rva0089C820::share( const Rva0089C820 &other )
{
	m_handle = other.m_handle;
	++*m_handle;
}

// 0x0089DC30 (13 bytes): stores its word argument through the pointer at +0
class Rva0089DC30
{
public:
	void set( short value );

	short *m_target;
};

void Rva0089DC30::set( short value )
{
	*m_target = value;
}

// 0x0089DCD0 (9 bytes): zeroes the word at +6 of the pointed block
class Rva0089DCD0
{
public:
	void clear();

	short *m_target;
};

void Rva0089DCD0::clear()
{
	m_target[ 3 ] = 0;
}

// 0x008A3060 (14 bytes): pre-decrements the count at +4 and returns that dword of +8
class Rva008A3060
{
public:
	int pop();

	char m_lead[ 0x4 ];
	int m_count;
	int *m_items;
};

int Rva008A3060::pop()
{
	return m_items[ --m_count ];
}

// 0x008BCFF0 (9 bytes): bit 0 of the byte at +0x62
class Rva008BCFF0
{
public:
	int bit0() const;

	char m_lead[ 0x62 ];
	unsigned char m_62;
};

int Rva008BCFF0::bit0() const
{
	return m_62 & 1;
}

// 0x008CB510 (10 bytes): last dword of the array at +8 counted at +0
class Rva008CB510
{
public:
	int back() const;

	int m_count;
	char m_lead[ 0x4 ];
	int *m_items;
};

int Rva008CB510::back() const
{
	return m_items[ m_count - 1 ];
}

// 0x008CB520 (10 bytes): last dword of the array at +8 counted at +0
class Rva008CB520
{
public:
	int back() const;

	int m_count;
	char m_lead[ 0x4 ];
	int *m_items;
};

int Rva008CB520::back() const
{
	return m_items[ m_count - 1 ];
}

// 0x008F7DC0 (15 bytes): zeroes dword i of the array at +0x24
class Rva008F7DC0
{
public:
	void clear( int index );

	char m_lead[ 0x24 ];
	int m_slots[ 1 ];
};

void Rva008F7DC0::clear( int index )
{
	m_slots[ index ] = 0;
}

// 0x00903360 (14 bytes): byte +0x39 of 0x54-byte record i
class Rva00903360
{
public:
	unsigned char value( int index ) const;

	struct Record { char m_lead[ 0x39 ]; unsigned char m_value; char m_rest[ 0x54 - 0x3A ]; } m_records[ 1 ];
};

unsigned char Rva00903360::value( int index ) const
{
	return m_records[ index ].m_value;
}

// 0x00912110 (9 bytes): bit 1 of +0x30
class Rva00912110
{
public:
	unsigned int bit1() const;

	char m_lead[ 0x30 ];
	unsigned int m_30;
};

unsigned int Rva00912110::bit1() const
{
	return ( m_30 >> 1 ) & 1;
}

// 0x00918D10 (8 bytes): zero-extended byte at +0x14B
class Rva00918D10
{
public:
	int get() const;

	char m_lead[ 0x14B ];
	unsigned char m_14b;
};

int Rva00918D10::get() const
{
	return m_14b;
}

// 0x00918D60 (10 bytes): flag 1 of +0x148
class Rva00918D60
{
public:
	unsigned int flag() const;

	char m_lead[ 0x148 ];
	unsigned int m_148;
};

unsigned int Rva00918D60::flag() const
{
	return m_148 & 1;
}

// 0x00918D70 (10 bytes): flag 2 of +0x148
class Rva00918D70
{
public:
	unsigned int flag() const;

	char m_lead[ 0x148 ];
	unsigned int m_148;
};

unsigned int Rva00918D70::flag() const
{
	return m_148 & 2;
}

// 0x00918D80 (10 bytes): flag 4 of +0x148
class Rva00918D80
{
public:
	unsigned int flag() const;

	char m_lead[ 0x148 ];
	unsigned int m_148;
};

unsigned int Rva00918D80::flag() const
{
	return m_148 & 4;
}

// 0x00918D90 (10 bytes): flag 8 of +0x148
class Rva00918D90
{
public:
	unsigned int flag() const;

	char m_lead[ 0x148 ];
	unsigned int m_148;
};

unsigned int Rva00918D90::flag() const
{
	return m_148 & 8;
}

// 0x0092C330 (10 bytes): +0x20 of the object at +0xC8
class Rva0092C330
{
public:
	int get() const;

	char m_lead[ 0xC8 ];
	struct Inner { char m_lead[ 0x20 ]; int m_20; } *m_inner;
};

int Rva0092C330::get() const
{
	return m_inner->m_20;
}

// 0x00933890 (8 bytes): zeroes the dword at +8
class Rva00933890
{
public:
	void clear();

	char m_lead[ 0x8 ];
	int m_8;
};

void Rva00933890::clear()
{
	m_8 = 0;
}

// 0x00933970 (8 bytes): zeroes the dword at +8
class Rva00933970
{
public:
	void clear();

	char m_lead[ 0x8 ];
	int m_8;
};

void Rva00933970::clear()
{
	m_8 = 0;
}

// 0x0093CFA0 (21 bytes): copies the word at +0 and dword at +4 and returns this
class Rva0093CFA0
{
public:
	Rva0093CFA0 &operator=( const Rva0093CFA0 &other );

	short m_0;
	short m_2;
	int m_4;
};

Rva0093CFA0 &Rva0093CFA0::operator=( const Rva0093CFA0 &other )
{
	m_0 = other.m_0;
	m_4 = other.m_4;
	return *this;
}

// 0x00945630 (14 bytes): +0xBC non-null
class Rva00945630
{
public:
	int has() const;

	char m_lead[ 0xBC ];
	void *m_bc;
};

int Rva00945630::has() const
{
	return m_bc != 0;
}

// 0x0094C6B0 (10 bytes): copies +8 of the object at +8 into +0x14
class Rva0094C6B0
{
public:
	void sync();

	char m_lead[ 0x8 ];
	struct Inner { char m_lead[ 8 ]; int m_8; } *m_inner;
	char m_gap[ 8 ];
	int m_14;
};

void Rva0094C6B0::sync()
{
	m_14 = m_inner->m_8;
}

// 0x009559D0 (15 bytes): stores argument != 0 at +0x20
class Rva009559D0
{
public:
	void set( int on );

	char m_lead[ 0x20 ];
	bool m_20;
};

void Rva009559D0::set( int on )
{
	m_20 = on != 0;
}

// 0x00955B30 (8 bytes): zero-extended byte at +0x108
class Rva00955B30
{
public:
	int get() const;

	char m_lead[ 0x108 ];
	unsigned char m_108;
};

int Rva00955B30::get() const
{
	return m_108;
}

// 0x00955BF0 (13 bytes): stores its argument at +0x100
class Rva00955BF0
{
public:
	void set( int value );

	char m_lead[ 0x100 ];
	int m_100;
};

void Rva00955BF0::set( int value )
{
	m_100 = value;
}

// 0x00955C30 (11 bytes): twice +0xD4 minus 2
class Rva00955C30
{
public:
	int get() const;

	char m_lead[ 0xD4 ];
	int m_d4;
};

int Rva00955C30::get() const
{
	return m_d4 * 2 - 2;
}

// 0x00958A20 (12 bytes): dword through the pointer at +0 or zero
class Rva00958A20
{
public:
	int get() const;

	int *m_p;
};

int Rva00958A20::get() const
{
	return m_p ? *m_p : 0;
}

// 0x00979380 (9 bytes): bit 20 of +0x10
class Rva00979380
{
public:
	unsigned int flag() const;

	char m_lead[ 0x10 ];
	unsigned int m_10;
};

unsigned int Rva00979380::flag() const
{
	return m_10 & 0x100000;
}

// 0x0098E9B0 (13 bytes): address of dword i of the array at +0xC
class Rva0098E9B0
{
public:
	int *at( int index ) const;

	char m_lead[ 0xC ];
	int *m_items;
};

int *Rva0098E9B0::at( int index ) const
{
	return &m_items[ index ];
}

// 0x009A2940 (28 bytes): stores at +0xC068 and marks +0xC06C when it changes
class Rva009A2940
{
public:
	void set( int value );

	char m_lead[ 0xC068 ];
	int m_value;
	char m_dirty;
};

void Rva009A2940::set( int value )
{
	if ( value != m_value )
	{
		m_value = value;
		m_dirty = 1;
	}
}

// 0x009A2F10 (9 bytes): inverted bit 0 of +0xC
class Rva009A2F10
{
public:
	unsigned int notBit0() const;

	char m_lead[ 0xC ];
	unsigned int m_c;
};

unsigned int Rva009A2F10::notBit0() const
{
	return ~m_c & 1;
}

// 0x009A2F20 (13 bytes): bit 0 of +0xC as 0/1
class Rva009A2F20
{
public:
	int bit0() const;

	char m_lead[ 0xC ];
	unsigned int m_c;
};

int Rva009A2F20::bit0() const
{
	return ( m_c & 1 ) == 1;
}

// 0x009A5870 (11 bytes): cdecl dword at +0x244 of its argument
struct Rva009A5870Record
{
	char m_lead[ 0x244 ];
	int m_244;
};

int Rva009A5870( const Rva009A5870Record *record )
{
	return record->m_244;
}

// 0x009D90B0 (15 bytes): zeroes +8 when set
class Rva009D90B0
{
public:
	void reset();

	char m_lead[ 0x8 ];
	int m_8;
};

void Rva009D90B0::reset()
{
	if ( m_8 )
		m_8 = 0;
}

// 0x009E1250 (9 bytes): top bit of +4
class Rva009E1250
{
public:
	unsigned int flag() const;

	char m_lead[ 0x4 ];
	unsigned int m_4;
};

unsigned int Rva009E1250::flag() const
{
	return m_4 & 0x80000000;
}

// 0x009EB900 (8 bytes): pre-increments +0x28 and returns it
class Rva009EB900
{
public:
	int increment();

	char m_lead[ 0x28 ];
	int m_28;
};

int Rva009EB900::increment()
{
	return ++m_28;
}

// 0x009ECA50 (15 bytes): stores a block and bumps its word count at +4
struct Rva009ECA50Block
{
	char m_lead[ 4 ];
	unsigned short m_refs;
};

class Rva009ECA50
{
public:
	Rva009ECA50( Rva009ECA50Block *block );

	Rva009ECA50Block *m_block;
};

Rva009ECA50::Rva009ECA50( Rva009ECA50Block *block )
{
	m_block = block;
	++block->m_refs;
}

#pragma pack( pop )
