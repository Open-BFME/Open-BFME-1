// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: Player::hasAnyBuildings, retail 0x000CDF70, 118 bytes.
//
// The reference's mask-taking overload with the same extra flag its
// hasAnyObjects sibling carries, forwarded to each team prototype along with
// the mask.
//
// The mask is BitFlags<192> -- six dwords, which the `ret 0x1C` accounts for
// together with the flag -- and it is passed by value, so most of the body is
// the copy the compiler builds in the outgoing argument slots on every
// iteration. The prototype list is at this+0x288, as in the sibling.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <int NUMBITS> class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	Bool hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag);	// ILT 0x0000B55F
};

typedef _STL::list<TeamPrototype *> PlayerTeamList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag) const;

private:
	char m_slice_pad[0x288];				// retail this+0x00 .. +0x287, untouched
	PlayerTeamList m_playerTeamPrototypes;			// this+0x288
};

Bool Player::hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag) const
{
	for (PlayerTeamList::const_iterator it = m_playerTeamPrototypes.begin();
			 it != m_playerTeamPrototypes.end(); ++it)
	{
		if ((*it)->hasAnyBuildings(kindOf, bfmeFlag)) {
			return true;
		}
	}
	return false;
}
