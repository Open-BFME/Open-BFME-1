// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?countObjectsByThingTemplate@Player@@QBEXHPBQBVThingTemplate@@_NPAH1@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// Open-BFME: Player::countObjectsByThingTemplate, retail 0x000CDD50, 84 bytes.
//
// The reference's body unchanged: zero the caller's counts, then hand all five
// arguments to every team prototype in turn.  The prototype list is at
// this+0x288, the same place Player_hasAnyObjects.cpp measured it, and the
// zeroing loop comes out as a rep stosd.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef bool Bool;

class ThingTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate* const* things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;	// ILT 0x0001424A
};

typedef _STL::list<TeamPrototype *> PlayerTeamList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate* const * things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;

private:
	char m_slice_pad[0x288];				// retail this+0x00 .. +0x287, untouched
	PlayerTeamList m_playerTeamPrototypes;			// this+0x288
};

void Player::countObjectsByThingTemplate(Int numTmplates, const ThingTemplate* const * things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction ) const
{
	Int i;

	for (i = 0; i < numTmplates; ++i)
		counts[i] = 0;

	for (PlayerTeamList::const_iterator it = m_playerTeamPrototypes.begin();
			 it != m_playerTeamPrototypes.end();
			 ++it)
	{
		(*it)->countObjectsByThingTemplate(numTmplates, things, ignoreDead, counts, ignoreUnderConstruction);
	}
}
