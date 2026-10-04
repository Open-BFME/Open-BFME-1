enum DamageType
{
	BFME_DAMAGE_TYPE_8 = 8
};

enum DeathType
{
	BFME_DEATH_TYPE_0 = 0
};

#define OBJECT_TU_MEMBERS \
	void kill(DamageType damageType, DeathType deathType);
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

struct BfmeKillContext
{
	char m_bfmeFields[8];
	void *m_bfmeOwner;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class WeaponStore
{
};

extern WeaponStore *TheWeaponStore;

extern void j_00035e5e();

class Gen_0028CA70
{
public:
	void bfmeKill(void);

private:
	char m_bfmeFields[4];
	BfmeKillContext *m_bfmeContext;
	Object *m_bfmeObject;
	char m_bfme0C[0x18];
	bool m_bfmeFinished;
};

// ?bfmeKill@Gen_0028CA70@@QAEXXZ
void Gen_0028CA70::bfmeKill(void)
{
	Object *object = m_bfmeObject;
	typedef void (WeaponStore::*CreateFn)(void *, Object *, void *);
	union { void (*fn)(); CreateFn call; } create = { j_00035e5e };

	if ((object->m_status[0] & 4) == 0 &&
		(object->m_status[0] & 0x00080000) == 0)
	{
		(TheWeaponStore->*create.call)(
			m_bfmeContext->m_bfmeOwner, object, object->m_cachedPos);
	}

	object->kill(BFME_DAMAGE_TYPE_8, BFME_DEATH_TYPE_0);
	m_bfmeFinished = true;
}
