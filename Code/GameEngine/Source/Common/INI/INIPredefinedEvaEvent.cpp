// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception

// The INI block registry pairs the block name 'PredefinedEvaEvent' with this
// body.  BFME keeps that registry as a linked list of 12-byte rows whose head
// is the global at VA 0x0130CE50, and the row at 0x012B5250 holds the name
// string and this address.
//
// The block names one of the seventeen Eva events the engine ships with.  The
// body reads that name, looks it up in the hashtable at +0x38 of the Eva
// singleton, and rejects a name the table does not hold.  It rejects an index
// outside the seventeen slots the same way, because the stored index is the
// array subscript and nothing else bounds it.
//
// A map.ini may override an event but may not redefine event zero, which is the
// default every other event copies from.  So a map.ini load writes into the
// override array at +0x0C and a normal load writes into the main array at
// +0x18.  Either way the body copies event zero over the slot first and then
// fills the slot from the FieldParse table at 0x010F1B68, whose four fields all
// parse as unsigned integers.
//
// Zero Hour declares this parser as INI::parseEvaEvent, and the sibling block
// MiscEvaData is already named INI::parseMiscEvaData, so the name follows that
// pattern.  The hashtable lookup is the converted _M_find at 0x004246F0 and the
// copy is the converted 28-byte memberwise copy at 0x004256E0.  Both are
// reached here through declarations the linker aliases onto their ledger names.
//
// Naming the copy source through a local pointer is what fixed the last six
// bytes.  Reading eva->m_bfmeEvents straight into the argument left the address
// in EDX, and retail puts it in ECX.

#include "Common/INIException.h"

struct FieldParse;

template <typename T>
class StringBase
{
	friend class AsciiString;

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
};

class Rva004246F0Node
{
public:
	Rva004246F0Node *m_bfmeNext;
	AsciiString m_bfmeKey;
	int m_bfmeValue;
};

class Rva004246F0Table
{
public:
	Rva004246F0Node *find( const AsciiString &key ) const;
};

class Gen_004256E0
{
public:
	Gen_004256E0( const Gen_004256E0 &that );

	unsigned char m_bfmeBody[ 0x1C ];
};

class BfmeGlobal_012f142c
{
public:
	unsigned char m_bfmePad000[ 0x0C ];
	Gen_004256E0 *m_bfmeOverrides;
	unsigned char m_bfmePad010[ 0x18 - 0x10 ];
	Gen_004256E0 *m_bfmeEvents;
	unsigned char m_bfmePad01C[ 0x38 - 0x1C ];
	Rva004246F0Table m_bfmeNames;
};

extern BfmeGlobal_012f142c *TheBfmeGlobal_012f142c;

inline void *operator new( unsigned int, void *where ) { return where; }

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *what, const FieldParse *parseTable );

	int getLoadType( void ) const { return m_bfmeLoadType; }

	static void parsePredefinedEvaEvent( INI *ini );

private:
	int m_bfmePad000;
	int m_bfmePad004;
	int m_bfmeLoadType;
};

void INI::parsePredefinedEvaEvent( INI *ini )
{
	AsciiString name( ini->getNextToken() );

	const Rva004246F0Table *names = &TheBfmeGlobal_012f142c->m_bfmeNames;
	Rva004246F0Node *node = names->find( name );
	if ( node == 0 )
		throw INIException( 3, "'%s' is not a predefined Eva event name", name.str() );

	int index = node->m_bfmeValue;
	if ( index < 0 || index >= 17 )
		throw INIException( 3, "'%s' is not a predefined Eva event name", name.str() );

	BfmeGlobal_012f142c *eva;
	Gen_004256E0 *target;
	if ( ini->getLoadType() == 2 )
	{
		if ( index == 0 )
			throw INIException( 3, "You cannot redefine the default Eva event in a map.ini" );

		eva = TheBfmeGlobal_012f142c;
		target = eva->m_bfmeOverrides + index;
	}
	else
	{
		eva = TheBfmeGlobal_012f142c;
		target = eva->m_bfmeEvents + index;
	}

	if ( index != 0 )
	{
		__assume( target != 0 );
		Gen_004256E0 *defaults = eva->m_bfmeEvents;
		new ( target ) Gen_004256E0( *defaults );
	}

	ini->initFromINI( target, (const FieldParse *)0x010F1B68 );
}
