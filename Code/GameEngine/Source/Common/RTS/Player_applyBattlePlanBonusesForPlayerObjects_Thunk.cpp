// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ZH twin: Player::applyBattlePlanBonusesForPlayerObjects

#include <cstring>

typedef unsigned int UnsignedInt;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

class Object;

struct KindOfMaskType
{
	UnsignedInt m_bits[6];

	// std::bitset<192>::reset() is the authentic KindOfMaskType constructor
	// shape. MSVC inlines it as one xor, two lea instructions, and two groups
	// of six stores.
	__forceinline KindOfMaskType() { memset(this, 0, sizeof(*this)); }
};

class BattlePlanBonuses
{
public:
	float m_armorScalar;
	int m_bombardment;
	int m_searchAndDestroy;
	int m_holdTheLine;
	float m_sightRangeScalar;
	KindOfMaskType m_validKindOf;
	KindOfMaskType m_invalidKindOf;
};

void localApplyBattlePlanBonusesToObject(Object *object, void *bonuses);

class Player
{
public:
	unsigned char m_unreconstructed_00[0x70];
	BattlePlanBonuses *m_battlePlanBonuses;

	void applyBattlePlanBonusesForPlayerObjects(const BattlePlanBonuses *bonus);
	void iterateObjects(void (__cdecl *callback)(Object *, void *), void *userData) const;
};

// ?applyBattlePlanBonusesForPlayerObjects@Player@@QAEXPBVBattlePlanBonuses@@@Z
void Player::applyBattlePlanBonusesForPlayerObjects(const BattlePlanBonuses *bonus)
{
	if (!m_battlePlanBonuses)
	{
		m_battlePlanBonuses = new BattlePlanBonuses;
		*m_battlePlanBonuses = *bonus;
	}
	else
	{
		m_battlePlanBonuses->m_armorScalar *= bonus->m_armorScalar;
		m_battlePlanBonuses->m_sightRangeScalar *= bonus->m_sightRangeScalar;

		m_battlePlanBonuses->m_bombardment += bonus->m_bombardment;
		m_battlePlanBonuses->m_bombardment = MAX(0, m_battlePlanBonuses->m_bombardment);

		m_battlePlanBonuses->m_holdTheLine += bonus->m_holdTheLine;
		m_battlePlanBonuses->m_holdTheLine = MAX(0, m_battlePlanBonuses->m_holdTheLine);

		m_battlePlanBonuses->m_searchAndDestroy += bonus->m_searchAndDestroy;
		m_battlePlanBonuses->m_searchAndDestroy = MAX(0, m_battlePlanBonuses->m_searchAndDestroy);
	}

	iterateObjects(localApplyBattlePlanBonusesToObject, (void *)bonus);
}
