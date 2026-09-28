// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x000D42A0, 146 bytes: replace Player::m_sciences with a caller's
// science list, but only when that list is non-empty.
//
// Owner: the body sits in Player.cpp's run of code, between
// Player::removeTeamRelationship (0x000D4200) and
// Player::findNaturalCommandCenter (0x000D4400). Its one caller, 0x00367470,
// reaches it through ILT 0x0001E056 with ThePlayers->m_local (PlayerList+0x0C)
// in ECX, and the vector it rewrites is at +0x234, which the layout witness
// names Player::m_sciences. The growth path calls ILT 0x00023588, the
// vector<ScienceType>::_M_insert_overflow pin.
//
// The method's own name is not evidenced, so it keeps its address.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

enum ScienceType
{
	SCIENCE_INVALID = -1
};

typedef _STL::vector<ScienceType> ScienceVec;

class Player
{
public:
	void rva000D42A0ReplaceSciences(const ScienceVec &sciences);

private:
	char m_unknown000[0x234];
	ScienceVec m_sciences;		// +0x234
};

void Player::rva000D42A0ReplaceSciences(const ScienceVec &sciences)
{
	if (sciences.empty())
		return;

	m_sciences.clear();
	for (unsigned int i = 0; i < sciences.size(); ++i)
		m_sciences.push_back(sciences[i]);
}
