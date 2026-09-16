// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_outofline /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

#include "Common/AsciiString.h"
#include "Common/INIException.h"

extern "C" __declspec( dllimport ) int __cdecl stricmp( const char *, const char * );

typedef unsigned int UnsignedInt;

class INI
{
public:
	const char *getNextToken( const char *seps );
	const char *getNextTokenOrNull( const char *seps );
	__forceinline const char *getSepsColon() const
	{
		return *(const char **)((const char *)this + 0x41C);
	}
	AsciiString getNextAsciiString();
	static void parseDurationUnsignedInt( INI *, void *, void *, const void * );
	static void parseFXList( INI *, void *, void *, const void * );
};

class FXList;

struct TimeAndLocationInfo
{
	UnsignedInt delay;
	AsciiString boneName;
};

class BridgeBehaviorModuleData
{
public:
	static void parseFX( INI *, void *, void *, const void * );
};

namespace _STL
{

class __new_alloc
{
public:
static void *__cdecl allocate( unsigned int bytes );
};

template <class T1, class T2>
void __cdecl _Construct( T1 *destination, const T2 &value );

template <class T>
class allocator
{
};

struct _List_node_base
{
	_List_node_base *m_next;
	_List_node_base *m_previous;
};

template <class T>
struct _List_node : public _List_node_base
{
	T m_data;
};

template <class T>
struct _List_iterator
{
	_List_iterator( _List_node_base *node ) : m_node( node ) {}

	_List_node_base *m_node;
};

template <class T, class Allocator>
class list
{
public:
	typedef _List_node<T> Node;

	Node *m_node;

	__forceinline void push_back( const T &value )
	{
		_List_node_base *at = m_node;
		Node *node = (Node *)__new_alloc::allocate( sizeof( Node ) );
		_Construct( &node->m_data, value );

		_List_node_base *before = at->m_previous;
		node->m_next = at;
		node->m_previous = before;
		before->m_next = node;
		at->m_previous = node;
	}
};

}

struct Rva001F52F0Element
{
	FXList *fx;
	UnsignedInt delay;
	AsciiString boneName;

	~Rva001F52F0Element()
	{
		boneName.~AsciiString();
	}
};

struct BoneNameSlot
{
	AsciiString *destination;

	__forceinline BoneNameSlot( AsciiString *value ) : destination( value ) {}

	__forceinline void operator=( const AsciiString &value )
	{
		destination->operator=( value );
	}
};

static void parseTimeAndLocationInfo( INI *ini, void *instance, TimeAndLocationInfo *info )
{
	const char *token = ini->getNextToken( ini->getSepsColon() );
	if( stricmp( token, "Delay" ) != 0 )
		throw INIException( 3, "Expected 'Delay' token, found '%s'\n", token );
	ini->parseDurationUnsignedInt( ini, instance, &info->delay, 0 );
	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if( token != 0 )
	{
		if( stricmp( token, "Bone" ) != 0 )
			throw INIException( 3, "Expected 'Bone' token, found '%s'\n", token );
		BoneNameSlot( &info->boneName ) = ini->getNextAsciiString();
	}
}

// ?keepParseTimeAndLocationInfo absent-from-retail
static __declspec( noinline ) void keepParseTimeAndLocationInfo( INI *ini, void *instance, TimeAndLocationInfo *info )
{
	parseTimeAndLocationInfo( ini, instance, info );
}

void (* volatile keepParseTimeAndLocationInfoAnchor)( INI *, void *, TimeAndLocationInfo * ) =
	keepParseTimeAndLocationInfo;

// ?parseFX_unlanded absent-from-retail
#if 0
void BridgeBehaviorModuleData::parseFX_unlanded( INI *ini, void *instance, void *store, const void * )
{
	const char *token;
	Rva001F52F0Element item;
	item.fx = 0;
	_STL::list<Rva001F52F0Element, _STL::allocator<Rva001F52F0Element> > *bridgeFXList =
		(_STL::list<Rva001F52F0Element, _STL::allocator<Rva001F52F0Element> > *)store;

	const char *sepsColon = *(const char **)((const char *)ini + 0x41C);
	token = ini->getNextToken( sepsColon );
	if( stricmp( token, "FX" ) != 0 )
		throw INIException( 3, "Expected 'FX' token, found '%s'\n", token );

	FXList *fx;
	INI::parseFXList( ini, instance, &fx, 0 );
	item.fx = fx;
	parseTimeAndLocationInfo( ini, instance, (TimeAndLocationInfo *)( (char *)&item + 4 ) );
	bridgeFXList->push_back( item );
}
#endif
