// ?d_00786b70@@YAXXZ
// partial score=0.95 date=2026-08-29
// Open2Zero6 / open2ZeroSix helper shared by 0x00786B70 and 0x00787460
// ---------------------------------------------------------------------------
// 0x00786B70 -- constructor: vtable, three zeroed members, then a sub-object
// that zeroes six of its own.
//
//     mov [eax],VPTR / xor ecx,ecx / mov [eax+4],ecx ... lea edx,[eax+0x10]
//     mov [edx],ecx ... mov [edx+0x14],ecx
//
// The six trailing zeroes index off a MATERIALISED base at +0x10 while the
// first three index off `this`: that is a member with its own inline
// constructor, running after the initialiser list rather than inside it.

class Open2Zero6
{
public:
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	int m_e;
	int m_f;
};

static void open2ZeroSix( Open2Zero6 *slots )
{
	slots->m_a = 0;
	slots->m_b = 0;
	slots->m_c = 0;
	slots->m_d = 0;
	slots->m_e = 0;
	slots->m_f = 0;
}

class Rva00786B70
{
public:
	Rva00786B70();
	virtual void slot00();

	int m_x;
	int m_y;
	int m_z;
	Open2Zero6 m_sub;
};

// @??0Rva00786B70@@QAE@XZ 0x00786B70
Rva00786B70::Rva00786B70()
	: m_x( 0 ), m_y( 0 ), m_z( 0 )
{
	open2ZeroSix( &m_sub );
}

// ---------------------------------------------------------------------------
// 0x00787460 -- the same shape one member wider, and here the vtable store is
// SUNK to the end of the leading run of four zeroes, which is where MSVC puts
// it when the run's value differs from the pointer's.

class Rva00787460
{
public:
	Rva00787460();
	virtual void slot00();

	int m_a;
	int m_b;
	int m_c;
	int m_d;
	unsigned char m_e;
	unsigned char m_f;
	unsigned char m_pad[ 2 ];
	int m_g;
	Open2Zero6 m_sub;
};

// @??0Rva00787460@@QAE@XZ 0x00787460
Rva00787460::Rva00787460()
	: m_a( 0 ), m_b( 0 ), m_c( 0 ), m_d( 0 ), m_e( 0 ), m_f( 0 ), m_g( 0 )
{
	open2ZeroSix( &m_sub );
}

