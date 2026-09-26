// EA FESL client SDK ("jabba") -- five small __thiscall members from the
// gamebrowser cluster that are complete on their own bytes.
//
// The neighbourhood is the same one U2FeslGameBrowserAsserts.cpp identified
// from its two assert sites; the reporter fetched at 0x007EB810 and the two
// counted-array clears at 0x00801570 / 0x00802A10 are already in the ledger and
// are reused here by name so their call sites resolve.
//
// WHAT THE BYTES SHOW.
//
// 0x008022A0 pushes FIVE dwords and cleans them itself before entering the
// reporter's THIRD vtable slot, with the reporter object as the first of the
// five.  That is MSVC's calling convention for a VARIADIC virtual member: a
// member with an ellipsis is __cdecl, so `this` becomes an ordinary stack
// argument.  The format it passes is retail's own "hpstate: %d -> %d\n", and
// the value it logs as the first %d is the field it overwrites with its
// argument immediately afterwards -- so the member is a state setter that
// traces the transition.  "hpstate" is retail's spelling; the member name is
// not.
//
// 0x00801830 and 0x00802BB0 are the same shape at two different offsets: run
// the embedded array-clear, then zero the two dwords that follow it.  The
// embedded object's size is fixed by the two offsets (0x3C + 8 = 0x44, and
// 0x1C + 8 = 0x24), which is what the already-landed clears' two fields give.
//
// IDENTITY IS NOT RECOVERED.  No class or member name here comes from the
// image; all are derived from addresses.  Nothing in the bytes says whether
// 0x00802290 and 0x008022A0 are members of ONE class -- their field offsets are
// merely compatible -- so they are spelled as two.

// ---------------------------------------------------------- the reporter
struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void log( int level, const char *format, ... );
	virtual void fail( const char *expr, const char *file, int line );
};

extern Rva007EB810Diag *Rva007EB810Get();

// ------------------------------------- the two already-landed array clears
class Rva00801570Elem
{
public:
	virtual void step( int flags );
	char m_pad[ 48 - 4 ];
};

class Rva00801570
{
public:
	void clear();

	Rva00801570Elem *m_array;
	int m_count;
};

class Rva00802A10Elem
{
public:
	virtual void step( int flags );
	char m_pad[ 128 - 4 ];
};

class Rva00802A10
{
public:
	void clear();

	Rva00802A10Elem *m_array;
	int m_count;
};

// ------------------------------------------------------------------ rows
class Rva00802290Owner
{
public:
	void reset();               // 0x00802290

	int m_field0;
	int m_field4;
	int m_field8;
	int m_fieldC;
};

void Rva00802290Owner::reset()
{
	m_field4 = 0;
	m_fieldC = 0;
	m_field8 = 0;
}

class Rva008022A0Owner
{
public:
	void setHpState( int state );   // 0x008022A0

	int m_field0;
	int m_field4;
	int m_field8;
	int m_hpState;
};

void Rva008022A0Owner::setHpState( int state )
{
	Rva007EB810Get()->log( 0, "hpstate: %d -> %d\n", m_hpState, state );
	m_hpState = state;
}

class Rva00801830Owner
{
public:
	void clear();               // 0x00801830

	char        m_pad000[ 0x3C ];
	Rva00801570 m_entries;      // +0x3C
	int         m_field44;
	int         m_field48;
};

void Rva00801830Owner::clear()
{
	m_entries.clear();
	m_field44 = 0;
	m_field48 = 0;
}

class Rva00802BB0Owner
{
public:
	void clear();               // 0x00802BB0

	char        m_pad000[ 0x1C ];
	Rva00802A10 m_entries;      // +0x1C
	int         m_field24;
	int         m_field28;
};

void Rva00802BB0Owner::clear()
{
	m_entries.clear();
	m_field24 = 0;
	m_field28 = 0;
}
