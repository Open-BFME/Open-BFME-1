// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/stlp_nodealloc
// stlport
// Player::canBuild, retail 0x000D57B0, 303 bytes.
// Identity: the Zero Hour Player::canBuild twin (Common/RTS/Player.cpp) with
// allowedToBuild inlined (m_canBuildBase +0x295 / m_canBuildUnits +0x294 against
// KINDOF_STRUCTURE at ThingTemplate+0xc8), the getBuildable BSTATUS_NO /
// IGNORE_PREREQUISITES / ONLY_BY_AI + PLAYER_COMPUTER sequence and the
// ProductionPrerequisite::isSatisfied(this) loop over m_prereqInfo (+0x2c4, 0x24
// per element). BFME drops the canBuildMoreOfType tail and adds a walk of a
// std::list of template IDs at Player+0x64c: a template whose m_templateID
// (+0x478, ThingFactory::findByTemplateID) is on it cannot be built. The list's
// real name is unproven, so it keeps its offset.

#define BFME_STLP_NODE_ALLOC
#include <list>
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

enum BuildableStatus
{
	BSTATUS_YES,
	BSTATUS_IGNORE_PREREQUISITES,
	BSTATUS_NO,
	BSTATUS_ONLY_BY_AI
};

// reference/shims/bfmekindof/Common/KindOf.h: KINDOF_STRUCTURE is bit 7
enum KindOfType
{
	KINDOF_STRUCTURE = 7
};

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_COMPUTER
};

class Player;

class ProductionPrerequisite
{
public:
	bool isSatisfied(const Player *player) const;
private:
	char m_unmodelled[0x24];
};

class ThingTemplate
{
public:
	BuildableStatus getBuildable() const;
	Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }
	Int getPrereqCount() const { return m_prereqInfo.size(); }
	const ProductionPrerequisite *getNthPrereq(Int i) const { return &m_prereqInfo[i]; }
	UnsignedShort getTemplateID() const { return m_templateID; }
private:
	char m_before_kindof[0xc8];
	unsigned char m_kindof[8];		// +0xc8
	char m_before_prereqs[0x2c4 - 0xd0];
	std::vector<ProductionPrerequisite> m_prereqInfo;	// +0x2c4
	char m_before_id[0x478 - 0x2d0];
	UnsignedShort m_templateID;		// +0x478
};

class Player
{
public:
	Bool canBuild(const ThingTemplate *tmplate) const;
	Bool allowedToBuild(const ThingTemplate *tmplate) const;
	PlayerType getPlayerType() const { return m_playerType; }
private:
	char m_before_type[0x2c];
	PlayerType m_playerType;		// +0x2c
	char m_before_canBuild[0x294 - 0x30];
	Bool m_canBuildUnits;			// +0x294
	Bool m_canBuildBase;			// +0x295
	char m_before_list[0x64c - 0x296];
	std::list<UnsignedShort> m_templateIdList_64c;	// +0x64c
};

// ?allowedToBuild@Player@@QBE_NPBVThingTemplate@@@Z present-unmatched
inline Bool Player::allowedToBuild(const ThingTemplate *tmplate) const
{
	if (!m_canBuildBase && tmplate->isKindOf(KINDOF_STRUCTURE))
		return false;
	if (!m_canBuildUnits && !tmplate->isKindOf(KINDOF_STRUCTURE))
		return false;
	return true;
}

Bool Player::canBuild(const ThingTemplate *tmplate) const
{
	if (!tmplate)
		return false;

	if (!allowedToBuild(tmplate))
		return false;

	if (tmplate->getBuildable() == BSTATUS_NO)
		return false;

	if (tmplate->getBuildable() == BSTATUS_IGNORE_PREREQUISITES)
		return true;

	if (tmplate->getBuildable() == BSTATUS_ONLY_BY_AI && getPlayerType() != PLAYER_COMPUTER)
		return false;

	for (std::list<UnsignedShort>::const_iterator it = m_templateIdList_64c.begin(); it != m_templateIdList_64c.end(); ++it)
	{
		if (*it == tmplate->getTemplateID())
			return false;
	}

	Bool prereqsOK = true;
	for (Int i = 0; i < tmplate->getPrereqCount(); i++)
	{
		const ProductionPrerequisite *pre = tmplate->getNthPrereq(i);
		if (pre->isSatisfied(this) == false)
			prereqsOK = false;
	}

	if (!prereqsOK)
		return false;

	return true;
}
