// cl: /DNDEBUG /MD
// ZH twin: Player::removeBattlePlanBonusesForObject
// KindOfMask default ctor is memset of the 0x18-byte / 192-bit mask; that
// inlines as xor ecx / lea edx [eax+disp] / six stores, which member stores
// fold away.

#include <cstring>
#include <stdlib.h>

class Object;

struct KindOfMaskType
{
	unsigned m_bits[6];
	KindOfMaskType() { memset(this, 0, sizeof(*this)); }
};

struct BattlePlanBonuses
{
	float m_armorScalar;
	int m_bombardment;
	int m_searchAndDestroy;
	int m_holdTheLine;
	float m_sightRangeScalar;
	KindOfMaskType m_validKindOf;
	KindOfMaskType m_invalidKindOf;
};

void localApplyBattlePlanBonusesToObject(Object *obj, void *bonus);

extern float g_01076C24;
extern float g_bfmeDefaultBU;

class Player
{
public:
	void removeBattlePlanBonusesForObject(Object *obj) const;

private:
	unsigned char m_pad[0x70];
	BattlePlanBonuses *m_battlePlanBonuses;
};

// ?removeBattlePlanBonusesForObject@Player@@QBEXPAVObject@@@Z
void Player::removeBattlePlanBonusesForObject(Object *obj) const
{
	BattlePlanBonuses *bonus = new BattlePlanBonuses;
	*bonus = *m_battlePlanBonuses;
	bonus->m_armorScalar = g_bfmeDefaultBU / __max(bonus->m_armorScalar, g_01076C24);
	bonus->m_sightRangeScalar = g_bfmeDefaultBU / __max(bonus->m_sightRangeScalar, g_01076C24);
	bonus->m_bombardment = -1000000;
	bonus->m_searchAndDestroy = -1000000;
	bonus->m_holdTheLine = -1000000;
	localApplyBattlePlanBonusesToObject(obj, bonus);
	delete bonus;
}
