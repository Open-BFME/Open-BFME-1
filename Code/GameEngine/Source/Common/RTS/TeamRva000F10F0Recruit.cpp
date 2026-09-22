// Retail 000F1030 (150B) and 000F10F0 (356B).
// The static helper is the released Team.cpp isInBuildVariations: it compares
// ThingTemplate::m_buildVariations (+2D0) with the candidate name (+20).
// Compiling it with the real caller lets MSVC select the witnessed private ABI
// (first template in ECX, second on the caller stack, plain RET).
// The BFME-specific five-argument Team helper factors the recruitment test out
// of the released tryToRecruit loop. Its exact method name is not established,
// so it retains its RVA rather than borrowing the outer method's name.
// Calls: getFinalOverride via ILT000022BB ->00087A80;
// Object::getControllingPlayer via ILT00020824 ->001BE3F0;
// ThingTemplate::isEquivalentTo via ILT0003E80B ->0013FE10.
// Native recursive OVERRIDE access is essential: a cached manual chain loses
// the two context-dependent register lifetimes. The null-first team-owner
// accessor reproduces the retail branch and preserves its null behavior.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1

#include "ascii_string.h"
#include <vector>

typedef bool Bool;

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const
	{
		return m_name;
	}

	const std::vector<AsciiString> &getBuildVariations() const
	{
		return m_buildVariations;
	}

	Bool isEquivalentTo(const ThingTemplate *) const;

private:
	unsigned char m_unmodelled_00c[0x20 - 0x0c];
	AsciiString m_name;
	unsigned char m_unmodelled_024[0x2d0 - 0x24];
	std::vector<AsciiString> m_buildVariations;
};

template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}

private:
	const T *m_overridable;
};

static Bool isInBuildVariations(const ThingTemplate *ttWithVariations,
	const ThingTemplate *b)
{
	const std::vector<AsciiString> &bv = ttWithVariations->getBuildVariations();
	if (bv.empty())
		return false;

	for (std::vector<AsciiString>::const_iterator it = bv.begin();
		it != bv.end(); ++it)
	{
		if (b->getName().compare(*it) == 0)
			return true;
	}
	return false;
}

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Player;
class Team;

class TeamPrototype
{
public:
	unsigned char m_unknown_000[8];
	Player *m_owningPlayer;
	unsigned char m_unknown_00c[0x1bc - 0x0c];
	Bool m_isAIRecruitable;
	unsigned char m_unknown_1bd[0x1c8 - 0x1bd];
	int m_productionPriority;
};

class Player
{
public:
	unsigned char m_unknown_000[0x230];
	Team *m_defaultTeam;
};

class AIUpdateInterface
{
public:
	unsigned char m_unknown_000[0x32c];
	Bool m_recruitable;
};

class Object
{
public:
	unsigned char m_unknown_000[4];
	OVERRIDE<ThingTemplate> m_template;
	unsigned char m_unknown_008[0x38 - 0x08];
	float m_x;
	float m_y;
	unsigned char m_unknown_040[0x1a4 - 0x40];
	unsigned char m_disabledBits;
	unsigned char m_unknown_1a5[0x204 - 0x1a5];
	AIUpdateInterface *m_aiUpdateInterface;
	unsigned char m_unknown_208[0x23c - 0x208];
	Team *m_team;

	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}

	Player *getControllingPlayer() const;
};

class Team
{
public:
	unsigned char m_unknown_000[4];
	TeamPrototype *m_prototype;
	unsigned char m_unknown_008[0x31 - 0x08];
	Bool m_active;
	unsigned char m_unknown_032[0xe4 - 0x32];
	Bool m_isRecruitabilitySet;
	Bool m_isRecruitable;

	Bool Rva000F10F0(Object **recruit, float *distanceSquared,
		Object *candidate, ThingTemplate *desired, Coord3D *teamHome);

	Player *getControllingPlayer() const
	{
		if (m_prototype == 0)
			return 0;
		return m_prototype->m_owningPlayer;
	}
};

Bool Team::Rva000F10F0(Object **recruit, float *distanceSquared,
	Object *candidate, ThingTemplate *desired, Coord3D *teamHome)
{
	Player *myPlayer = getControllingPlayer();

	if (!candidate->getTemplate()->isEquivalentTo(desired))
	{
		if (!isInBuildVariations(desired, candidate->getTemplate()))
			return false;
	}

	if (candidate->getControllingPlayer() != myPlayer)
		return false;

	Team *candidateTeam = candidate->m_team;
	Bool isDefaultTeam = false;
	if (candidateTeam == myPlayer->m_defaultTeam)
		isDefaultTeam = true;
	if (!candidateTeam->m_active)
		return false;

	TeamPrototype *candidatePrototype = candidateTeam->m_prototype;
	if (candidatePrototype->m_productionPriority >=
		m_prototype->m_productionPriority)
		return false;

	Bool teamIsRecruitable = isDefaultTeam;
	if (candidatePrototype->m_isAIRecruitable)
		teamIsRecruitable = true;
	if (candidateTeam->m_isRecruitabilitySet)
		teamIsRecruitable = candidateTeam->m_isRecruitable;
	if (!teamIsRecruitable)
		return false;

	if (candidate->m_aiUpdateInterface != 0 &&
		!candidate->m_aiUpdateInterface->m_recruitable)
		return false;
	if ((candidate->m_disabledBits & 8) != 0)
		return false;

	float dx = teamHome->x - candidate->m_x;
	float dy = teamHome->y - candidate->m_y;
	if (isDefaultTeam && *recruit == 0)
	{
		*distanceSquared = dx * dx + dy * dy;
		*recruit = candidate;
		return true;
	}
	if (dx * dx + dy * dy > *distanceSquared)
		return false;
	*distanceSquared = dx * dx + dy * dy;
	*recruit = candidate;
	return true;
}
