// ?update@RampageBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.69 date=2026-09-23
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// RampageBehavior secondary UpdateModule interface entry at retail 0x00203F90.

typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

class AsciiString
{
private:
	void *m_data;
};
class UpgradeTemplate;
class Drawable;
class Object;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;
extern Real g_bfmeDefaultBU;

template <class T>
inline const T &maxRef(const T &left, const T &right)
{
	return left > right ? left : right;
}

struct RampageUpgradeRange
{
	AsciiString *m_begin;
	AsciiString *m_end;
};

class RampageBehaviorModuleData
{
private:
	UnsignedByte m_pad00[8];

public:
	RampageUpgradeRange m_upgrades;
	UnsignedInt m_pad10;
	Real m_threshold;
	Int m_frames18;
	Int m_frames1c;
	Int m_condition20;
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual Real getHealth() const = 0;
	virtual void slot14() = 0;
	virtual Real getMaxHealth() const = 0;
};

class AICommandInterface
{
public:
	virtual void slot00();
	void aiIdle(CommandSourceType source);
	void aiAttackPosition(const Coord3D *position, Int maxShots,
		CommandSourceType source);
};

class AIUpdateInterface
{
private:
	UnsignedByte m_pad00[0x20];

public:
	AICommandInterface m_commands;
};

class CountermeasuresBehaviorInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08(Int value) = 0;
};

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable() const;

	Bool hasUpgrade(const UpgradeTemplate *upgrade) const;
	Int bfmeHasSignificantPreferredLocomotorHeight() const;
	void notifyModelConditionChanged();

	private:
	UnsignedByte m_pad04[0x11c];

	public:
	UnsignedInt m_status120;
	UnsignedInt m_status124;
	UnsignedByte m_pad128[0xd8];
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
	UnsignedByte m_pad208[0x13c];
	UnsignedByte m_effectivelyDead;
};

class DrawableApplyPendingThunk
{
public:
	void apply(Bool immediate);
};

class Rva00203DB0Owner
{
public:
	UnsignedByte ready() const;
};

class Rva001BF6B0Query
{
public:
	void *query();
};

class Rva001BEF20FieldAddress
{
public:
	char *get();
};

class Gen001C9A10
{
public:
	void handle(Int player);
};

class Gen001C9AC0
{
public:
	void handle(Int player);
};

extern void j_00004b33();
extern void j_0000f8e4();
extern void j_000122ab();
extern void j_0001336d();
extern void j_000209fa();
extern void j_0002191d();
extern void j_00024d70();
extern void j_0002d439();
extern void j_000348ec();
extern void j_0003e54a();
extern void j_000404c1();

#pragma comment(linker, "/alternatename:?findUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@ABVAsciiString@@@Z=?j_0002f95a@@YAXXZ")
#pragma comment(linker, "/alternatename:?hasUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z=?j_0000ba37@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeHasSignificantPreferredLocomotorHeight@Object@@QBEHXZ=?j_0003e54a@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")
#pragma comment(linker, "/alternatename:?aiIdle@AICommandInterface@@QAEXW4CommandSourceType@@@Z=?j_00024d70@@YAXXZ")
#pragma comment(linker, "/alternatename:?aiAttackPosition@AICommandInterface@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z=?j_000404c1@@YAXXZ")
#pragma comment(linker, "/alternatename:?apply@DrawableApplyPendingThunk@@QAEX_N@Z=?j_0002d439@@YAXXZ")
#pragma comment(linker, "/alternatename:?ready@Rva00203DB0Owner@@QBEEXZ=?j_00004b33@@YAXXZ")
#pragma comment(linker, "/alternatename:?handle@Gen001C9A10@@QAEXH@Z=?j_000348ec@@YAXXZ")
#pragma comment(linker, "/alternatename:?handle@Gen001C9AC0@@QAEXH@Z=?j_000122ab@@YAXXZ")

typedef void *(Rva001BF6B0Query::*QueryCall)();
typedef char *(Rva001BEF20FieldAddress::*FieldCall)();
typedef UnsignedByte (Rva00203DB0Owner::*ReadyCall)() const;
typedef void (AICommandInterface::*CommandCall)(Int, Int);

static __forceinline void *queryCountermeasures(Object *object)
{
	union { void (*raw)(); QueryCall member; } route;
	route.raw = j_0000f8e4;
	return (reinterpret_cast<Rva001BF6B0Query *>(object)->*route.member)();
}

static __forceinline char *weaponSetField(Object *object)
{
	union { void (*raw)(); FieldCall member; } route;
	route.raw = j_000209fa;
	return (reinterpret_cast<Rva001BEF20FieldAddress *>(object)->*route.member)();
}

static __forceinline Bool rampageReady(unsigned char *self)
{
	union { void (*raw)(); ReadyCall member; } route;
	route.raw = j_00004b33;
	return (reinterpret_cast<Rva00203DB0Owner *>(self - 0x10)->*route.member)() != 0;
}

static __forceinline void issueSecondaryCommand(AICommandInterface *commands)
{
	union { void (*raw)(); CommandCall member; } route;
	route.raw = j_0001336d;
	(commands->*route.member)(0, 2);
}

class RampageBehavior
{
public:
	virtual UpdateSleepTime update();

private:
	UnsignedByte m_pad04[0x0c];
	Real m_healthRatio;
	Int m_rampageFrames;
	Int m_countdownFrames;
};

union RampageBodyOrMaxHealth
{
	BodyModuleInterface *m_body;
	Real m_maxHealth;
	};

struct RampageUpdateLocals
{
	Real m_health;
	RampageBodyOrMaxHealth m_bodyOrMaxHealth;
	Drawable *m_drawable;
	Real m_defaultHealth;
};

// ?update@RampageBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime RampageBehavior::update()
{
	RampageBehaviorModuleData *data;
	RampageUpdateLocals locals;
	Object *object = *reinterpret_cast<Object **>(
		reinterpret_cast<unsigned char *>(this) - 0x08);
	AIUpdateInterface *ai = object->m_ai;
	locals.m_bodyOrMaxHealth.m_body = object->m_body;
	locals.m_drawable = object->getDrawable();

	if (locals.m_bodyOrMaxHealth.m_body == 0 || ai == 0 || locals.m_drawable == 0)
		return UPDATE_SLEEP_FOREVER;

	data =
		*reinterpret_cast<RampageBehaviorModuleData **>(
			reinterpret_cast<unsigned char *>(this) - 0x0c);
	AsciiString *upgrade = data->m_upgrades.m_begin;
	while (upgrade != data->m_upgrades.m_end)
	{
		const UpgradeTemplate *upgradeTemplate =
			TheUpgradeCenter->findUpgrade(*upgrade);
		if (!object->hasUpgrade(upgradeTemplate))
			goto returnNone;
		++upgrade;
	}

	locals.m_health = locals.m_bodyOrMaxHealth.m_body->getHealth();
	locals.m_bodyOrMaxHealth.m_maxHealth =
		locals.m_bodyOrMaxHealth.m_body->getMaxHealth();
	locals.m_defaultHealth = 1.0f;
	const Real healthRatio = locals.m_health /
		*(g_bfmeDefaultBU > locals.m_bodyOrMaxHealth.m_maxHealth ?
			&locals.m_defaultHealth : &locals.m_bodyOrMaxHealth.m_maxHealth);

	if (m_rampageFrames > 0)
	{
		Int frames = --m_rampageFrames;
		if (frames > 0 &&
			(*reinterpret_cast<UnsignedByte *>(reinterpret_cast<unsigned char *>(object) + 0x344) & 1) == 0 &&
			(UnsignedByte)object->bfmeHasSignificantPreferredLocomotorHeight() == 0)
			goto countdown;

		UnsignedInt weaponFlags = *reinterpret_cast<UnsignedInt *>(weaponSetField(object));
		if ((weaponFlags & 0x100) != 0)
			reinterpret_cast<Gen001C9AC0 *>(object)->handle(8);

		if ((*reinterpret_cast<UnsignedByte *>(reinterpret_cast<unsigned char *>(object) + 0x344) & 1) == 0 &&
			(UnsignedByte)object->bfmeHasSignificantPreferredLocomotorHeight() == 0)
		{
			reinterpret_cast<AICommandInterface *>(
				reinterpret_cast<unsigned char *>(ai) + 0x20)->aiIdle(CMD_FROM_AI);
		}

		m_countdownFrames = data->m_condition20;
		m_rampageFrames = 0;

		if ((object->m_status120 & 0x01000000) != 0)
		{
			object->m_status120 &= 0xfeffffff;
			object->notifyModelConditionChanged();
		}
		goto applyDrawable;
	}
	else
	{
		if (healthRatio < data->m_threshold ||
			(*reinterpret_cast<UnsignedByte *>(reinterpret_cast<unsigned char *>(object) + 0x344) & 1) != 0)
			goto countdown;

		UnsignedInt weaponFlags = *reinterpret_cast<UnsignedInt *>(weaponSetField(object));
		if ((weaponFlags & 0x100) != 0)
			goto countdown;

		if (locals.m_health < m_healthRatio)
			goto countdown;

		if (m_countdownFrames != 0)
			goto countdown;

		if (rampageReady(reinterpret_cast<unsigned char *>(this)))
		{
			reinterpret_cast<Gen001C9AC0 *>(object)->handle(7);
			reinterpret_cast<Gen001C9A10 *>(object)->handle(8);
			reinterpret_cast<AICommandInterface *>(
				reinterpret_cast<unsigned char *>(ai) + 0x20)->aiAttackPosition(
				reinterpret_cast<const Coord3D *>(reinterpret_cast<unsigned char *>(object) + 0x38),
				0x0ffffffe, CMD_FROM_AI);
			m_rampageFrames = data->m_frames18;
		}
		else
		{
			UnsignedInt conditionMask = 0x01000000;
			if ((object->m_status120 & conditionMask) == 0)
			{
				object->m_status120 |= conditionMask;
				object->notifyModelConditionChanged();
			}
			issueSecondaryCommand(reinterpret_cast<AICommandInterface *>(
				reinterpret_cast<unsigned char *>(ai) + 0x20));
			m_rampageFrames = data->m_frames1c;
		}
	}

	if ((object->m_status120 & 0x00400000) != 0)
	{
		object->m_status120 &= 0xffbfffff;
		object->notifyModelConditionChanged();
	}
	if ((*reinterpret_cast<UnsignedByte *>(reinterpret_cast<unsigned char *>(object) + 0x124)) & 4)
	{
		object->m_status124 &= ~4;
		object->notifyModelConditionChanged();
	}
	if ((*reinterpret_cast<UnsignedByte *>(reinterpret_cast<unsigned char *>(object) + 0x124)) & 8)
	{
		object->m_status124 &= ~8;
		object->notifyModelConditionChanged();
	}
	if ((*reinterpret_cast<UnsignedByte *>(reinterpret_cast<unsigned char *>(object) + 0x124)) & 0x10)
	{
		object->m_status124 &= ~0x10;
		object->notifyModelConditionChanged();
	}
	if ((*reinterpret_cast<UnsignedByte *>(reinterpret_cast<unsigned char *>(object) + 0x124)) & 0x20)
	{
		object->m_status124 &= ~0x20;
			object->notifyModelConditionChanged();
	}

	{
		CountermeasuresBehaviorInterface *countermeasures =
			reinterpret_cast<CountermeasuresBehaviorInterface *>(queryCountermeasures(object));
		if (countermeasures != 0)
			countermeasures->slot08(0);
	}

applyDrawable:
	{
		DrawableApplyPendingThunk *apply =
		reinterpret_cast<DrawableApplyPendingThunk *>(locals.m_drawable);
		apply->apply(false);
	}

countdown:
	if (m_countdownFrames > 0)
	{
		Int frames = --m_countdownFrames;
		if (frames <= 0)
			m_healthRatio = locals.m_health;
	}

returnNone:
	return UPDATE_SLEEP_NONE;
}
