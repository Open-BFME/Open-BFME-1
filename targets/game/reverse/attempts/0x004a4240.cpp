// ?getCommandAvailability@ControlBar@@IBE?AW4CommandAvailability@@PBVCommandButton@@PAVGameWindow@@PAVObject@@PAM_N@Z
// partial score=0.93 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ControlBar::getCommandAvailability (retail 0x004A4240, 4572 B), rewritten
// from the retail disassembly instead of the Zero Hour ControlBarCommand.cpp
// skeleton. Identity: sole named caller ControlBar::updateSpecialPowerShortcut
// (0x0049E3C9 pushes Bool, Real*, Object*, GameWindow*, CommandButton*) and the
// GeneralsMD twin. Switch labels come from the retail jump tables at
// 0x004A541C (targets) / 0x004A547C (index bytes, type-1). Members are named
// by offset: only offsets are witnessed here, not names.
//
// BANK STATE (opus-5.5, 2026-09-28, pass 2): compiles 4670 B incl. jump
// table, probe shape 0.932, 2876 non-reloc diffs, 17 structural diffs.
// Pass-2 levers: upgrade local before canAffordUpgrade (cases 5/6/7 tails),
// single re-fetch of the projectile interface in case 1, ai/contain locals so
// the pointer loads straight into ECX, options loaded before the battle-plan
// virtual call. Prologue, this=EBX and the EBP=-1 constant now match retail.
// Residue: first CastleBehavior key reload uses ECX (6 B) where retail uses
// EAX (5 B) at +0x28D, shifting everything after by one byte; query zero
// stores after the hidden-return push (+0x2A2); shared return-0 epilogue
// placement (+0xE53); case 7 not cross-jumped onto the case 5 tail; spUpdate
// +0x20 lea
// order. Mechanical eh_levers + shape_family_levers (register, store,
// constant, copy): 16 trials, no gain. A `const Int none = -1` local changes
// nothing (folded). No pins are needed: all 63 call targets have ledger rows;
// landing needs these TU-local declarations respelled to the ledger names.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef int NameKeyType;

enum CommandAvailability
{
	COMMAND_RESTRICTED,				// ZH recursion: non-hidden disabled result
	COMMAND_AVAILABLE,				// the switch's break value
	COMMAND_ACTIVE,
	COMMAND_HIDDEN,
	COMMAND_NOT_READY,				// set with *readiness
	COMMAND_CANT_AFFORD,
	COMMAND_AVAILABILITY_6,
	COMMAND_AVAILABILITY_7
};

class Object;
class Player;
class ThingTemplate;
class UpgradeTemplate;
class SpecialPowerTemplate;
class CommandButton;
class Module;

class AsciiString
{
public:
	__forceinline ~AsciiString() { releaseBuffer(); }
	Bool isEmpty() const throw();
private:
	void releaseBuffer();
	char *m_data;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define NAMEKEY(s) TheNameKeyGenerator->nameToKey(s)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Int getBuildable() const;
	Bool canRappel() const { return (m_kindof[1] & 0x800) != 0; }
private:
	unsigned char m_padding[0xc0];
	volatile UnsignedInt m_kindof[3];
};

class UpgradeTemplate
{
public:
	void *m_vtbl;
	Int m_upgradeType;				// +0x04
};

class SpecialPowerTemplate
{
public:
	Int getRequiredScience() const;
	Int getSpecialPowerType() const;
};

struct CastleQueryKey004A3AB0
{
	CastleQueryKey004A3AB0() { m_value[0] = 0; m_value[1] = 0; m_value[2] = 0; m_value[3] = 0; m_value[4] = 0; m_value[5] = 0; }
	Int m_value[6];
};

struct CastleQuery004A4240
{
	CastleQuery004A4240() : m_result(false) {}
	CastleQueryKey004A3AB0 m_key;
	Bool m_result;
};

class CommandButton
{
public:
	const ThingTemplate *getThingTemplate() const;					// ILT 0x000205CC
	CastleQueryKey004A3AB0 getCastleQueryKey() const;				// ILT 0x00021CC9
	AsciiString getString184() const;								// ILT 0x00015E51
	Int pickLayer(Int layer) const;									// ILT 0x0001123E

	unsigned char m_pad00[0x10];
	Int m_commandType;				// +0x10
	unsigned char m_pad14[0x04];
	UnsignedInt m_options;			// +0x18
	unsigned char m_pad1c[0x04];
	const UpgradeTemplate *m_upgrade20;	// +0x20
	const UpgradeTemplate *m_upgrade24;	// +0x24
	unsigned char m_pad28[0x0c];
	const SpecialPowerTemplate *m_specialPower;	// +0x34
	unsigned char m_pad38[0x34];
	Int m_weaponSlot;				// +0x6c
	unsigned char m_pad70[0x30];
	Int m_valueA0;					// +0xa0
	unsigned char m_padA4[0xa9];
	Bool m_flag14D;					// +0x14d
	unsigned char m_pad14E[0x04];
	Bool m_flag152;					// +0x152
	unsigned char m_pad153;
	Int m_value154;					// +0x154
};

class GameWindow
{
public:
	UnsignedInt winGetStatus();
};

class Module
{
public:
	virtual ~Module();
	unsigned char m_pad04[0x14];
	Int m_objectID18;				// +0x18
	unsigned char m_pad1c[0x04];
};

typedef Int (*CastleQueryFn)(void *, void *);
Int castleQueryCallback0002C11F(void *, void *);

class CastleBehavior : public Module
{
public:
	Bool isCastle0036BA40();
	Bool isPlayerAllowedToPackOrUnpack(Player *player, Bool flag);
	Bool canUnpack(Bool flag);
	Bool canPlayerAffordUnpack(Player *player) const;
	Real ratio0036CD50() const;
	Bool canAfford0036BA60(Player *player, const ThingTemplate *thing) const;
	Int query(CastleQueryFn fn, void *data);
};

class BattlePlanInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual UnsignedInt getCommandOption();					// +0x0c
};

class BattlePlanUpdate : public Module, public BattlePlanInterface
{
public:
	Int getActiveBattlePlan();								// ILT 0x0002CE21
};

class GateInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14();
	virtual Bool isOpen();									// +0x18
	virtual void v1c(); virtual void v20(); virtual void v24();
	virtual Bool isUsable();								// +0x28
};

class GateBehavior : public GateInterface, public Module
{
};

class StealthUpdate : public Module
{
public:
	unsigned char cmp002AC0B0();
};

class SpecialAbilityInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14();
	virtual Bool isPowerCurrentlyInUse(const CommandButton *command);	// +0x18
};

class SpecialAbilityUpdate : public Module, public SpecialAbilityInterface
{
};

class SpecialPowerModuleInterface
{
public:
	virtual void v00();
	virtual Bool isReady();									// +0x04
	virtual Real getPercentReady();							// +0x08
	virtual Bool v0c();
	virtual void v10(); virtual void v14();
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate();	// +0x18
	virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
	virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
	virtual Bool v58(Int arg);								// +0x58
};

class ProductionUpdateInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
	virtual Bool isUpgradeInQueue(const UpgradeTemplate *upgrade);	// +0x14
	virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
	virtual void v2c(); virtual void v30(); virtual void v34();
	virtual Int getProductionCount();						// +0x38
	virtual void v3c(); virtual void v40(); virtual void v44();
	virtual void *firstProduction();						// +0x48
};

class DozerAIInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
	virtual void v14();
	virtual Bool isTaskPending(Int task);					// +0x18
};

#define VSLOTS8(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); \
	virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7();

#define VSLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define VSLOTS1(p) virtual void p();

class AIUpdateInterface
{
public:
	VSLOTS8(a) VSLOTS8(b) VSLOTS8(c) VSLOTS8(d) VSLOTS8(e) VSLOTS8(f) VSLOTS8(g) VSLOTS8(h) VSLOTS8(i)
	VSLOTS4(j) VSLOTS1(k0) VSLOTS1(k1) VSLOTS1(k2)
	virtual DozerAIInterface *getDozerAIInterface();		// +0x13c
	VSLOTS8(l) VSLOTS8(m) VSLOTS8(n) VSLOTS8(o) VSLOTS8(p) VSLOTS4(q)
	virtual Bool isMoving();								// +0x1f0
};

class ProjectileUpdateInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual Bool v0c();
};

class StructureCompletionInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
	virtual Bool v14();
	virtual Bool v18(Player *player);
	virtual Bool v1c();
};

class IntList
{
public:
	UnsignedInt size() const;
};

typedef void (*ContainCallback)(void *, void *);
void Rva004A41D0UpgradeSinkCallback(void *, void *);

class ContainModuleInterface
{
public:
	VSLOTS8(a) VSLOTS8(b) VSLOTS8(c) VSLOTS8(d) VSLOTS8(e) VSLOTS8(f) VSLOTS8(g)
	VSLOTS4(h) VSLOTS1(i0) VSLOTS1(i1) VSLOTS1(i2)
	virtual void callForEach(ContainCallback fn, void *data, Bool flag);	// +0x100 - 4 = +0xfc
	virtual UnsignedInt getCount(Int arg);					// +0x100
	virtual const struct ContainedItemsList *getContainedItemsList() const;	// +0x104
	virtual IntList *getList();								// +0x108
};

class Relation1BFE20
{
public:
	VSLOTS8(a) VSLOTS8(b) VSLOTS8(c)
	virtual Bool v60(const ThingTemplate *thing);			// +0x60
};

class Interface200
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
	virtual void v14(); virtual void v18(); virtual void v1c();
	virtual Int v20();										// +0x20
};

class Weapon
{
public:
	Int getClipReloadTime(const Object *obj) const;
	Bool isLive001E1B70();
	Int getStatus(Bool *flag = 0) const;
	Real getPercentReadyToFire() const;

	unsigned char m_pad00[0x0c];
	Int m_weaponSlot;				// +0x0c
	unsigned char m_pad10[0x08];
	UnsignedInt m_possibleNextShotFrame;	// +0x18
};

class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(Int slot) const;
};

class WordBitTest000D2F40
{
public:
	Bool test(UnsignedInt index) const;
};

class DisabledMaskType
{
public:
	Int count() const;
	Bool any() const { return m_bits != 0; }
	Bool test(Int bit) const { return (m_bits & (1 << bit)) != 0; }
	UnsignedInt m_bits;
};

class CastleMember
{
public:
	unsigned char m_pad00[0x18];
	Int m_castleID;					// +0x18
};
CastleMember *rva0036BB10FindCastleMemberBehavior(const Object *obj);

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool hasUpgrade(const UpgradeTemplate *upgrade) const;
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	ProductionUpdateInterface *getProductionUpdateInterface();
	ProjectileUpdateInterface *getProjectileUpdateInterface() const;
	StructureCompletionInterface *getStructureCompletionInterface();
	Bool isKindOf(Int kindOf) const;
	Module *findModule(NameKeyType key) const;
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
	SpecialAbilityUpdate *findSpecialAbilityUpdate(Int type) const;
	Bool testStatus(Int bit) const;
	Bool isLocallyControlled() const;
	Weapon *getCurrentWeapon(Int *slot = 0);
	Int getDestinationLayer() const;
	Relation1BFE20 *unidentified001BFE20() const;

	const ThingTemplate *getTemplate() const
	{
		const volatile unsigned char *address = reinterpret_cast<const volatile unsigned char *>(this);
		address += 4;
		return *(const ThingTemplate *volatile *)address;
	}
	Bool testScriptStatusBit(UnsignedInt bit) const { return (m_status343 & bit) != 0; }
	Bool isDisabled() const { return m_disabled.m_bits != 0; }
	DisabledMaskType getDisabledFlags() const { return m_disabled; }

	unsigned char m_pad000[0x110];
	WordBitTest000D2F40 m_bits110;	// +0x110
	unsigned char m_pad114[0x90];
	DisabledMaskType m_disabled;	// +0x1a4
	unsigned char m_pad1a8[0x54];
	ContainModuleInterface *m_contain;	// +0x1fc
	Interface200 *m_iface200;		// +0x200
	AIUpdateInterface *m_ai;		// +0x204
	unsigned char m_pad208[0x08];
	Int *m_ptr210;					// +0x210
	unsigned char m_pad214[0x50];
	WeaponSet m_weaponSet;			// +0x264
	unsigned char m_pad265[0xde];
	unsigned char m_status343;		// +0x343
	unsigned char m_status344;		// +0x344
	unsigned char m_pad345[0x02];
	Bool m_flag347;					// +0x347
};

class Drawable
{
public:
	unsigned char m_pad[0xfc];
	Object *m_object;				// +0xfc
};

struct DrawableListNode
{
	DrawableListNode *m_next;
	DrawableListNode *m_prev;
	Drawable *m_data;
};

struct DrawableList
{
	DrawableListNode *m_node;
};

class InGameUI
{
public:
	VSLOTS8(a) VSLOTS8(b) VSLOTS8(c) VSLOTS8(d) VSLOTS8(e) VSLOTS8(f) VSLOTS8(g)
	VSLOTS4(h) VSLOTS1(i0) VSLOTS1(i1) VSLOTS1(i2)
	virtual const DrawableList *getAllSelectedDrawables();	// +0xfc
};
extern InGameUI *TheInGameUI;

class ScienceValues000F9820
{
public:
	Real getValue(Int index, Int *cost);
};

class Player
{
public:
	Object *findNaturalCommandCenter();
	Object *findObject000D4490();
	Bool hasUpgradeComplete(const UpgradeTemplate *upgrade);
	Bool hasUpgradeInProduction(const UpgradeTemplate *upgrade);
	Bool canBuild(const ThingTemplate *thing) const;
	Bool canAffordBuild(const ThingTemplate *thing) const;
	Bool isPlayerActive() const;
	Bool hasScience(Int science) const;
	Bool isScienceDisabled(Int science) const;
	Bool isScienceHidden(Int science) const;

	unsigned char m_pad00[0x2c];
	Int m_playerType;				// +0x2c
	unsigned char m_pad30[0x1c];
	UnsignedInt m_money4c;			// +0x4c
	unsigned char m_pad50[0x634];
	ScienceValues000F9820 m_values684;	// +0x684
};

class PlayerList
{
public:
	Player *getLocalPlayer();
	Bool isLocalAlliedWith(Object *obj);
};
extern PlayerList *ThePlayers;

class GameLogic
{
public:
	Object *findObjectByID(Int id);
	unsigned char m_pad[0x3c];
	UnsignedInt m_frame;			// +0x3c
};
extern GameLogic *TheGameLogic;

class BuildAssistant
{
public:
	VSLOTS8(a) VSLOTS8(b)
	virtual Int canMakeUnit(Object *obj, const ThingTemplate *thing, Int arg);	// +0x40
};
extern BuildAssistant *TheBuildAssistant;

class UpgradeCenter
{
public:
	Bool canAffordUpgrade(Player *player, const UpgradeTemplate *upgrade, const ThingTemplate *thing, Bool flag) const;
};
extern UpgradeCenter *TheUpgradeCenter;

extern Real g_bfmeDefaultBU;
extern const Real BfmeZeroRange;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
protected:
	CommandAvailability getCommandAvailability(const CommandButton *command, GameWindow *win, Object *obj,
		Real *readiness, Bool forceDisabledEvaluation) const;
	Int commandMaskCheck004A3D50(const CommandButton *command, Object *obj) const;
};
extern ControlBar *TheControlBar;

struct ContainedItemNode
{
	ContainedItemNode *m_next;
	ContainedItemNode *m_prev;
	Object *m_item;
};

struct ContainedItemsList
{
	ContainedItemNode *m_node;
};

// Same body as the landed 0x004A4160 (ControlBar_getRappellerCount.cpp). It
// is defined in this TU because retail +0xB9A passes the object in EAX: MSVC's
// same-TU static calling convention, so the caller only matches with the
// definition visible here.
static __declspec(noinline) Int getRappellerCount(Object *obj)
{
	Int num = 0;
	const ContainedItemsList *items = obj->m_contain ? obj->m_contain->getContainedItemsList() : 0;
	if (items)
	{
		ContainedItemNode *sentinel = items->m_node;
		for (ContainedItemNode *it = sentinel->m_next; it != sentinel; it = it->m_next)
		{
			Object *member = it->m_item;
			const ThingTemplate *thingTemplate = member->getTemplate();
			if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
				thingTemplate = (const ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
			if (thingTemplate->canRappel())
				++num;
		}
	}
	return num;
}

CommandAvailability ControlBar::getCommandAvailability(const CommandButton *command, GameWindow *win,
	Object *obj, Real *readiness, Bool forceDisabledEvaluation) const
{
	*readiness = 1.0f;
	Player *player = ThePlayers->getLocalPlayer();
	if (player == 0)
		return COMMAND_HIDDEN;

	switch (command->m_commandType)
	{
		case 0x1f: obj = player->findNaturalCommandCenter(); break;
		case 0x24: obj = player->findObject000D4490(); break;
	}

	if (obj == 0)
		return COMMAND_HIDDEN;
	if (obj->testScriptStatusBit(1) || obj->testScriptStatusBit(2))
		return COMMAND_HIDDEN;
	if (obj->getDisabledFlags().m_bits & 0x20)
		return COMMAND_HIDDEN;

	Bool bit = obj->m_bits110.test(0xcb);
	if ((command->m_options & 0x4000000) && !bit)
		return COMMAND_RESTRICTED;
	if ((command->m_options & 0x8000000) && bit)
		return COMMAND_RESTRICTED;
	if (command->m_options & 0x40000000)
	{
		AIUpdateInterface *ai = obj->m_ai;
		if (ai && ai->isMoving())
			return COMMAND_RESTRICTED;
	}

	Int commandType = command->m_commandType;
	if (commandType != 0x17 && commandMaskCheck004A3D50(command, obj) == COMMAND_HIDDEN)
		return COMMAND_RESTRICTED;
	if (obj->m_flag347)
		return COMMAND_RESTRICTED;

	Int *ptr210 = obj->m_ptr210;
	if (ptr210 == 0)
		return COMMAND_HIDDEN;
	if (command->m_value154 > 0 && ptr210[10] < command->m_value154)
		return COMMAND_HIDDEN;

	DisabledMaskType flags = obj->getDisabledFlags();
	Bool disabled = flags.any();
	if (disabled && (flags.m_bits & 0x100) && DisabledMaskType(flags).count() == 1)
		disabled = false;
	if (disabled && (command->m_options & 0x100000) && (flags.m_bits & 0x40) && DisabledMaskType(flags).count() == 1)
		disabled = false;
	if (disabled && !forceDisabledEvaluation)
	{
		if (commandType != 0x10 && commandType != 0x26 && commandType != 0x0f
			&& commandType != 0x13 && commandType != 0x14 && commandType != 0x1a)
		{
			if (getCommandAvailability(command, win, obj, readiness, true) == COMMAND_HIDDEN)
				return COMMAND_HIDDEN;
			return COMMAND_RESTRICTED;
		}
	}

	if (command->m_options & 0x40)
	{
		const UpgradeTemplate *upgradeT = command->m_upgrade24;
		if (upgradeT)
		{
			if (upgradeT->m_upgradeType == 0)
			{
				if (player->hasUpgradeComplete(upgradeT) == false)
					return COMMAND_RESTRICTED;
			}
			else if (upgradeT->m_upgradeType == 1 && obj->hasUpgrade(upgradeT) == false)
			{
				if (command->getThingTemplate())
				{
					Int status = command->getThingTemplate()->getBuildable();
					if (status == 2 || (status == 3 && obj->getControllingPlayer()->m_playerType != 1))
						return COMMAND_HIDDEN;
				}
				return COMMAND_RESTRICTED;
			}
		}
	}

	if (command->m_options & 0x800)
	{
		CastleMember *member = rva0036BB10FindCastleMemberBehavior(obj);
		if (member)
		{
			Object *castle = TheGameLogic->findObjectByID(member->m_castleID);
			if (castle == 0)
				return COMMAND_HIDDEN;
			static NameKeyType key_Castle0 = NAMEKEY("CastleBehavior");
			CastleBehavior *castleBehavior = (CastleBehavior *)castle->findModule(key_Castle0);
			if (castleBehavior)
			{
				CastleQuery004A4240 query;
				query.m_key = command->getCastleQueryKey();
				castleBehavior->query(castleQueryCallback0002C11F, &query);
				if (!query.m_result)
					return COMMAND_HIDDEN;
			}
		}
	}

	ProductionUpdateInterface *pu = obj->getProductionUpdateInterface();
	if (pu && pu->firstProduction() && (command->m_options & 0x10000))
		return COMMAND_RESTRICTED;
	Bool queueMaxed = pu ? (pu->getProductionCount() == 20) : false;

	switch (command->m_commandType)
	{
		case 0x01:
		{
			if (command->getThingTemplate())
			{
				Int status = command->getThingTemplate()->getBuildable();
				if (status == 2 || (status == 3 && obj->getControllingPlayer()->m_playerType != 1))
					return COMMAND_HIDDEN;
			}
			if (obj->isKindOf(0x0e) == false && obj->isKindOf(0x67) == false)
				return COMMAND_RESTRICTED;
			AIUpdateInterface *ai = obj->m_ai;
			DozerAIInterface *dozerAI = ai ? ai->getDozerAIInterface() : 0;
			ProjectileUpdateInterface *projectile = obj->getProjectileUpdateInterface();
			if (dozerAI == 0 && projectile == 0)
				return COMMAND_RESTRICTED;
			if (dozerAI && dozerAI->isTaskPending(0) == true)
				return COMMAND_RESTRICTED;
			if (projectile)
			{
				ProjectileUpdateInterface *again = obj->getProjectileUpdateInterface();
				if (again && again->v0c())
					return COMMAND_RESTRICTED;
			}
			if (player->canBuild(command->getThingTemplate()) == false)
				return command->m_flag14D ? COMMAND_HIDDEN : COMMAND_RESTRICTED;
			if (!player->canAffordBuild(command->getThingTemplate()))
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 0x21:
		{
			static NameKeyType key_Castle1 = NAMEKEY("CastleBehavior");
			CastleBehavior *castle = (CastleBehavior *)obj->findModule(key_Castle1);
			if (castle == 0 || !castle->isCastle0036BA40()
				|| !castle->isPlayerAllowedToPackOrUnpack(obj->getControllingPlayer(), false))
				return COMMAND_HIDDEN;
			return COMMAND_ACTIVE;
		}

		case 0x20:
		{
			static NameKeyType key_Castle2 = NAMEKEY("CastleBehavior");
			CastleBehavior *castle = (CastleBehavior *)obj->findModule(key_Castle2);
			if (castle == 0 || !castle->canUnpack(false)
				|| !castle->isPlayerAllowedToPackOrUnpack(obj->getControllingPlayer(), false))
				return COMMAND_HIDDEN;
			if (!castle->canPlayerAffordUnpack(obj->getControllingPlayer()))
				return COMMAND_CANT_AFFORD;
			Real ratio = castle->ratio0036CD50();
			*readiness = ratio;
			if (ratio >= g_bfmeDefaultBU)
				return COMMAND_ACTIVE;
			return COMMAND_NOT_READY;
			return COMMAND_ACTIVE;
		}

		case 0x30:
		{
			const ThingTemplate *thing = command->getThingTemplate();
			static NameKeyType key_Castle3 = NAMEKEY("CastleBehavior");
			CastleBehavior *castle = (CastleBehavior *)obj->findModule(key_Castle3);
			if (thing == 0 || castle == 0 || !castle->canUnpack(false)
				|| !castle->isPlayerAllowedToPackOrUnpack(obj->getControllingPlayer(), false))
				return COMMAND_HIDDEN;
			if (!castle->canAfford0036BA60(obj->getControllingPlayer(), thing))
				return COMMAND_CANT_AFFORD;
			Real ratio = castle->ratio0036CD50();
			*readiness = ratio;
			if (ratio >= g_bfmeDefaultBU)
				return COMMAND_ACTIVE;
			return COMMAND_NOT_READY;
			return COMMAND_ACTIVE;
		}

		case 0x31:
		{
			StructureCompletionInterface *sci = obj->getStructureCompletionInterface();
			if (sci == 0)
				return COMMAND_HIDDEN;
			if (sci->v1c())
				return sci->v18(obj->getControllingPlayer()) ? COMMAND_ACTIVE : COMMAND_CANT_AFFORD;
			return sci->v14() ? COMMAND_AVAILABILITY_7 : COMMAND_RESTRICTED;
		}

		case 0x03:
		{
			if (obj->m_status344 & 1)
				return COMMAND_RESTRICTED;
			const ThingTemplate *thing = command->getThingTemplate();
			if (thing == 0)
				return COMMAND_HIDDEN;
			Int status = thing->getBuildable();
			if (status == 2 || (status == 3 && obj->getControllingPlayer()->m_playerType != 1))
				return COMMAND_HIDDEN;
			if (queueMaxed)
				return COMMAND_CANT_AFFORD;
			if (player->canBuild(thing) == false)
				return COMMAND_RESTRICTED;
			Int makeType = TheBuildAssistant->canMakeUnit(obj, thing, -1);
			if (makeType == 7)
				return COMMAND_AVAILABILITY_6;
			if (makeType == 6 || makeType == 5)
				return COMMAND_RESTRICTED;
			if (makeType == 2)
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 0x2c:
		{
			if (!ThePlayers->isLocalAlliedWith(obj))
				return COMMAND_HIDDEN;
			if (obj->m_status344 & 1)
				return COMMAND_RESTRICTED;
			Player *owner = obj->getControllingPlayer();
			Int index = command->m_valueA0;
			if (owner == 0 || index == -1)
				return COMMAND_RESTRICTED;
			Int cost = 0;
			Real value = owner->m_values684.getValue(index, &cost);
			*readiness = value;
			if (value == BfmeZeroRange)
				return COMMAND_RESTRICTED;
			if (value != g_bfmeDefaultBU)
				return COMMAND_NOT_READY;
			return owner->m_money4c < (UnsignedInt)cost ? COMMAND_CANT_AFFORD : COMMAND_AVAILABLE;
		}

		case 0x2f:
		{
			ContainModuleInterface *contain = obj->m_contain;
			if (contain && contain->getCount(0) > 0)
				return COMMAND_RESTRICTED;
			break;
		}

		case 0x05:
		{
			if (command->m_upgrade20 == 0)
				return COMMAND_HIDDEN;
			if (queueMaxed)
				return COMMAND_CANT_AFFORD;
			if (player->hasUpgradeComplete(command->m_upgrade20) == true
				|| player->hasUpgradeInProduction(command->m_upgrade20) == true)
				return COMMAND_AVAILABILITY_7;
			const UpgradeTemplate *upgrade = command->m_upgrade20;
			if (TheUpgradeCenter->canAffordUpgrade(player, upgrade, command->getThingTemplate(), false) == false)
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 0x06:
		{
			if (command->m_upgrade20 == 0)
				return COMMAND_HIDDEN;
			if (obj->isKindOf(0x95) && obj->m_iface200->v20() == 3)
				return COMMAND_RESTRICTED;
			if (queueMaxed)
				return COMMAND_CANT_AFFORD;
			if (pu == 0)
				return COMMAND_RESTRICTED;
			if (obj->hasUpgrade(command->m_upgrade20) == true
				|| pu->isUpgradeInQueue(command->m_upgrade20) == true)
				return COMMAND_AVAILABILITY_7;
			if (obj->affectedByUpgrade(command->m_upgrade20) == false)
				return COMMAND_RESTRICTED;
			const UpgradeTemplate *upgrade = command->m_upgrade20;
			if (TheUpgradeCenter->canAffordUpgrade(player, upgrade, command->getThingTemplate(), false) == false)
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 0x07:
		{
			if (queueMaxed)
				return COMMAND_CANT_AFFORD;
			if (pu == 0)
				return COMMAND_RESTRICTED;
			if (!pu->isUpgradeInQueue(command->m_upgrade20))
			{
				static NameKeyType key_CastleMember = NAMEKEY("CastleMemberBehavior");
				Module *member = obj->findModule(key_CastleMember);
				if (member)
				{
					Object *castle = TheGameLogic->findObjectByID(member->m_objectID18);
					if (castle && castle->hasUpgrade(command->m_upgrade20))
						return COMMAND_AVAILABILITY_7;
				}
			}
			const UpgradeTemplate *upgrade = command->m_upgrade20;
			if (TheUpgradeCenter->canAffordUpgrade(player, upgrade, command->getThingTemplate(), false) == false)
				return COMMAND_CANT_AFFORD;
			break;
		}

		case 0x16:
		{
			if (obj->m_ai == 0)
				return COMMAND_RESTRICTED;
			Weapon *w = obj->m_weaponSet.getWeaponInWeaponSlot(command->m_weaponSlot);
			UnsignedInt now = TheGameLogic->m_frame;
			if (w == 0)
				break;
			if (w->getClipReloadTime(obj) == 0 && !w->isLive001E1B70())
				break;
			if (w->getStatus() != 0 || w->m_possibleNextShotFrame == now || w->m_possibleNextShotFrame == now - 1)
			{
				if (w->getStatus() == 3 || w->isLive001E1B70())
					*readiness = w->getPercentReadyToFire();
				else
					*readiness = 0.0f;
				return COMMAND_NOT_READY;
			}
			break;
		}

		case 0x19:
		{
			if (getRappellerCount(obj) <= 0)
				return COMMAND_RESTRICTED;
			break;
		}

		case 0x0f:
		{
			if (win && !(win->winGetStatus() & 8))
				return COMMAND_RESTRICTED;
			ContainModuleInterface *contain = obj->m_contain;
			if (contain)
			{
				struct { Object *m_obj; Bool m_found; } sink;
				sink.m_found = false;
				sink.m_obj = obj;
				contain->callForEach(Rva004A41D0UpgradeSinkCallback, &sink, true);
				if (sink.m_found)
					return COMMAND_HIDDEN;
			}
			break;
		}

		case 0x10:
		{
			ContainModuleInterface *contain = obj->m_contain;
			if (contain == 0 || contain->getCount(0) <= 0)
				return COMMAND_RESTRICTED;
			break;
		}

		case 0x26:
		{
			ContainModuleInterface *contain = obj->m_contain;
			if (contain == 0 || contain->getList() == 0
				|| obj->m_contain->getList()->size() <= 0)
				return COMMAND_RESTRICTED;
			break;
		}

		case 0x17:
		case 0x1f:
		case 0x24:
		{
			const SpecialPowerTemplate *power = command->m_specialPower;
			if (!command->m_flag152 || power == 0)
				return COMMAND_HIDDEN;
			Int science = power->getRequiredScience();
			if (science != -1)
			{
				Player *owner = obj->getControllingPlayer();
				if (owner == 0 || !owner->isPlayerActive() || !owner->hasScience(science))
					return COMMAND_HIDDEN;
				if (owner->isScienceDisabled(science) || owner->isScienceHidden(science))
					return COMMAND_RESTRICTED;
			}
			SpecialPowerModuleInterface *mod = obj->getSpecialPowerModule(power);
			if (mod == 0)
			{
				if (!command->getString184().isEmpty())
				{
					const CommandButton *other = TheControlBar->findCommandButton(command->getString184());
					if (other && other->m_commandType == 0x17 && other->m_specialPower)
					{
						obj->getSpecialPowerModule(other->m_specialPower);
						return COMMAND_AVAILABLE;
					}
				}
				break;
			}
			if (mod->isReady() == false)
			{
				Real percent = mod->getPercentReady();
				*readiness = percent;
				if (percent <= BfmeZeroRange && mod->v0c())
				{
					*readiness = 1.0f;
					return COMMAND_RESTRICTED;
				}
				return commandMaskCheck004A3D50(command, obj) == COMMAND_HIDDEN ? COMMAND_RESTRICTED : COMMAND_NOT_READY;
			}
			if (commandMaskCheck004A3D50(command, obj) == COMMAND_HIDDEN || !mod->v58(0))
				return COMMAND_RESTRICTED;
			if (SpecialAbilityUpdate *spUpdate = obj->findSpecialAbilityUpdate(power->getSpecialPowerType()))
			{
				if (spUpdate->isPowerCurrentlyInUse(command))
					return COMMAND_RESTRICTED;
			}
			else if (mod->getSpecialPowerTemplate()->getSpecialPowerType() == 0x24)
			{
				static NameKeyType key_BattlePlanUpdate = NAMEKEY("BattlePlanUpdate");
				BattlePlanUpdate *update = (BattlePlanUpdate *)obj->findModule(key_BattlePlanUpdate);
				if (update)
				{
					UnsignedInt options = command->m_options;
					if (update->getCommandOption() & options)
						return COMMAND_ACTIVE;
				}
			}
			break;
		}

		case 0x28:
		case 0x29:
		case 0x2a:
		{
			static NameKeyType key_Gate = NAMEKEY("GateOpenAndCloseBehavior");
			GateBehavior *gate = static_cast<GateBehavior *>(obj->findModule(key_Gate));
			if (gate == 0)
				gate = static_cast<GateBehavior *>(obj->findModule(NAMEKEY("GateProxyBehavior")));
			if (obj->testStatus(2) || (obj->m_status344 & 1) || gate == 0 || !gate->isUsable())
				return COMMAND_RESTRICTED;
			if (command->m_commandType == 0x2a)
				return COMMAND_ACTIVE;
			if (command->m_commandType == 0x29 && !gate->isOpen())
				return COMMAND_ACTIVE;
			if (command->m_commandType == 0x28 && gate->isOpen() == true)
				return COMMAND_ACTIVE;
			return COMMAND_RESTRICTED;
		}

		case 0x1a:
		{
			if (obj->m_weaponSet.getWeaponInWeaponSlot(command->m_weaponSlot) == 0)
				return COMMAND_RESTRICTED;
			const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
			for (DrawableListNode *it = selected->m_node->m_next; it != selected->m_node; it = it->m_next)
			{
				Drawable *draw = it->m_data;
				if (draw && draw->m_object && draw->m_object->isLocallyControlled() && draw->m_object->getCurrentWeapon())
				{
					if (draw->m_object->getCurrentWeapon()->m_weaponSlot != command->m_weaponSlot)
						return COMMAND_AVAILABLE;
				}
			}
			return COMMAND_ACTIVE;
		}

		case 0x22:
		{
			Int layer = obj->getDestinationLayer();
			Int picked = command->pickLayer(layer);
			if (picked == 3 || picked == layer || obj->m_weaponSet.getWeaponInWeaponSlot(picked) == 0)
				return COMMAND_HIDDEN;
		}
		// fall through
		case 0x0d:
		{
			if (!(command->m_options & 0x2000))
				return COMMAND_AVAILABLE;
			static NameKeyType key_BattlePlanUpdate = NAMEKEY("BattlePlanUpdate");
			BattlePlanUpdate *bpUpdate = (BattlePlanUpdate *)obj->findModule(key_BattlePlanUpdate);
			if (bpUpdate && bpUpdate->getActiveBattlePlan() != 1)
				return COMMAND_RESTRICTED;
			return COMMAND_AVAILABLE;
		}

		case 0x25:
		{
			if (!obj->testStatus(0x12))
				return COMMAND_RESTRICTED;
			static NameKeyType key_StealthUpdate = NAMEKEY("StealthUpdate");
			StealthUpdate *stealth = (StealthUpdate *)obj->findModule(key_StealthUpdate);
			if (stealth && !stealth->cmp002AC0B0())
				return COMMAND_RESTRICTED;
			break;
		}

		case 0x32:
		{
			const ThingTemplate *thing = command->getThingTemplate();
			Relation1BFE20 *relation = obj->unidentified001BFE20();
			if (thing == 0 || relation == 0 || !relation->v60(thing))
				return COMMAND_RESTRICTED;
			break;
		}
	}
	return COMMAND_AVAILABLE;
}
