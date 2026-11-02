// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: ActiveBody::attemptDamage, retail 0x00211D40, 1803 bytes.
//
// Identity: ilt_oracle confirms ?attemptDamage@ActiveBody@@UAEXPAVDamageInfo@@@Z
// exactly at this body; DetachableRiderBody::attemptDamage and
// PorcupineFormationBodyModule::attemptDamage reach it as their base call.
// The flow is Zero Hour's attemptDamage (armor adjust, healing hand-off,
// last-damage bookkeeping, damage/state module notification, death) with
// BFME's additions: a container notification, a damager relation interface
// that can force a kill, per-state disable timers from the module data, the
// low-health voice (event 0x7E0), the RespawnUpdate threshold (1.01) and the
// delayed Lua event on death.
//
// The method is a virtual of the body interface at +0x10 inside the module,
// so this points there: the primary vtable is this-0x10, the module data
// this-0x0C and the object this-0x08 (same view as attemptHealing).
//
// Shape notes (all read off the bytes): the last-damage else branch is Zero
// Hour's nested srcObj2/srcObj1 form, whose three copies the compiler merges
// into one tail; it reloads the GameLogic singleton into a local rather than
// reusing the frame compare's load, which the TheBfmeGameLogic spelling of the
// same 0x012F0898 global reproduces. The RespawnUpdate test is one condition
// (findModule && health <= 1.01 && prev > 1.01) whose failure falls into the
// death test. Zero Hour's inline accessors (getFrame, getID, getPlayerIndex,
// getContainedBy/getContain) are kept: they decide the scratch registers.
#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
// stlport
#include <list>

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
enum ObjectID { INVALID_ID = 0 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum KindOfType
{
	BFME_KINDOF_08 = 0x08,
	BFME_KINDOF_09 = 0x09,
	BFME_KINDOF_19 = 0x19,
	BFME_KINDOF_2D = 0x2D,
	BFME_KINDOF_36 = 0x36,
	BFME_KINDOF_58 = 0x58,
};
enum DisabledType { BFME_DISABLED_08 = 8 };
enum
{
	BFME_DAMAGE_04 = 4,
	DAMAGE_HEALING = 7,
	DAMAGE_UNRESISTABLE = 8,
};
enum
{
	BFME_SOUND_DAMAGED = 0x63,
	BFME_SOUND_REALLY_DAMAGED = 0x64,
};

class Drawable;
typedef _STL::list<Drawable *> DrawableList;

namespace GameMessage { enum Type { BFME_MSG_7E0 = 0x7E0 }; }
class PickAndPlayInfo;
extern bool pickAndPlayUnitVoiceResponse(const DrawableList *list,
	GameMessage::Type messageType, PickAndPlayInfo *info);

class DamageInfo
{
public:
	DamageInfo &operator=(const DamageInfo &);		// ILT 0x00017E4F

	char m_unreconstructed000[0x04];
	char m_in[0x04];					// +0x04 the input record HealingArmor001B0200::adjust reads
	Int m_sourceID;						// +0x08
	char m_unreconstructed00C[0x04];
	Int m_damageType;					// +0x10
	char m_unreconstructed014[0x0c];
	Bool m_kill;						// +0x20
	char m_unreconstructed021[0x50 - 0x21];
	Real m_actualDamageDealt;				// +0x50
	Real m_actualDamageClipped;				// +0x54
	char m_unreconstructed058[0x04];
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &);			// ILT 0x00047B27
	~AudioEventRTS();					// ILT 0x00026F35
	void setObjectID(ObjectID id);				// ILT 0x00019A6A
private:
	unsigned char m_unmodelled_000[0x70];
};

class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const;		// ILT 0x0001BFD1
};

class AudioManager
{
public:
	virtual void unusedSlot00(); virtual void unusedSlot01(); virtual void unusedSlot02(); virtual void unusedSlot03();
	virtual void unusedSlot04(); virtual void unusedSlot05(); virtual void unusedSlot06(); virtual void unusedSlot07();
	virtual void unusedSlot08(); virtual void unusedSlot09(); virtual void unusedSlot10(); virtual void unusedSlot11();
	virtual void unusedSlot12(); virtual void unusedSlot13(); virtual void unusedSlot14(); virtual void unusedSlot15();
	virtual void unusedSlot16();
	virtual void addAudioEvent(const AudioEventRTS *event);	// vtable +0x44
};
extern AudioManager *TheAudio;

class Player
{
public:
	void setAttackedBy(Int playerIndex);
	char m_unreconstructed000[0x24];
	Int m_playerIndex;					// +0x24
	Int getPlayerIndex() const { return m_playerIndex; }
};

class Object;
class Module;
class Thing { public: Bool isKindOf(KindOfType t) const; };

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void unusedSlot01();
	virtual void onBodyDamageStateChange(DamageInfo *damageInfo, Int oldState, Int newState);
};

class BehaviorModuleInterface
{
public:
	virtual void unusedSlot00(); virtual void unusedSlot01(); virtual void unusedSlot02(); virtual void unusedSlot03();
	virtual DamageModuleInterface *getDamage();
};

class BehaviorModule
{
public:
	char m_unreconstructed000[0x0c];
	BehaviorModuleInterface m_interface;			// +0x0C
};

#define V(N) virtual void slot##N()
class ContainModuleInterface
{
public:
	V(00);V(01);V(02);V(03);V(04);V(05);V(06);V(07);V(08);V(09);V(10);V(11);V(12);V(13);V(14);V(15);V(16);V(17);V(18);V(19);V(20);
	virtual void slot21(Object *obj, void *body, DamageInfo *damageInfo);	// vtable +0x54
	V(22);V(23);V(24);V(25);V(26);V(27);V(28);V(29);V(30);V(31);V(32);V(33);V(34);V(35);V(36);V(37);V(38);V(39);
	V(40);V(41);V(42);V(43);V(44);V(45);V(46);V(47);V(48);V(49);V(50);V(51);V(52);V(53);V(54);V(55);V(56);V(57);V(58);V(59);
	V(60);V(61);V(62);V(63);
	virtual UnsignedInt slot64(Int);			// vtable +0x100
};

class LinkedBodyInterface
{
public:
	V(00);V(01);V(02);V(03);V(04);V(05);V(06);V(07);V(08);V(09);V(10);V(11);V(12);V(13);V(14);V(15);V(16);V(17);V(18);V(19);
	V(20);V(21);V(22);V(23);V(24);V(25);V(26);V(27);V(28);V(29);V(30);V(31);V(32);V(33);V(34);V(35);V(36);V(37);V(38);
	virtual void setDamageState(Int state);			// vtable +0x9C
};

class Object
{
	friend class ActiveBody;
public:
	V(00);V(01);V(02);V(03);V(04);V(05);V(06);V(07);V(08);V(09);
	virtual const ThingTemplate *getTemplate(void) const;	// vtable +0x28

	Bool isKindOf(KindOfType t) const { return ((const Thing *)this)->isKindOf(t); }
	Player *getControllingPlayer() const;
	void setDisabledUntil(DisabledType type, UnsignedInt frame);
	void onDie(DamageInfo *damageInfo);
	void setEffectivelyDead(Bool dead);
	void setStatusBit(Int bit, Bool set);
	Bool isFactionStructure() const;
protected:
	Module *findModule(NameKeyType key) const;
public:
	char m_unreconstructed004[0x74 - 0x04];
	ObjectID m_id;						// +0x74
	ObjectID getID() const { return m_id; }
	char m_unreconstructed078[0x94 - 0x78];
	UnsignedInt m_status94;					// +0x94
	char m_unreconstructed098[0x134 - 0x98];
	UnsignedInt m_modelCondition134;			// +0x134
	char m_unreconstructed138[0x1f0 - 0x138];
	BehaviorModule **m_behaviors;				// +0x1F0
	char m_unreconstructed1F4[0x1fc - 0x1f4];
	ContainModuleInterface *m_contain;			// +0x1FC
	ContainModuleInterface *getContain() const { return m_contain; }
	Object *getContainedBy() const { return m_containedBy; }
	LinkedBodyInterface *m_body;				// +0x200
	char m_unreconstructed204[0x214 - 0x204];
	Object *m_containedBy;					// +0x214
	char m_unreconstructed218[0x344 - 0x218];
	unsigned char m_privateStatus;				// +0x344
};

class BFMEActionObject { public: Bool testStatus(Int status) const; };
struct RvaC4390Interface
{
	V(00);V(01);V(02);
	virtual Bool slot03(Object *victim);			// vtable +0x0C
	V(04);V(05);V(06);V(07);
	virtual void slot08(Object *victim);			// vtable +0x20
};
struct RvaC4390First { RvaC4390Interface *getInterface(); };
class Rva0025DF30Object { public: Rva0025DF30Object *related(Int); };
class Gen_001be760 { public: void m(Int); };
class BFMEReportDamageSource { public: void report(Object *victim, Int); };

// report is reached through ILT 0x0001B94B (body 0x001C9490, still a gen dump); the
// ledger defines that ILT as ?j_0001b94b@@YAXXZ, so the call names it through a
// member-pointer view.
extern void j_0001b94b(void);
static __forceinline void reportDamageSource(BFMEReportDamageSource *source, Object *victim, int setting)
{
	union { void (*raw)(void); void (BFMEReportDamageSource::*member)(Object *, int); } call;
	call.raw = j_0001b94b;
	(source->*call.member)(victim, setting);
}
class BfmeObj1004;
char bfmeGo1004A(BfmeObj1004 *);

class BfmeDelayedLuaEvent
{
public:
	char m_pad0[0x0c];
	UnsignedInt m_value;
	char m_pad1[0x04];
	UnsignedInt m_count;
};

class DelayedLuaEventList;
class BfmeDelayedLuaEventList
{
public:
	BfmeDelayedLuaEventList();				// ILT 0x00019CF9
	~BfmeDelayedLuaEventList();				// ILT 0x00013156
	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};
class BfmeOwnerBR { public: void bfmeGo939B(Int, Object *, DelayedLuaEventList *); };
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class NameKeyGenerator { public: NameKeyType nameToKey(const char *name); };
extern NameKeyGenerator *TheNameKeyGenerator;

class GameLogic
{
public:
	Object *findObjectByID(Int id);
	UnsignedInt getFrame() const { return m_frame; }
	char m_unreconstructed000[0x3c];
	UnsignedInt m_frame;					// +0x3C
};
extern GameLogic *TheGameLogic;
extern GameLogic *TheBfmeGameLogic;			// same retail global as TheGameLogic

struct AIData { char m_pad[0x64]; Bool m_flag64; };
class AI { public: char m_pad[0x14]; AIData *m_data; };
extern AI *TheAI;

class HealingArmor001B0200 { public: float adjust(void *, Object *, Int); };

class ActiveBodyModuleData
{
public:
	char m_unreconstructed000[0x1c];
	UnsignedInt m_damagedDisableFrames;			// +0x1C
	UnsignedInt m_reallyDamagedDisableFrames;		// +0x20
	UnsignedInt m_damageTimerFrames;			// +0x24
};

class ActiveBodyPrimary
{
public:
	V(00);V(01);V(02);V(03);V(04);V(05);V(06);V(07);V(08);V(09);V(10);V(11);V(12);V(13);
	virtual void validateArmorAndDamageFX();		// vtable +0x38
	virtual void doDamageFX(DamageInfo *damageInfo);	// vtable +0x3C
	V(16);V(17);V(18);
	virtual void slot19();					// vtable +0x4C
};

struct Rva00211890DamageInfo;
class Rva00211890Owner { public: void forwardSourcePosition(float amount, Rva00211890DamageInfo *damage); };

class ActiveBody
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual void attemptHealing(DamageInfo *damageInfo);
	V(02);V(03);V(04);V(05);V(06);V(07);V(08);V(09);V(10);V(11);V(12);V(13);V(14);V(15);V(16);V(17);V(18);V(19);
	V(20);V(21);V(22);V(23);V(24);V(25);V(26);V(27);V(28);V(29);V(30);V(31);
	virtual void internalChangeHealth(Real delta, DamageInfo *damageInfo);	// vtable +0x80

	ActiveBodyPrimary *primary() { return (ActiveBodyPrimary *)((char *)this - 0x10); }
	const ActiveBodyModuleData *getModuleData() const { return *(const ActiveBodyModuleData **)((char *)this - 0x0c); }
	Object *getObject() const { return *(Object **)((char *)this - 0x08); }

	Real m_damageScalar;					// +0x04
	Real m_currentHealth;					// +0x08
	Real m_prevHealth;					// +0x0C
	Real m_maxHealth;					// +0x10
	char m_unreconstructed14[0x20 - 0x14];
	Int m_curDamageState;					// +0x20
	char m_unreconstructed24[0x30 - 0x24];
	DamageInfo m_lastDamageInfo;				// +0x30
	UnsignedInt m_lastDamageTimestamp;			// +0x8C
	char m_unreconstructed90[0x96 - 0x90];
	Bool m_lastDamageCleared;				// +0x96
	Bool m_indestructible;					// +0x97
	char m_unreconstructed98[0xbc - 0x98];
	Int m_linkedObjectID;					// +0xBC
	char m_unreconstructedC0[0xc8 - 0xc0];
	HealingArmor001B0200 m_curArmor;			// +0xC8
};

void ActiveBody::attemptDamage(DamageInfo *damageInfo)
{
	primary()->validateArmorAndDamageFX();
	const ActiveBodyModuleData *data = getModuleData();
	Object *obj = getObject();
	if (damageInfo == 0)
		return;
	if (m_indestructible)
		return;
	if (obj->m_modelCondition134 & 0x200)
		return;
	UnsignedInt status = obj->m_status94;
	if ((status & 0x8000000) && damageInfo->m_damageType != DAMAGE_UNRESISTABLE)
		return;

	Object *container = obj->m_containedBy;
	if (container && !obj->isKindOf(BFME_KINDOF_36)) {
		ContainModuleInterface *contain = container->m_contain;
		if (contain)
			contain->slot21(obj, primary(), damageInfo);
	}

	damageInfo->m_actualDamageDealt = 0.0f;
	damageInfo->m_actualDamageClipped = 0.0f;
	if (obj->m_privateStatus & 1)
		return;

	Real amount = m_curArmor.adjust(damageInfo->m_in, obj, 0);
	switch (damageInfo->m_damageType) {
	case DAMAGE_HEALING:
		if (!damageInfo->m_kill)
			attemptHealing(damageInfo);
		return;
	}
	if (damageInfo->m_damageType != DAMAGE_UNRESISTABLE)
		amount *= m_damageScalar;

	Object *damager = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
	if (damager && ((BFMEActionObject *)damager)->testStatus(0x40)) {
		Rva0025DF30Object *related = ((Rva0025DF30Object *)damager)->related(0);
		if (related) {
			RvaC4390Interface *relation = ((RvaC4390First *)related)->getInterface();
			if (relation && relation->slot03(obj)) {
				damageInfo->m_kill = true;
				relation->slot08(obj);
			}
		}
	}

	if (amount > 0.0f || damageInfo->m_kill) {
		Int oldState = m_curDamageState;
		if (damageInfo->m_kill)
			amount = m_currentHealth;
		if (damageInfo->m_damageType == BFME_DAMAGE_04)
			((Rva00211890Owner *)primary())->forwardSourcePosition(amount, (Rva00211890DamageInfo *)damageInfo);
		internalChangeHealth(-amount, damageInfo);
		if (data->m_damageTimerFrames > 0)
			((Gen_001be760 *)obj)->m(data->m_damageTimerFrames + TheGameLogic->getFrame());
		damageInfo->m_actualDamageDealt = amount;
		damageInfo->m_actualDamageClipped = m_prevHealth - m_currentHealth;

		UnsignedInt now = TheGameLogic->getFrame();
		if (m_lastDamageTimestamp != now && m_lastDamageTimestamp != now - 1) {
			m_lastDamageInfo = *damageInfo;
			m_lastDamageCleared = false;
			m_lastDamageTimestamp = TheGameLogic->getFrame();
		} else {
			GameLogic *logic = TheBfmeGameLogic;
			Object *srcObj1 = logic->findObjectByID(m_lastDamageInfo.m_sourceID);
			Object *srcObj2 = logic->findObjectByID(damageInfo->m_sourceID);
			if (srcObj2) {
				if (srcObj1) {
					if (srcObj2->isKindOf(BFME_KINDOF_09) || srcObj2->isKindOf(BFME_KINDOF_08) ||
						srcObj2->isFactionStructure()) {
						m_lastDamageInfo = *damageInfo;
						m_lastDamageCleared = false;
						m_lastDamageTimestamp = TheGameLogic->getFrame();
					}
				} else {
					m_lastDamageInfo = *damageInfo;
					m_lastDamageCleared = false;
					m_lastDamageTimestamp = TheGameLogic->getFrame();
				}
			}
		}

		Object *srcObj = 0;
		if (m_lastDamageInfo.m_sourceID != INVALID_ID) {
			srcObj = TheGameLogic->findObjectByID(m_lastDamageInfo.m_sourceID);
			if (srcObj) {
				Player *srcPlayer = srcObj->getControllingPlayer();
				obj->getControllingPlayer()->setAttackedBy(srcPlayer->getPlayerIndex());
			}
		}

		if (m_currentHealth < m_prevHealth) {
			for (BehaviorModule **m = obj->m_behaviors; *m; ++m) {
				DamageModuleInterface *d = (*m)->m_interface.getDamage();
				if (!d)
					continue;
				d->onDamage(damageInfo);
			}
		}

		if (m_curDamageState != oldState) {
			for (BehaviorModule **m = obj->m_behaviors; *m; ++m) {
				DamageModuleInterface *d = (*m)->m_interface.getDamage();
				if (!d)
					continue;
				d->onBodyDamageStateChange(damageInfo, oldState, m_curDamageState);
			}
			if (m_curDamageState == 1 && (Real)data->m_damagedDisableFrames > 0.0f)
				obj->setDisabledUntil(BFME_DISABLED_08, data->m_damagedDisableFrames + TheGameLogic->getFrame());
			else if (m_curDamageState == 2 && (Real)data->m_reallyDamagedDisableFrames > 0.0f)
				obj->setDisabledUntil(BFME_DISABLED_08, data->m_reallyDamagedDisableFrames + TheGameLogic->getFrame());

			const ThingTemplate *tmpl = obj->getTemplate();
			if (tmpl) {
				if (m_curDamageState == 1) {
					AudioEventRTS damaged = *tmpl->getSound(BFME_SOUND_DAMAGED);
					damaged.setObjectID(obj->getID());
					TheAudio->addAudioEvent(&damaged);
				} else if (m_curDamageState == 2) {
					AudioEventRTS reallyDamaged = *tmpl->getSound(BFME_SOUND_REALLY_DAMAGED);
					reallyDamaged.setObjectID(obj->getID());
					TheAudio->addAudioEvent(&reallyDamaged);
				}
			}

			if (m_linkedObjectID) {
				Object *linked = TheGameLogic->findObjectByID(m_linkedObjectID);
				if (linked) {
					LinkedBodyInterface *body = linked->m_body;
					if (body)
						body->setDamageState(m_curDamageState);
				}
			}
		}

		Real inverseMax = 1.0f / m_maxHealth;
		if (m_prevHealth * inverseMax >= 0.35f && m_currentHealth * inverseMax < 0.35f && m_currentHealth > 0.0f) {
			DrawableList drawables;
			drawables.push_back((Drawable *)obj->getTemplate());
			pickAndPlayUnitVoiceResponse(&drawables, GameMessage::BFME_MSG_7E0, 0);
		}

		static NameKeyType respawnKey = TheNameKeyGenerator->nameToKey("RespawnUpdate");
		if (obj->findModule(respawnKey) && m_currentHealth <= 1.01f && m_prevHealth > 1.01f) {
			if (damager)
				reportDamageSource((BFMEReportDamageSource *)damager, obj, 1);
		} else if (m_currentHealth <= 0.0f && m_prevHealth > 0.0f) {
			if (damager)
				reportDamageSource((BFMEReportDamageSource *)damager, obj, 1);
			if (bfmeGo1004A((BfmeObj1004 *)obj)) {
				m_currentHealth = 1.0f;
			} else {
				Bool contained = obj->getContainedBy() != 0;
				if (contained) {
					if (obj->getContainedBy()->getContain() && obj->getContainedBy()->getContain()->slot64(0) < 2)
						contained = false;
				}
				obj->onDie(damageInfo);
				if (m_linkedObjectID) {
					Object *linked = TheGameLogic->findObjectByID(m_linkedObjectID);
					if (linked) {
						linked->onDie(damageInfo);
						linked->setEffectivelyDead(true);
					}
				}
				if (!contained && !obj->isKindOf(BFME_KINDOF_19) && !obj->isKindOf(BFME_KINDOF_58))
					primary()->slot19();
			}
		}

		BfmeDelayedLuaEventList events;
		if (srcObj) {
			events.m_events[0].m_value = srcObj->m_id;
			events.m_events[0].m_count = 3;
		}
		((BfmeOwnerBR *)TheLuaScriptEngine)->bfmeGo939B(0, obj, (DelayedLuaEventList *)&events);
	}

	primary()->doDamageFX(damageInfo);
	if (TheAI->m_data->m_flag64 && obj->isKindOf(BFME_KINDOF_2D))
		obj->setStatusBit(8, true);
}
