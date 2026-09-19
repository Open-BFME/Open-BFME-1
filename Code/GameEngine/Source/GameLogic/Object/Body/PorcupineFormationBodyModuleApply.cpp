// cl: /DNDEBUG /MD /EHsc
//
// BFME's 142-byte PorcupineFormationBodyModule damage helper at retail
// 0x002144D0.  The named attemptDamage override immediately to the right of
// this body calls it through ILT 0x0002B35A with the primary module address.

typedef int ObjectID;
typedef float Real;

class DamageInfo
{
private:
	char m_pad[8];

public:
	ObjectID m_sourceID;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum KindOfType
{
	KINDOF_PORCUPINE_DAMAGE_EXCLUDED = 0x19
};

class Thing
{
private:
	void *m_vtable;

public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
private:
	char m_pad38[0x34];

public:
	Coord3D m_position;

private:
	char m_pad40[0x300];

public:
	unsigned char m_status;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class WeaponTemplate
{
public:
	Real getUnmodifiedAttackRange() const;
};

class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *weapon,
		const Object *source, Object *target);
};

class PorcupineFormationBodyModuleData
{
private:
	char m_pad[0x5c];

public:
	WeaponTemplate *m_weapon;
};

class PorcupineDamageHelper
{
private:
	void *m_vtable;
	PorcupineFormationBodyModuleData *m_moduleData;
	Object *m_object;

public:
	// Retail sets ECX to this module before calling the 67-byte predicate.
	// The predicate ignores ECX and reads only x/y from the two positions.
	unsigned char withinDistance00214350(Real distance,
		const Coord3D *a, const Coord3D *b);
	void apply(DamageInfo *damageInfo);
};

extern GameLogic *TheBfmeGameLogic;
extern WeaponStore *TheWeaponStore;

// ?apply@PorcupineDamageHelper@@QAEXPAVDamageInfo@@@Z
void PorcupineDamageHelper::apply(DamageInfo *damageInfo)
{
	Object *source = m_object;
	if (source != 0) {
		PorcupineFormationBodyModuleData *data = m_moduleData;
		if (data != 0) {
			WeaponTemplate *weapon = data->m_weapon;
			if (weapon != 0) {
				Object *target = TheBfmeGameLogic->findObjectByID(
					damageInfo->m_sourceID);
				if (target != 0 && (target->m_status & 1) == 0 &&
					!target->isKindOf(KINDOF_PORCUPINE_DAMAGE_EXCLUDED) &&
					this->withinDistance00214350(weapon->getUnmodifiedAttackRange(),
						&source->m_position, &target->m_position)) {
					TheWeaponStore
						->createAndFireTempWeapon(data->m_weapon, source, target);
				}
			}
		}
	}
}
