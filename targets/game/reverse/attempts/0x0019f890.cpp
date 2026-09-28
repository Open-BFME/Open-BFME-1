// ?fillHelper@Rva001A0320Owner@@AAEXHPAVRva0019A7D0Vector@@PAXPAVRva00197AE0Temporary@@PAVScriptList@@PAVRva0019A1D0Owner@@@Z
// partial score=0.992 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x0019F890, 900 bytes, ret 0x18: the recursive helper that the
// matched Rva001A0320Owner::fill (0x0019FD00, Rva0019FD00Fill.cpp) calls
// twice through ILT 0x00008634, and that calls itself through the same thunk.
// The owner keeps the address-derived name the matched caller already uses.
//
// What the body proves (all from matched callees and witnessed layouts):
// - the receiver has the SidesList side table (count +0x28, 0x18-byte side
//   entries at +0x2C; CachedSidesLoader0019EC80.cpp), and the helper reads
//   side[index]'s Dict name through GenKey0012A7918, the key that
//   SidesList::findSideInfo (SidesListFindSideInfo.cpp) compares names with;
// - argument 2 is the CachedSidesLoader0019EC80 whose load() (0x0019EC80)
//   returns the SidesList parsed from a library map file;
// - argument 3 is a side entry's +0xC AsciiString vector, which that loader
//   fills from the "LibraryMapLists" chunk; it is walked from the back;
// - argument 4 is fill's case-insensitive set<AsciiString> of visited maps
//   (_M_find 0x00195EC0, insert_unique 0x00197270);
// - argument 5 receives a copy of library side 1's ScriptList (ctor
//   0x0035E3B0, ~ScriptList 0x0035BC20) through 0x0035E510 and 0x00357800;
// - argument 6 is the Rva0019BE80TeamRec that append() (0x0019BA40) extends
//   with a copy of each library team Dict whose teamOwner is set and whose
//   teamName is not "team"+owner, re-owned to this side's name and tagged
//   with TheKey_teamLibraryMapName (0x012A7770, SidesListWriteTeams.cpp).
// The declared parameter types are those of the pinned mangled name.
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include "Common/Dict.h"
#include "Common/NameKeyGenerator.h"
#include <vector>
#include <set>

extern const StaticNameKey TheKey_teamOwner;
extern const StaticNameKey TheKey_teamName;
extern const StaticNameKey TheKey_teamLibraryMapName;

class GenKey : public StaticNameKey
{
};

extern GenKey GenKey0012A7918;

struct BfmeStringNoCaseLess
{
	bool operator()( const AsciiString &left, const AsciiString &right ) const;
};

typedef _STL::set<AsciiString, BfmeStringNoCaseLess> VisitedMaps0019F890;

class ScriptList;

class SidesList;

// Retail inlines the empty test on the 8-byte StringBase header.
template <>
inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}

class CachedSidesLoader0019EC80
{
public:
	SidesList *load( const AsciiString &name );
};

struct Gen_t_0019a890_p16cd
{
	short next;
	short previous;
	short reserved;
	short free;
	int generation;
	Dict dict;
};

class Rva0019BE80TeamRec
{
public:
	int append( const Dict *dict );

	char m_prefix[0xc];
	_STL::vector<Gen_t_0019a890_p16cd> m_teams;
	short m_numActive;
	short m_freeHead;
};

struct SideEntry0019F890
{
	void *m_buildList;
	Dict m_dict;
	ScriptList *m_scripts;
	_STL::vector<AsciiString> m_libraries;
};

class SidesList
{
public:
	SideEntry0019F890 *getSideInfo( int side )
	{
		if ( side >= 0 && side < m_numSides )
			return &m_sides[side];
		return 0;
	}

	char m_prefix[0x28];
	int m_numSides;
	SideEntry0019F890 m_sides[32];
	char m_gap32c[0x63c - 0x32c];
	Gen_t_0019a890_p16cd *m_teams;
};

namespace Rva0035E510
{
class BfmeNodeEAT
{
public:
	void bfmeSwapEAT( BfmeNodeEAT *other );
};
}

class Rva00357800Owner
{
public:
	void swap( Rva00357800Owner *other );
};

class Host0035E450;

class ScriptList
{
public:
	ScriptList( Host0035E450 *source );
	~ScriptList();

	char m_body[0x4c];
};

#pragma comment(linker, "/alternatename:??0ScriptList@@QAE@PAVHost0035E450@@@Z=??0Gen0035E3B0@@QAE@PAVHost0035E450@@@Z")

class Rva0019A7D0Vector;
class Rva00197AE0Temporary;
class Rva0019A1D0Owner;

class Rva001A0320Owner
{
public:
	SideEntry0019F890 *getSideInfo( int side )
	{
		if ( side >= 0 && side < m_numSides )
			return &m_sides[side];
		return 0;
	}

private:
	char m_prefix[0x28];
	int m_numSides;
	SideEntry0019F890 m_sides[32];

	void fillHelper( int index, Rva0019A7D0Vector *out, void *entry,
		Rva00197AE0Temporary *temporary, ScriptList *scripts,
		Rva0019A1D0Owner *tree );
};

void Rva001A0320Owner::fillHelper( int index, Rva0019A7D0Vector *out, void *entry,
	Rva00197AE0Temporary *temporary, ScriptList *scripts,
	Rva0019A1D0Owner *tree )
{
	SideEntry0019F890 *side = getSideInfo( index );
	_STL::vector<AsciiString> *libraries = (_STL::vector<AsciiString> *)entry;
	VisitedMaps0019F890 *visited = (VisitedMaps0019F890 *)temporary;
	_STL::vector<AsciiString>::reverse_iterator last = libraries->rend();
	for ( _STL::vector<AsciiString>::reverse_iterator it = libraries->rbegin(); it != last; ++it )
	{
		AsciiString mapName( *it );
		if ( visited->find( mapName ) != visited->end() )
			continue;
		visited->insert( mapName );
		SidesList *library = ( (CachedSidesLoader0019EC80 *)out )->load( mapName );
		if ( library == 0 )
			continue;
		SideEntry0019F890 *librarySide = library->getSideInfo( 1 );
		fillHelper( index, out, &librarySide->m_libraries, temporary, scripts, tree );
		if ( librarySide->m_scripts )
		{
			ScriptList copy( (Host0035E450 *)librarySide->m_scripts );
			( (Rva0035E510::BfmeNodeEAT *)&copy )->bfmeSwapEAT( (Rva0035E510::BfmeNodeEAT *)scripts );
			( (Rva00357800Owner *)scripts )->swap( (Rva00357800Owner *)&copy );
		}
		AsciiString sideName = side->m_dict.getAsciiString( GenKey0012A7918.key() );
		register int team = library->m_teams[0].next;
		register Gen_t_0019a890_p16cd *teams = library->m_teams;
		for ( ; team != 0; teams = library->m_teams, team = teams[team].next )
		{
			Gen_t_0019a890_p16cd &slot = teams[team];
			Dict *teamDict = &slot.dict;
			AsciiString owner = teamDict->getAsciiString( TheKey_teamOwner.key() );
			if ( owner.isEmpty() )
				continue;
			bool isDefaultTeam = teamDict->getAsciiString( TheKey_teamName.key() ).compare( AsciiString( "team" ) + owner ) == 0;
			if ( !isDefaultTeam )
			{
				Dict dict( *teamDict );
				dict.setAsciiString( TheKey_teamOwner.key(), sideName );
				dict.setAsciiString( TheKey_teamLibraryMapName.key(), mapName );
				( (Rva0019BE80TeamRec *)tree )->append( &dict );
			}
		}
	}
}
