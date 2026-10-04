// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// W3DModelDrawModuleData::parseConditionState, retail 0x0077C860 (748 B).
//
// Identity: TheW3DModelDrawModuleDataFieldParse at 0x01124F90 (the table
// W3DModelDrawModuleData::buildFieldParse at 0x0077D380 adds) registers
// "DefaultModelConditionState" with userData 1 and "ModelConditionState" with
// userData 0, both through ILT 0x00045219 to this body.  The Zero Hour twin's
// PARSE_DEFAULT / PARSE_NORMAL values are 1 / 0 and its asset-error texts are
// the ones this body throws.  BFME drops the transition and alias modes (their
// table rows go to the parser at 0x0077D150) and keeps a single ten-word
// condition set per state instead of Zero Hour's vector of them.
//
// Layout the body proves:
//   W3DModelDrawModuleData+0x18  vector of 0x128-byte ModelConditionInfo
//                                (Zero Hour m_conditionStates: indexed by the
//                                default state, searched by doesStateExist,
//                                appended to at the end)
//   W3DModelDrawModuleData+0x4C  Int, Zero Hour m_defaultState at the same offset
//   ModelConditionInfo+0x00      ten-word condition set
//   ModelConditionInfo+0x28      vector<AsciiString> the "Model" field parser
//                                0x00773170 fills (ModelConditionInfo_parseModel.cpp)
//
// doesStateExist (0x00765B20) takes its arguments in EAX/EBX, the custom
// convention MSVC gives a TU-static callee, so this TU carries its own static
// copy under the ledger's decorated name (docs/shape_levers.md "Compiler-private
// ABI: compile the static helper with its caller"); the copy compiles to the
// same 64 bytes as the matched helper in W3DModelDraw.cpp.  The vector<ModelConditionInfo> in that
// name spells the element as a struct while operator= at 0x00772870 spells the
// class as a class: the forward declaration fixes the template argument's key
// before the definition fixes the class's.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct FieldParse;
class GenItem;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );
	~INIException();

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	const char *getNextTokenOrNull( const char *separators );
	void initFromINI( void *what, const FieldParse *parseTable );
};

#include "ascii_string.h"

namespace _STL
{
template <class T>
class allocator;

template <class T, class Allocator = allocator<T> >
class vector
{
public:
	void push_back( const T *value );
	T *erase( T *first, T *last );
	void clear( void ) { erase( m_start, m_finish ); }
	T *begin( void ) const { return m_start; }
	bool empty( void ) const { return m_start == m_finish; }
	UnsignedInt size( void ) const { return UnsignedInt( m_finish - m_start ); }
	T &operator[]( UnsignedInt i ) { return m_start[ i ]; }

	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
}

struct ModelConditionInfo;
template <int N>
class BitFlags;

typedef _STL::vector<ModelConditionInfo> ModelConditionVector;
typedef BitFlags<117> ModelConditionFlags;

static Bool doesStateExist( const ModelConditionVector &v, const ModelConditionFlags &f );

// address-derived: the condition-token parser at 0x00208810 (ILT 0x000140D8)
struct Gen000140D8
{
	UnsignedInt m_words[ 10 ];

	bool handle( GenItem *item, bool *first, bool *second );

	bool operator==( const Gen000140D8 &that ) const
	{
		for ( UnsignedInt i = 0; i < 10; ++i )
		{
			if ( m_words[ i ] != that.m_words[ i ] )
				return false;
		}
		return true;
	}

	bool any( void ) const
	{
		for ( UnsignedInt i = 0; i < 10; ++i )
		{
			if ( m_words[ i ] != 0 )
				return true;
		}
		return false;
	}
};

class ModelConditionInfo
{
public:
	ModelConditionInfo();
	~ModelConditionInfo();
	ModelConditionInfo &operator=( const ModelConditionInfo &other );

	Gen000140D8 m_conditions;
	_STL::vector<AsciiString> m_modelNames;
	char m_unknown34[ 0x128 - 0x34 ];
};

// the element name the matched push_back at 0x0077C670 carries
struct Rva0077C670Element;

class W3DModelDrawModuleData
{
private:
	static void parseConditionState( INI *ini, void *instance, void *store, const void *userData );

public:
	char m_unknown00[ 0x18 ];
	ModelConditionVector m_conditionStates;
	char m_unknown24[ 0x4C - 0x24 ];
	Int m_defaultState;
};

extern const FieldParse Rva00D24718ModelConditionInfoFieldParse[];	// VA 0x01124718: Model Skeleton WeaponFireFXBone ...

static Bool doesStateExist( const ModelConditionVector &v, const ModelConditionFlags &f )
{
	const Gen000140D8 &flags = reinterpret_cast<const Gen000140D8 &>( f );
	for ( const ModelConditionInfo *it = v.m_start; it != v.m_finish; ++it )
	{
		if ( flags == it->m_conditions )
			return true;
	}
	return false;
}

// ?parseConditionState@W3DModelDrawModuleData@@CAXPAVINI@@PAX1PBX@Z
void W3DModelDrawModuleData::parseConditionState( INI *ini, void *instance, void * /*store*/, const void *userData )
{
	ModelConditionInfo info;
	W3DModelDrawModuleData *self = (W3DModelDrawModuleData *)instance;
	Gen000140D8 conditionsYes = { };

	switch ( (UnsignedInt)userData )
	{
		case 1:
		{
			if ( self->m_defaultState >= 0 )
				throw INIException( 3, "*** ASSET ERROR: you may have only one default state!" );
			if ( ini->getNextTokenOrNull( 0 ) )
				throw INIException( 3, "*** ASSET ERROR: unknown keyword" );
			if ( !self->m_conditionStates.empty() )
				throw INIException( 3, "*** ASSET ERROR: when using DefaultConditionState, it must be the first state listed (%s)\n", "" );
			self->m_defaultState = self->m_conditionStates.size();
		}
		break;

		case 0:
		{
			// begin()[i], not operator[]: the subscript form loads the vector's
			// start into EDX where retail uses ECX.
			if ( self->m_defaultState >= 0 )
				info = self->m_conditionStates.begin()[ self->m_defaultState ];

			bool first = false;
			bool second = false;
			const char *token = ini->getNextTokenOrNull( 0 );
			while ( token != 0 )
			{
				if ( !conditionsYes.handle( reinterpret_cast<GenItem *>( const_cast<char *>( token ) ), &first, &second ) )
					break;
				token = ini->getNextTokenOrNull( 0 );
			}

			if ( self->m_defaultState < 0 && self->m_conditionStates.empty() && conditionsYes.any() )
				throw INIException( 3, "*** ASSET ERROR: when not using DefaultConditionState, the first ConditionState must be for NONE (%s)", "" );

			if ( !conditionsYes.any() && self->m_defaultState >= 0 )
				throw INIException( 3, "*** ASSET ERROR: you may not specify both a Default state and a Conditions=None state" );

			if ( doesStateExist( self->m_conditionStates, reinterpret_cast<const ModelConditionFlags &>( conditionsYes ) ) )
				throw INIException( 3, "*** ASSET ERROR: duplicate condition states are not currently allowed (%s)", "" );
		}
		break;
	}

	ini->initFromINI( &info, Rva00D24718ModelConditionInfoFieldParse );

	if ( info.m_modelNames.size() == 0 )
		throw INIException( 3, "*** ASSET ERROR: you must specify a model name" );
	else if ( info.m_modelNames[ 0 ].isNone() )
		info.m_modelNames.clear();

	info.m_conditions = conditionsYes;
	reinterpret_cast<_STL::vector<Rva0077C670Element> &>( self->m_conditionStates ).push_back(
		reinterpret_cast<const Rva0077C670Element *>( &info ) );
}
