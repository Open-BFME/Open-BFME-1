// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX-
// AimWeaponBehavior update through its secondary UpdateModuleInterface.
// Evidence: targets/game/reverse/identity_evidence/001ed230-aim-update.md

#include <math.h>

typedef int Int;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Drawable
{
	friend class AimWeaponBehavior;
private:
	void applyPendingModelConditionFlags(Bool immediate);
};

class WeaponTemplate
{
public:
	char m_pad[0x51E];
	unsigned char m_useAimConditions;
};

class Weapon
{
public:
	unsigned char m_pad00[4];
	WeaponTemplate *m_template;
};

class Object;

class AIUpdateInterface
{
public:
#define BFME_SLOT(n) virtual Int bfmeSlot##n() = 0
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27);
	BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35);
	BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43);
	BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47);
	BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50); BFME_SLOT(51);
	BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54); BFME_SLOT(55);
	BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63);
	BFME_SLOT(64); BFME_SLOT(65); BFME_SLOT(66); BFME_SLOT(67);
	BFME_SLOT(68); BFME_SLOT(69); BFME_SLOT(70); BFME_SLOT(71);
	BFME_SLOT(72); BFME_SLOT(73); BFME_SLOT(74); BFME_SLOT(75);
	BFME_SLOT(76); BFME_SLOT(77); BFME_SLOT(78); BFME_SLOT(79);
	BFME_SLOT(80); BFME_SLOT(81); BFME_SLOT(82); BFME_SLOT(83);
	BFME_SLOT(84); BFME_SLOT(85); BFME_SLOT(86); BFME_SLOT(87);
	BFME_SLOT(88); BFME_SLOT(89); BFME_SLOT(90); BFME_SLOT(91);
	BFME_SLOT(92); BFME_SLOT(93); BFME_SLOT(94); BFME_SLOT(95);
#undef BFME_SLOT
	virtual Bool isIdle() const = 0;
	virtual Bool isAttacking() const = 0;
	Bool bfmeBlocksFormationRefresh();
};

class Rva00170C70BitSet
{
public:
	Rva00170C70BitSet(void *unused, unsigned index);
	unsigned m_words[10];
};

class BfmeE1166
{
public:
	BfmeE1166(int tag, unsigned a02, unsigned a03, unsigned a04, unsigned a05, unsigned a06);
	unsigned m_bfme00[10];
};

extern const float g_bfmeK1254;

template <int N> class BitFlags
{
public:
	// ?test@?$BitFlags@$0BEA@@@QBEII@Z absent-from-retail
	unsigned test(unsigned bit) const { return m_words[bit >> 5] & (1u << (bit & 31)); }
	// ?set@?$BitFlags@$0BEA@@@QAEXI@Z absent-from-retail
	void set(unsigned bit) { m_words[bit >> 5] |= (1u << (bit & 31)); }
	unsigned m_words[(N + 31) / 32];
};
typedef BitFlags<320> ModelConditionFlags;
#define BFME_HAVE_MODELCONDITIONFLAGS 1
#define BFME_HAVE_COORD3D 1
#define OBJECT_TU_MEMBERS \
    Weapon *getCurrentWeapon(WeaponSlotType *); \
    void notifyModelConditionChanged(); \
    void clearAndSetModelConditionFlags(const BitFlags<320> &, const BitFlags<320> &); \
    void clearModelConditionFlags(const BitFlags<304> &);
#include "../object.h"

// ?setAimCondition@@YAXPAVObject@@I@Z absent-from-retail
static __forceinline void setAimCondition(Object *obj, unsigned mask)
{
	if (!obj->m_modelConditionFlags.test(mask))
	{
		obj->m_modelConditionFlags.set(mask);
		obj->notifyModelConditionChanged();
	}
}

class AimWeaponBehaviorModuleData
{
public:
	virtual ~AimWeaponBehaviorModuleData();
	int m_gap4;
	float m_pitchLow;
	float m_pitchHigh;
	float m_rangeMin;
	float m_rangeMax;
};

class Module
{
public:
	virtual ~Module();
	AimWeaponBehaviorModuleData *m_moduleData;
};
class ObjectModule : public Module
{
public:
	Object *m_object;
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot() = 0;
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	virtual BitFlags<13> getDisabledTypesToProcess() const = 0;
};
class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_pad;
};
class AimWeaponBehavior : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	bool m_aiming;
};

// ?update@AimWeaponBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime AimWeaponBehavior::update()
{
	Object *obj = m_object;
	AIUpdateInterface *ai = obj->m_ai;
	Drawable *drawStash[1];
	drawStash[0] = obj->getDrawable();
	if (ai && drawStash[0])
	{
		Weapon *weapon = obj->getCurrentWeapon(0);
		if (weapon && weapon->m_template->m_useAimConditions
			&& ai->isAttacking() && !ai->bfmeBlocksFormationRefresh() && !ai->isIdle())
		{
			Coord3D m_aimPos;
			m_aimPos.x = reinterpret_cast<const Coord3D *>(obj->m_unmodelled2A4 + 4)->x;
			m_aimPos.y = reinterpret_cast<const Coord3D *>(obj->m_unmodelled2A4 + 4)->y;
			m_aimPos.z = reinterpret_cast<const Coord3D *>(obj->m_unmodelled2A4 + 4)->z;
			float ten = 10.0f;
			m_aimPos.x -= obj->m_cachedPos.x;
			m_aimPos.y -= obj->m_cachedPos.y;
			m_aimPos.z -= obj->m_cachedPos.z;
			float len = (float)sqrt(m_aimPos.y * m_aimPos.y + m_aimPos.x * m_aimPos.x);
			float *chosen = (g_bfmeK1254 > len) ? &ten : &len;
			float denom = *chosen;
			AimWeaponBehaviorModuleData *data = m_moduleData;
			float pitch = m_aimPos.z / denom;
			if (pitch > data->m_pitchHigh)
			{
				m_aiming = 1;
				setAimCondition(obj, 0xA8);
			}
			else if (pitch < data->m_pitchLow)
			{
				m_aiming = 1;
				setAimCondition(obj, 0xAA);
			}
			else
			{
				m_aiming = 1;
				setAimCondition(obj, 0xA9);
			}
			if (denom < data->m_rangeMin)
			{
				m_aiming = 1;
				obj->clearAndSetModelConditionFlags(reinterpret_cast<const BitFlags<320> &>(Rva00170C70BitSet(0, 0xAC)), reinterpret_cast<const BitFlags<320> &>(Rva00170C70BitSet(0, 0xAB)));
			}
			else if (denom > data->m_rangeMax)
			{
				m_aiming = 1;
				obj->clearAndSetModelConditionFlags(reinterpret_cast<const BitFlags<320> &>(Rva00170C70BitSet(0, 0xAB)), reinterpret_cast<const BitFlags<320> &>(Rva00170C70BitSet(0, 0xAC)));
			}
			drawStash[0]->applyPendingModelConditionFlags(0);
		}

		if (m_aiming)
		{
			if (!ai->isAttacking() || ai->bfmeBlocksFormationRefresh() || ai->isIdle())
			{
				m_aiming = 0;
				obj->clearModelConditionFlags(reinterpret_cast<const BitFlags<304> &>(BfmeE1166(0, 0xAB, 0xAC, 0xAA, 0xA9, 0xA8)));
				drawStash[0]->applyPendingModelConditionFlags(0);
			}
		}

		return UPDATE_SLEEP_NONE;
	}
	return UPDATE_SLEEP_FOREVER;
}
