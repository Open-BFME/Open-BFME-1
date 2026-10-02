// stlport
#include "Thing/GameLogicObjectLookup.h"
#include "../GameLogic/command_source_type.h"

struct Coord3D;

struct BfmeSetVK
{
	unsigned char m_bfmeRawVK[4];
};

// Retail ILTs 0x00044A44 and 0x000339FB reach the matched command bodies
// at 0x0025D170 and 0x0025D270 in the AICommandInterface command TUs.
class AICommandInterface
{
public:
	void aiBfmeCommand63(Object *object, CommandSourceType commandSource);
	void aiBfmeCommand40(const Coord3D *position, CommandSourceType commandSource);
};

class BfmeUnitVK
{
public:
	unsigned char m_bfmeHeadVK[0x20];
	AICommandInterface m_bfmeListVK;
};

class BfmeHolderVK
{
public:
	unsigned char m_bfmeHeadVK[0x204];
	BfmeUnitVK *m_bfmeUnitVK;
};

// ILT 0x0001F253 reaches GameLogic::findObjectByID at 0x0009A510.
extern GameLogic *TheGameLogic;

class BfmeOwnerVK
{
public:
	void bfmeApplyVK(void);

	unsigned char m_bfmeHeadVK[8];
	BfmeHolderVK *m_bfmeHolderVK;
	unsigned char m_bfmeGapVK[0xa0];
	void *m_bfmeKeyVK;
	BfmeSetVK m_bfmeSetVK;
};

void BfmeOwnerVK::bfmeApplyVK(void)
{
	BfmeUnitVK *unit = m_bfmeHolderVK->m_bfmeUnitVK;

	if (unit == 0)
		return;

	BfmeSetVK *set = &m_bfmeSetVK;
	Object *player = TheGameLogic->findObjectByID((int)m_bfmeKeyVK);

	if (player != 0)
		unit->m_bfmeListVK.aiBfmeCommand63(player, CMD_FROM_AI);
	else if (set != 0)
		unit->m_bfmeListVK.aiBfmeCommand40((const Coord3D *)set, CMD_FROM_AI);
}
