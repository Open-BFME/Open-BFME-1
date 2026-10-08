// Retail ILT 0x0003EEBE lands on 0x001CEA50, matched as Object::setWeaponLock.
class Object
{
public:
	void setWeaponLock(int weaponSlot, int lockType);
};

#include "../GameLogic/command_source_type.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiAttackObject(Object *object, int mode, CommandSourceType source);
};

class BfmeActiveState
{
public:
	char m_bfmeFields[0x204];
	struct BfmeAIHolder *m_bfmeAI;
};

struct BfmeAIHolder
{
	char m_bfmeFields[0x20];
	AICommandInterface m_bfmeCommands;
};

struct BfmeAttackForwardInfo
{
	char m_bfmeFields[8];
	int m_bfmeMode;
	int m_bfmeValue;
	void *m_bfmeFirst;
	void *m_bfmeSecond;
};

class ThingTemplate;

// ZH AssistedTargetingUpdate::assistAttack: lock the slot, attack the victim,
// then draw the two optional feedback lasers. ILT 0x00021EE5 lands on the
// matched private makeFeedbackLaser (0x0027FD70).
class AssistedTargetingUpdate
{
public:
	void assistAttack(const Object *requestingObject, Object *victimObject);

private:
	void makeFeedbackLaser(const ThingTemplate *laserTemplate, const Object *from, const Object *to);

	char m_bfmeFields[4];
	BfmeAttackForwardInfo *m_bfmeInfo;
	BfmeActiveState *m_bfmeState;
};

// ?assistAttack@AssistedTargetingUpdate@@QAEXPBVObject@@PAV2@@Z
void AssistedTargetingUpdate::assistAttack(const Object *requestingObject, Object *victimObject)
{
	BfmeActiveState *state = m_bfmeState;
	BfmeAttackForwardInfo *info = m_bfmeInfo;

	if (state->m_bfmeAI != 0) {
		((Object *)state)->setWeaponLock(info->m_bfmeValue, 1);
		state->m_bfmeAI->m_bfmeCommands.aiAttackObject(
			victimObject, info->m_bfmeMode, CMD_FROM_AI);

		if (info->m_bfmeFirst != 0)
			makeFeedbackLaser((const ThingTemplate *)info->m_bfmeFirst, requestingObject, (const Object *)state);

		if (info->m_bfmeSecond != 0)
			makeFeedbackLaser((const ThingTemplate *)info->m_bfmeSecond, (const Object *)state, victimObject);
	}
}
