// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: the Eva message INI field parser, retail 0x00425B80, 214 bytes.
//
// Sixteen FieldParse rows across four tables point at this body. The object
// table at 0x010913E0 pairs EvaEventDieOwner with it at row 0x01091490, and the
// other three are at 0x010AF710, 0x010E96F0 and 0x010F2550. Every one of those
// field names names an Eva event. Zero Hour's Eva.cpp writes
// Eva::parseEvaMessageFromIni as four steps: read a token, turn the name into a
// message, throw when the message is invalid, and store it. This body runs the
// same four. The named five-byte entry at 0x00004B65 already holds that
// decorated name and jumps here, so the implementation keeps the shim name that
// targets/game/reverse/symbols.csv pins at this address.
//
// The body reads one token, answers the literal None with -1, and otherwise
// looks the token up in the hash table at TheEva plus 0x24. A hit takes the
// message from the node's second word. A miss throws INIException with the
// token in the message. The lookup is the landed STLport hashtable _M_find at
// 0x004246F0, whose value type the ledger already calls Rva004246F0Value.
#include "string_base.h"
#include "ascii_string.h"

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl _strcmpi( const char *left, const char *right );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *separators = 0 );	// retail 0x00850970
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException( Int code, const char *msg, ... );		// direct call to 0x00850600
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

struct Rva004246F0Value
{
	AsciiString m_key;
	Int m_message;
};

struct Rva004246F0ExtractKey
{
	const AsciiString &operator()( const Rva004246F0Value &entry ) const { return entry.m_key; }
};

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()( T value ) const;
};
}

namespace _STL
{
template <class T> struct equal_to {};
template <class T> class allocator {};

template <class V>
struct _Hashtable_node
{
	_Hashtable_node<V> *m_next;
	V m_val;
};

template <class V, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
class hashtable
{
public:
	const _Hashtable_node<V> *find( const Key &key ) const { return _M_find( key ); }

private:
	template <class KT>
	_Hashtable_node<V> *_M_find( const KT &key ) const;	// retail 0x004246F0
};
}

typedef _STL::hashtable<Rva004246F0Value, AsciiString, rts::hash<AsciiString>,
	Rva004246F0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva004246F0Value> > AsciiStringKeyedHash004246F0;

enum EvaMessage
{
	EVA_MESSAGE_INVALID = -1
};

class Eva
{
public:
	unsigned char m_unmodelled[ 0x24 ];
	AsciiStringKeyedHash004246F0 m_messageNames;
};

extern Eva *TheEva;

class EvaParseMessageFromIniShim
{
public:
	static void parse( INI *ini, void *instance, void *store, const void *userData );
};

void EvaParseMessageFromIniShim::parse( INI *ini, void *instance, void *store, const void *userData )
{
	const char *token = ini->getNextToken();

	if( _strcmpi( "None", token ) == 0 )
	{
		*(EvaMessage *)store = EVA_MESSAGE_INVALID;
		return;
	}

	EvaMessage message;
	{
		AsciiString name( token );
		const _STL::_Hashtable_node<Rva004246F0Value> *found = TheEva->m_messageNames.find( name );
		if( found == 0 )
			message = EVA_MESSAGE_INVALID;
		else
			message = (EvaMessage)found->m_val.m_message;
	}

	if( message == EVA_MESSAGE_INVALID )
		throw INIException( 3, "Expected a recognized Eva event name or 'None'; got '%s'", token );

	*(EvaMessage *)store = message;
}
