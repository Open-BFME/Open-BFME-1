// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x0051D4A0 (145 B) of BfmeThingBHG, derived
// from _bfme_AptGameWindow (Rva00465430AptGameWindowDestructor.cpp): the own
// and second-base vtables are re-installed at +0 (0x11061C4) and +0x218
// (0x11061C0) before the base destructor is reached through ILT thunk
// 0x000204C3.  The body: if the global singleton g_bfmeThingBHG points at
// this object, release the COM/array member at +0x268 (Rva00690B40Owner,
// whose reset() is already matched) and clear the global; unconditionally
// release the AsciiString filename at +0x27C.  The member at +0x268 then
// unwinds automatically (its own real destructor deletes two owned array
// pointers, ILT thunk 0x00013B56).

class GameWindow
{
public:
	virtual ~GameWindow();

private:
	unsigned char m_pad[ 0x218 - 4 ];
};

class Gen_dtor_004654c0Base
{
public:
	virtual ~Gen_dtor_004654c0Base();

private:
	unsigned char m_pad[ 0x24C - 0x218 - 4 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class _bfme_AptGameWindow : public GameWindow, public Gen_dtor_004654c0Base
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	AsciiString m_filenameString;
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	void releaseBuffer( void );

private:
	char *m_data;
};

class Rva00690B40Owner
{
public:
	~Rva00690B40Owner();

	void reset( void );

private:
	void *m_arr0;
	void *m_arr4;
	char m_pad08[ 4 ];
	int m_comInitialized;
	void *m_unknown;
};

// The retail global at VA 0x012F49B4 is mis-pinned in reverse/symbols.csv
// under the name g_bfmeThingBHG at the WRONG address 0x00EF49B4 (a stale,
// pre-existing entry this lane does not own); to avoid colliding with that
// bad pin under the same mangled name, this TU names the global after its
// own address instead of reusing g_bfmeThingBHG.
struct Rva012F49B4Thing;
extern Rva012F49B4Thing *g_rva012F49B4;

struct BfmeThingBHG : public _bfme_AptGameWindow
{
public:
	virtual ~BfmeThingBHG();

private:
	unsigned char m_unreconstructed250[ 0x268 - 0x250 ];
	Rva00690B40Owner m_comOwner;
	BFMERetailAsciiString m_filename27C;
};

// ??1BfmeThingBHG@@UAE@XZ
BfmeThingBHG::~BfmeThingBHG()
{
	if( (void *)g_rva012F49B4 == (void *)this )
	{
		m_comOwner.reset();
		g_rva012F49B4 = 0;
	}
}
