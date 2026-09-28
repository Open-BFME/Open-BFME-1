// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: readable conversion of the predefined Eva-event field parser.
// The INI registry row at 0x012B5250 names PredefinedEvaEvent and points
// to this callback; its field-parse table is at 0x010F1B68.  The owner remains address-derived because the
// retail image does not expose a matched source-level method name.

#include "ascii_string.h"

typedef int Int;

struct FieldParse;

// The retail wrapper is a four-byte StringBase pointer.  Its constructor and
// release helper are already matched in string_base.cpp; keeping the wrapper
// local preserves the exact BFMERetailAsciiString ABI used by this callback.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const
	{
		return m_data ? m_data + 8 : "";
	}

private:
	void releaseBuffer();
	char *m_data;
};

class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *object, const FieldParse *fieldParse );

	Int getLoadType() const
	{
		return *(const Int *)((const char *)this + 8);
	}
};

class INIException
{
public:
	INIException( Int code, const char *message, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_message;
};

struct Rva004246F0Value
{
	AsciiString m_key;
	Int m_message;
};

struct Rva004246F0ExtractKey
{
	const AsciiString &operator()( const Rva004246F0Value &value ) const
	{
		return value.m_key;
	}
};

namespace rts
{
template <class T> struct hash;
}

namespace _STL
{
template <class T> struct equal_to;
template <class T> class allocator;

template <class V>
struct _Hashtable_node
{
	_Hashtable_node<V> *m_next;
	V m_val;
};

template <class V, class Key, class HashFcn, class ExtractKey, class EqualKey,
	class Alloc>
class hashtable
{
public:
	const _Hashtable_node<V> *find( const Key &key ) const
	{
		return _M_find( key );
	}

private:
	template <class KT>
	_Hashtable_node<V> *_M_find( const KT &key ) const;

	char m_unmodelled[0x14];
};
}

typedef _STL::hashtable<Rva004246F0Value, AsciiString, rts::hash<AsciiString>,
	Rva004246F0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva004246F0Value> > Rva00425C90NameMap;

class Rva004256E0CopyPart
{
private:
	char m_unmodelled[0x0c];
};

class Rva004256E0Record
{
public:
	Rva004256E0Record &operator=( const Rva004256E0Record &other );

private:
	Int m_a;
	Int m_b;
	Int m_c;
	Int m_d;
	Rva004256E0CopyPart m_part;
};

// Retail 0x004256E0 copies four scalars then assigns its existing tree via
// ILT 0x000083E1 -> 0x00424AC0; it is assignment, not construction.

struct Rva00425C90Vector
{
	Rva004256E0Record *m_begin;
	Rva004256E0Record *m_end;
	Rva004256E0Record *m_capacity;

	Rva004256E0Record &operator[]( Int index )
	{
		return m_begin[index];
	}
};

class Eva
{
private:
	char m_head[0x0c];

public:
	Rva00425C90Vector m_current;
	Rva00425C90Vector m_default;
	char m_sideSounds[0x14];
	Rva00425C90NameMap m_defaultNames;
};

extern Eva *TheEva;

class Rva00425C90PredefinedEvaEvent
{
public:
	static void parse( INI *ini );
};

void Rva00425C90PredefinedEvaEvent::parse( INI *ini )
{
	const char *token = ini->getNextToken();
	BFMERetailAsciiString name( token );
	const _STL::_Hashtable_node<Rva004246F0Value> *found =
		((Rva00425C90NameMap *)((char *)TheEva + 0x38))->find(
			*(const AsciiString *)&name );

	if ( found == 0 )
		throw INIException( 3, "'%s' is not a predefined Eva event name", name.str() );

	const Int index = found->m_val.m_message;
	if ( index < 0 || index >= 0x11 )
		throw INIException( 3, "'%s' is not a predefined Eva event name", name.str() );

	Rva004256E0Record *destination;
	if ( ini->getLoadType() == 2 )
	{
		if ( index == 0 )
			throw INIException( 3,
				"You cannot redefine the default Eva event in a map.ini" );
		destination = ((Rva00425C90Vector *)((char *)TheEva + 0x0c))->m_begin + index;
	}
	else
	{
		destination = ((Rva00425C90Vector *)((char *)TheEva + 0x18))->m_begin + index;
	}

	Rva004256E0Record &record = *destination;
	if ( index != 0 )
	{
		__assume( destination != 0 );
		const Rva004256E0Record *source = TheEva->m_default.m_begin;
		record = *source;
	}

	ini->initFromINI( &record, (const FieldParse *)0x010F1B68 );
}
