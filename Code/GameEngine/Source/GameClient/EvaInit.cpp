// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?init@Eva@@: Code/GameEngine/Source/GameClient/Eva.cpp

// Eva::init, 0x00426680, 258 bytes.
//
// This row was logged blocked three times, most recently with "the FIRST byte
// already diverges" -- retail opening with the classic inline SEH prologue and
// an out-of-line AsciiString(const char *) while our build emitted a call-based
// EH-prolog helper and the shim's compile-time-strlen fast path. That diagnosis
// was accurate about the bytes and wrong about the cause: it was not an
// AsciiString-shape blocker at all, it was the TU. Eva.cpp pulls in the whole
// vendored Zero Hour include set, and that is what changes both the prologue
// form and the string constructor's inline visibility. Compiled in its own file
// against nothing, the prologue and the out-of-line call are what MSVC 7.1
// emits by default, and the first 27 bytes match with no work at all.
//
// Two further shape facts, both of the "declare it, do not define it" kind:
//
//  - Both by-value arguments (the AsciiString handed to INI::load and the
//    24-byte check seed handed to resize) are built directly in their argument
//    slot in retail. MSVC only does that when the type has a user-declared copy
//    constructor; with the implicit one it materialises a named local and
//    copies. Declaring the copy constructor is what removes the local -- and,
//    for the check seed, what takes the frame from 0x864 back to retail's 0x84c.
//  - The element count is evaluated BEFORE the seed. Argument evaluation is
//    right-to-left, so it cannot come from `resize(m_messages.size(), Check())`;
//    retail's source reads the count into its own local first.
//
// The layout is the one the earlier entries recovered, and it holds:
//
//   0x00  vptr                    (vtable 0x010F1FA8, init in slot 1)
//   0x0c  m_messages              12-byte table of 28-byte VALUE elements --
//   0x18  m_messagesDefault       not the vendored header's pointer vector; the
//                                 28-byte stride is what the 0x92492493/sar 4
//                                 division at 0x0042671f measures.
//   0x24  m_sideSounds            20 bytes each; the assignment between them is
//   0x38  m_sideSoundsDefault     an inlined operator= with the usual
//                                 `this != &that` guard around destroy+assign.
//   0x4c  m_checks                resized to the message count, seeded with a
//                                 24-byte value whose two leading floats are
//                                 -1.0f and whose byte at +0x14 is zero; the
//                                 12 bytes at +8..+0x10 are deliberately left
//                                 alone, which is why the seed's constructor
//                                 touches only three of its members.
//
// INI is 0x848 bytes here, not the vendored size, and both loads are real: the
// two string literals at 0x010F1FE8 and 0x010F1FD4 are Data\INI\Default\Eva.ini
// and Data\INI\Eva.ini, so defaults load first and the override second.
//
// Everything below is declared locally at retail offsets rather than through a
// header: INI, AsciiString and StringBase<char> are named truthfully, so their
// calls resolve straight to the matched bodies at 0x00851230, 0x008512E0,
// 0x00853A20 and 0x00888BC0 with no new pins. The three container types are
// still unidentified, so they carry Eva-scoped names and their entry points are
// pinned by address only.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Xfer;

template <typename T> class StringBase
{
friend class AsciiString;
private:
	StringBase( void );
	StringBase( const StringBase<T> &that );
	StringBase( const T *text );
	void releaseBuffer( void );
public:
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( text );
	}
	AsciiString( const AsciiString &that )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that );
	}
	~AsciiString( void );
private:
	char *m_text;
};

enum INILoadType
{
	INI_LOAD_OVERWRITE = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	INI( void );
	~INI( void );
	void load( AsciiString filename,
		INILoadType loadType, Xfer *xfer );
private:
	char m_unported[0x848];
};

struct EvaMessageInfo
{
	char m_unported[28];
};

class EvaMessageVector
{
public:
	void assign( const EvaMessageVector &that );
	Int size( void ) const { return m_end - m_begin; }

private:
	EvaMessageInfo *m_begin;
	EvaMessageInfo *m_end;
	EvaMessageInfo *m_capacity;
};

class EvaSideSoundVector
{
public:
	EvaSideSoundVector &operator=( const EvaSideSoundVector &that )
	{
		if ( &that != this )
		{
			destroy();
			assign( that );
		}
		return *this;
	}

	void destroy( void );
	void assign( const EvaSideSoundVector &that );

private:
	char m_unported[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheck
{
	EvaCheck( void )
	{
		m_a = -1.0f;
		m_b = -1.0f;
		m_flag = 0;
	}
	EvaCheck( const EvaCheck &that );
	~EvaCheck( void );

	Real m_a;
	Real m_b;
	void *m_c;
	UnsignedInt m_d;
	UnsignedInt m_e;
	char m_flag;
};

class EvaCheckVector
{
public:
	void resize( Int count, EvaCheck value );

private:
	char m_unported[0x0c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
class Eva
{
public:
	virtual void init();

private:
	char m_unported[8];							// this+0x04
	EvaMessageVector m_messages;				// this+0x0c
	EvaMessageVector m_messagesDefault;			// this+0x18
	EvaSideSoundVector m_sideSounds;			// this+0x24
	EvaSideSoundVector m_sideSoundsDefault;		// this+0x38
	EvaCheckVector m_checks;					// this+0x4c
};

void Eva::init()
{
	INI ini;

	ini.load( AsciiString( "Data\\INI\\Default\\Eva.ini" ),
		INI_LOAD_OVERWRITE, 0 );
	ini.load( AsciiString( "Data\\INI\\Eva.ini" ),
		INI_LOAD_OVERWRITE, 0 );

	m_messages.assign( m_messagesDefault );
	m_sideSounds = m_sideSoundsDefault;
	Int count = m_messages.size();
	m_checks.resize( count, EvaCheck() );
}
