// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception

// The INI block registry pairs the block name 'LightPointLevel' with this body.
// BFME keeps that registry as a linked list of 12-byte rows whose head is the
// global at VA 0x0130CE50, and the row at 0x012B4690 holds the name string and
// this address.

// The body reads a level name and takes one of two paths. A map.ini load looks
// the name up in the vector the light point system keeps at +0x08, walks that
// level's override chain to its end, copies the end over a fresh level, and
// links the fresh level on as the next override. A normal load builds a fresh
// level, gives it the name, and hands it to the system. Both paths then fill
// the level from the field table at 0x010EBE44.

// Four callees are already converted. The vector search is the body at
// 0x0039C1A0, the chain walk is Overridable::friend_getFinalOverride at
// 0x00097880, the copy is the assignment at 0x0039C830, and the insert is
// LightPointSystem::addLevel at 0x0039CAB0. The search is spelled as a member
// of the system because retail loads the system into ECX, computes the vector
// address from ECX, and leaves ECX alone across the call. A free function
// clobbers ECX instead and emits `add ecx,8' where retail emits a lea.

// The level is 0x20 bytes wide. It carries a vftable at +0, the override link
// at +4, the override flag at +8, the name at +0x0C, and four more fields the
// field table fills. The class is spelled with a non-polymorphic base holding
// the link and the flag, and a derived class that introduces the first virtual
// function. That puts the vftable pointer at +0 and the base behind it, which
// is the order retail's constructor writes: the base fields first, the vftable
// third, and the derived fields after.

// Two levers closed the last bytes. The derived fields have to be written from
// an initializer list rather than from the constructor body, including the
// name, which needs its own default constructor to qualify. Written in the
// body, MSVC leaves the vftable store third at the first of the two inlined
// constructors and sinks it past every other store at the second. The name
// store has to be an assignment operator rather than a set call, because retail
// computes the target address before it pushes the source.

// The override link is declared as a pointer to the derived class rather than
// to the base. Declared as a base pointer, the assignment on the map.ini path
// costs a null check and a 4-byte adjustment that retail does not have.

#include "Common/INIException.h"

struct FieldParse;

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set( const StringBase<T> &other );

private:
	StringBase( const T *text );
	void releaseBuffer();

	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}

	~AsciiString()
	{
		( (StringBase<char> *)this )->releaseBuffer();
	}

	const char *str() const
	{
		return m_data ? (const char *)( (const char *)m_data + 8 ) : (const char *)0x0107388B;
	}

	void setInto( void *target ) const
	{
		( (StringBase<char> *)target )->set( *(const StringBase<char> *)this );
	}
};

class BfmeNameField
{
public:
	BfmeNameField() : m_data( 0 ) {}

	BfmeNameField &operator=( const AsciiString &other )
	{
		( (StringBase<char> *)this )->set( *(const StringBase<char> *)&other );
		return *this;
	}

	void *m_data;
};

class Overridable
{
public:
	Overridable *friend_getFinalOverride();
};

class Rva0039C830
{
public:
	Rva0039C830 &operator=( const Rva0039C830 &that );
};

class LightPointLevel;

class BfmeOverridableBase
{
public:
	BfmeOverridableBase()
	{
		m_bfmeNextOverride = 0;
		m_bfmeIsOverride = 0;
	}

	LightPointLevel *m_bfmeNextOverride;
	unsigned char m_bfmeIsOverride;
	unsigned char m_bfmePad009[ 3 ];
};

class LightPointLevel : public BfmeOverridableBase
{
public:
	virtual void bfmeSlot00();

	LightPointLevel() : m_bfmeA( 0 ), m_bfmeB( 0 ), m_bfmeC( 0 ), m_bfmeD( 0 )
	{
	}

	BfmeNameField m_bfmeName;
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
};

class LightPointSystem
{
public:
	void addLevel( LightPointLevel *level );
	LightPointLevel *find( void *levels, AsciiString *name ) const;

	unsigned char m_bfmePad000[ 8 ];
	unsigned char m_bfmeLevels[ 12 ];
};

extern LightPointSystem *g_bfmeSinkBRB;

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );

	int getLoadType( void ) const { return m_bfmeLoadType; }

	static void parseLightPointLevel( INI *ini );

private:
	int m_bfmePad000;
	int m_bfmePad004;
	int m_bfmeLoadType;
};

void INI::parseLightPointLevel( INI *ini )
{
	if ( g_bfmeSinkBRB == 0 )
		return;

	AsciiString name( ini->getNextToken() );

	if ( ini->getLoadType() == 2 )
	{
		LightPointLevel *found =
			g_bfmeSinkBRB->find( &g_bfmeSinkBRB->m_bfmeLevels, &name );

		if ( found == 0 )
			throw INIException( 3, "Light point level %s not found in map.ini", name.str() );

		LightPointLevel *level = new LightPointLevel;

		LightPointLevel *base = found;
		if ( found->m_bfmeNextOverride != 0 )
			base = (LightPointLevel *)
				( (Overridable *)found->m_bfmeNextOverride )->friend_getFinalOverride();

		*(Rva0039C830 *)level = *(const Rva0039C830 *)base;
		base->m_bfmeNextOverride = level;
		level->m_bfmeIsOverride = 1;

		ini->initFromINI( level, (const FieldParse *)0x010EBE44 );
	}
	else
	{
		LightPointLevel *level = new LightPointLevel;

		level->m_bfmeName = name;

		ini->initFromINI( level, (const FieldParse *)0x010EBE44 );

		g_bfmeSinkBRB->addLevel( level );
	}
}
