// Sixteen 10-byte __cdecl bodies of the single shape
//
//     mov eax,[esp+4] / mov ds:<DIR32>,eax / ret
//
// WHAT THE BYTES SHOW.  The single dword argument is loaded off the stack and
// written to a fixed absolute address, and `ret` pops nothing: a __cdecl (or
// static-member) setter of a module-level variable, `void set(T v) { g = v; }`.
// A __thiscall or __stdcall spelling is excluded -- the former would take the
// value in ecx, the latter would `ret 4`.
//
// ONE AXIS: the address of the global.  It rides a DIR32 relocation, whose four
// bytes are verified against retail. The initialized scalar owners have
// data rows; all sixteen addresses are distinct.
//
// IDENTITY IS NOT RECOVERED.  Every class name is derived from the retail RVA.

#define BFME_GLOBAL_STORE( NAME )                                         \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		static void store( int value );                                     \
		static int s_value;                                                 \
	};                                                                     \
	void NAME::store( int value )                                          \
	{                                                                      \
		s_value = value;                                                    \
	}

BFME_GLOBAL_STORE( Rva0085A850 )
BFME_GLOBAL_STORE( Rva00882F80 )
BFME_GLOBAL_STORE( Rva00892340 )
BFME_GLOBAL_STORE( Rva00892360 )
BFME_GLOBAL_STORE( Rva008FE150 )
BFME_GLOBAL_STORE( Rva00937140 )
BFME_GLOBAL_STORE( Rva00956A70 )
BFME_GLOBAL_STORE( Rva009A58C0 )
BFME_GLOBAL_STORE( Rva001A1A30 )
BFME_GLOBAL_STORE( Rva006C5730 )
BFME_GLOBAL_STORE( Rva006E1BD0 )
BFME_GLOBAL_STORE( Rva006E7040 )
BFME_GLOBAL_STORE( Rva0075B2F0 )
BFME_GLOBAL_STORE( Rva00782DF0 )
BFME_GLOBAL_STORE( Rva00782E00 )
BFME_GLOBAL_STORE( Rva00782E10 )

int Rva0085A850::s_value;
int Rva00882F80::s_value;
int Rva00892340::s_value;
int Rva00892360::s_value;
int Rva008FE150::s_value;
int Rva00937140::s_value;
int Rva00956A70::s_value;
int Rva009A58C0::s_value;
int Rva006C5730::s_value;
int Rva006E1BD0::s_value = 2;
int Rva006E7040::s_value;
int Rva00782DF0::s_value;
int Rva00782E00::s_value;
int Rva00782E10::s_value;

// 0x00891C40: the same shape over a global another unit defines (Apt.cpp's
// data row at 0x01337A30), so it stores through that extern instead of a
// class-owned static. Unreferenced in retail.
struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

class Rva00891C40
{
public:
	static void store( BfmeStringPool3AF0 *value );
};

void Rva00891C40::store( BfmeStringPool3AF0 *value )
{
	g_rva01337A30AllocPair = value;
}

// 0x00891C50: the matching reset, directly after it: clears the same global.
// Unreferenced in retail.
class Rva00891C50
{
public:
	static void clear( void );
};

void Rva00891C50::clear( void )
{
	g_rva01337A30AllocPair = 0;
}

// 0x008FD620 stores into, and 0x008FD630 / 0x008FE160 read, the same global
// as Rva008FE150 above (0x012D6DC0), so they go through its static instead of
// defining another. All three are unreferenced in retail.
class Rva008FD620
{
public:
	static void store( int value );
};

void Rva008FD620::store( int value )
{
	Rva008FE150::s_value = value;
}

class Rva008FD630
{
public:
	static int get( void );
};

int Rva008FD630::get( void )
{
	return Rva008FE150::s_value;
}

class Rva008FE160
{
public:
	static int get( void );
};

int Rva008FE160::get( void )
{
	return Rva008FE150::s_value;
}

// 0x00937150 / 0x009A58D0 read the globals Rva00937140 (0x01346E4C) and
// Rva009A58C0 (0x0134C7DC) above store, the getter directly after each setter:
// `mov eax,[...] / ret`. Both are unreferenced in retail.
class Rva00937150
{
public:
	static int get( void );
};

int Rva00937150::get( void )
{
	return Rva00937140::s_value;
}

class Rva009A58D0
{
public:
	static int get( void );
};

int Rva009A58D0::get( void )
{
	return Rva009A58C0::s_value;
}

// 0x00882F70: `mov al,[0x0130E9F9] / ret`, directly before Rva00882F80, reads
// the byte the memory-pool allocator owns (data_rows.csv ?g_rva0130E9F9@@3EA).
// Unreferenced in retail.
extern unsigned char g_rva0130E9F9;

class Rva00882F70
{
public:
	static unsigned char get( void );
};

unsigned char Rva00882F70::get( void )
{
	return g_rva0130E9F9;
}

// 0x00892350: `mov byte ptr [0x0133780C],1 / ret`, between the Rva00892340 and
// Rva00892360 setters: raises the Apt flag AptTick00894660.cpp tests and
// clears. Unreferenced in retail. The byte is defined here, beside its
// only writer.
unsigned char g_rva0133780C;

class Rva00892350
{
public:
	static void raise( void );
};

void Rva00892350::raise( void )
{
	g_rva0133780C = 1;
}

