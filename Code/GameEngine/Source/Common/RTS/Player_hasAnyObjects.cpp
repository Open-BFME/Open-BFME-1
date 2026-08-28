// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: Player::hasAnyObjects, retail 0x000CE0B0, 60 bytes.
//
// The reference's body with one BFME change: the question takes a flag, and
// the player just forwards it to each of its team prototypes. The prototype
// list is at this+0x288 and the loop reloads the list header each iteration
// for the end test, the call in between being enough to make it.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	Bool hasAnyObjects(Bool bfmeFlag);			// ILT 0x00021D96
};

typedef _STL::list<TeamPrototype *> PlayerTeamList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool hasAnyObjects(Bool bfmeFlag) const;

private:
	char m_slice_pad[0x288];				// retail this+0x00 .. +0x287, untouched
	PlayerTeamList m_playerTeamPrototypes;			// this+0x288
};

Bool Player::hasAnyObjects(Bool bfmeFlag) const
{
	for (PlayerTeamList::const_iterator it = m_playerTeamPrototypes.begin();
			 it != m_playerTeamPrototypes.end(); ++it)
	{
		if ((*it)->hasAnyObjects(bfmeFlag)) {
			return true;
		}
	}
	return false;
}
