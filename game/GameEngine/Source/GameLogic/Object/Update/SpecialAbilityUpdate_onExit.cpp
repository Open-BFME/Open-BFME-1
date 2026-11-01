// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: SpecialAbilityUpdate::onExit, retail 0x002A8540 (814 bytes,
// ret 8 at +0x32B).  Zero Hour's onExit (status clear, prep sound removal,
// endPreparation, killSpecialObjects, state resets) with the BFME additions
// the Open BFME 2 donor (Code/GameEngine/Source/GameLogic/Object/Update/
// SpecialAbilityUpdate.cpp, retail 0x004502CE) also carries: the AI flag
// reset, the special-power module notify, the per-power-type exits (capture
// target release for 0x27/0x28, AutoHealBehavior for 0x66), the paralyze
// commands and the attribute-modifier removal.  Offsets are BFME 1's, read
// from the retail body; callee names are the ledger's.  The protected virtual
// spelling (MAE) is the one ilt_oracle confirms for ILT slot 11952.

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int AudioHandle;

enum CommandSourceType { CMD_FROM_AI = 2 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum KindOfType { KINDOF_6 = 6, KINDOF_83 = 0x83 };
enum ObjectStatusTypes { OBJECT_STATUS_3E = 0x3e };

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

template<int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };

	BitFlags() { }
	BitFlags(BogusInitType, int bit) { m_bits.set(bit); }
	void set(int bit) { m_bits.set(bit); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class ClientSubsystem
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
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void removeAudioEvent(AudioHandle event);
};

class AudioManager;
extern AudioManager *TheAudio;

class Object;

class Module
{
};

class UpdateModule
{
public:
	void resetWakeState();
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22();
	virtual void onSpecialAbilityExit();		// +0x5C
};

// Object +0x1FC: slot +0x98 takes the captured target, the module-data
// count at +0x1D0 and the owner.
class Rva002A8540Container
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37();
	virtual void release(Object *target, Int value, Object *owner);	// +0x98
};

// Object +0x200: slot +0x54 takes a percentage and a flag.
class Rva002A8540Body
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20();
	virtual void setPercent(Real percent, Int flag);	// +0x54
};

class AICommandInterface
{
public:
	void rva001F1370(Int value, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
};

class BfmeThingEW
{
public:
	void bfmeSwapEW();
};

class AIUpdateInterface
{
public:
	unsigned char m_unmodelled_000[0x20];
	AICommandInterface m_commandInterface;		// +0x20
	unsigned char m_unmodelled_021[0x338 - 0x21];
	Bool m_flag338;								// +0x338
};

// The ledger defines the 11-byte tail thunk at 0x001BE220 as
// ?invoke@Rva001BE220@@QAEXXZ; this call keeps its own argument shape and
// names that defined symbol.
extern "C" void __identifier("?invoke@Rva001BE220@@QAEXXZ")(void);

class Rva001BE220Receiver
{
};

static __forceinline void dispatchRva001BE220(Rva001BE220Receiver *receiver,
		Int condition, UnsignedInt frames)
{
	typedef void (Rva001BE220Receiver::*Call)(Int, UnsignedInt);
	union { void (*raw)(); Call member; } call;
	call.raw = __identifier("?invoke@Rva001BE220@@QAEXXZ");
	(receiver->*call.member)(condition, frames);
}

class BfmeMsgXI;
class BfmeOwnerXI
{
public:
	void bfmeSendXI(BfmeMsgXI *message);
};

class SpecialPowerTemplate;

class ModelConditionFlags
{
public:
	UnsignedInt m_bits;
};

static inline void setModelConditionBit(ModelConditionFlags &flags, int condition)
{
	flags.m_bits |= 1u << condition;
}

class Thing
{
public:
	Bool isKindOf(KindOfType t) const;
};

class Object : public Thing
{
	friend class SpecialAbilityUpdate;
public:
	void setStatus(const ObjectStatusMaskType &, Bool set = true);
	void clearStatus(ObjectStatusTypes);
	void notifyModelConditionChanged();
	__forceinline void setModelConditionState(int condition)
	{
		if (!((m_modelConditionFlags.m_bits & (1u << condition)) != 0))
		{
			setModelConditionBit(m_modelConditionFlags, condition);
			notifyModelConditionChanged();
		}
	}
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *t) const;

protected:
	Module *findModule(NameKeyType key) const;

public:
	unsigned char m_unmodelled_000[0x110];
	unsigned char m_unmodelled_110[0x118 - 0x110];
	ModelConditionFlags m_modelConditionFlags;	// +0x118
	unsigned char m_unmodelled_11c[0x124 - 0x11c];
	UnsignedInt m_modelConditionWord124;		// +0x124
	unsigned char m_unmodelled_128[0x138 - 0x128];
	unsigned char m_unmodelled_138[0x1fc - 0x138];
	Rva002A8540Container *m_field1fc;			// +0x1FC
	Rva002A8540Body *m_field200;				// +0x200
	AIUpdateInterface *m_ai;					// +0x204
	unsigned char m_unmodelled_208[0x3a0 - 0x208];
	Int m_field3a0;								// +0x3A0
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};
extern GameLogic *TheGameLogic;

class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	Int getSpecialPowerType() const
	{
		return getFO()->m_type;
	}

private:
	const SpecialPowerTemplate *getFO() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}

	unsigned char m_unmodelled_08[0x0c];
	Int m_type;									// +0x14
};

struct Rva002A8540StringData
{
	Int m_refCount;
	unsigned short m_length;
};

class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x1c8];
	Int m_specialConditionType;					// +0x1C8
	UnsignedInt m_specialConditionFrames;		// +0x1CC
	Int m_containValue;							// +0x1D0
	unsigned char m_unmodelled_1d4[0x1d8 - 0x1d4];
	const SpecialPowerTemplate *m_specialPowerTemplate;	// +0x1D8
	unsigned char m_unmodelled_1dc[0x1e8 - 0x1dc];
	Rva002A8540StringData *m_attributeModifier;	// +0x1E8
	unsigned char m_unmodelled_1ec[0x228 - 0x1ec];
	Int m_paralyzeWhenCompleted;				// +0x228
	Int m_paralyzeWhenAborted;					// +0x22C
	unsigned char m_unmodelled_230[0x241 - 0x230];
	Bool m_specialObjectsPersistent;			// +0x241
	Bool m_uniqueSpecialObjectTargets;			// +0x242
	Bool m_specialObjectsPersistWhenOwnerDies;	// +0x243
	unsigned char m_unmodelled_244[0x24b - 0x244];
	Bool m_killAttributeModifierOnExit;			// +0x24B
};

class Gen_002A6DE0
{
public:
	void bfmeGo1274();
};

class AutoHealBehavior;

class SpecialAbilityUpdate
{
public:
	void endPreparation();

protected:
	virtual void onExit(Bool cleanup, Bool aborted);
	void killSpecialObjects();

private:

	const SpecialAbilityUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;							// +0x08
	unsigned char m_unmodelled_00c[0x24 - 0x0c];
	Int m_field24;								// +0x24
	unsigned char m_unmodelled_028[0x30 - 0x28];
	Int m_packingState;							// +0x30
	unsigned char m_unmodelled_034[0x40 - 0x34];
	AudioHandle m_prepSoundHandle;				// +0x40
	unsigned char m_unmodelled_044[0xa4 - 0x44];
	AudioHandle m_packSoundHandle;				// +0xA4
	unsigned char m_unmodelled_0a8[0xac - 0xa8];
	Int m_targetID;								// +0xAC
	unsigned char m_unmodelled_0b0[0xd4 - 0xb0];
	UnsignedInt m_flagsD4;						// +0xD4
	unsigned char m_unmodelled_0d8[0xdc - 0xd8];
	Bool m_active;								// +0xDC
	unsigned char m_unmodelled_0dd;
	Bool m_fieldDE;								// +0xDE
	unsigned char m_unmodelled_0df[0xe2 - 0xdf];
	Bool m_withinStartAbilityRange;				// +0xE2
	unsigned char m_unmodelled_0e3;
	Bool m_fieldE4;								// +0xE4
	Bool m_fieldE5;								// +0xE5
};

// ?onExit@SpecialAbilityUpdate@@MAEX_N0@Z
void SpecialAbilityUpdate::onExit(Bool cleanup, Bool aborted)
{
	const SpecialAbilityUpdateModuleData *data = m_moduleData;
	Object *obj = m_object;

	((Gen_002A6DE0 *)this)->bfmeGo1274();
	{
		ObjectStatusMaskType mask(ObjectStatusMaskType::kInit, 24);
		mask.set(69);
		mask.set(23);
		obj->setStatus(mask, false);
	}

	AIUpdateInterface *ai = obj->m_ai;
	if (ai)
	{
		ai->m_flag338 = false;
		((BfmeThingEW *)ai)->bfmeSwapEW();
	}

	AudioHandle prepHandle = m_prepSoundHandle;
	((ClientSubsystem *)TheAudio)->removeAudioEvent(prepHandle);
	((ClientSubsystem *)TheAudio)->removeAudioEvent(m_packSoundHandle);
	m_packSoundHandle = 1;
	endPreparation();

	SpecialPowerModuleInterface *spm = obj->getSpecialPowerModule(data->m_specialPowerTemplate);
	if (spm)
		spm->onSpecialAbilityExit();

	switch (data->m_specialPowerTemplate->getSpecialPowerType())
	{
	case 0x66:
		{
			static const NameKeyType key = TheNameKeyGenerator->nameToKey("AutoHealBehavior");
			Module *heal = obj->findModule(key);
			if (heal)
				((UpdateModule *)heal)->resetWakeState();
		}
		break;

	case 0x27:
	case 0x28:
		{
			Object *target = TheGameLogic->findObjectByID(m_targetID);
			obj->m_field3a0 = 0;
			if (target)
			{
				target->clearStatus(OBJECT_STATUS_3E);
				if (m_field24 == 1)
				{
					if (target->isKindOf(KINDOF_6))
					{
						target->setModelConditionState(26);
					}
					else if (target->isKindOf(KINDOF_83) && (*(volatile UnsignedInt *)&obj->m_modelConditionWord124 & 0x40))
					{
						obj->m_modelConditionWord124 &= ~0x40;
						obj->notifyModelConditionChanged();
					}

					if (m_flagsD4 & 0x4000)
					{
						Rva002A8540Container *contain = obj->m_field1fc;
						Rva002A8540Body *body = obj->m_field200;
						if (contain)
						{
							contain->release(target, data->m_containValue, obj);
							body->setPercent(100.0f, 0);
							dispatchRva001BE220((Rva001BE220Receiver *)obj, data->m_specialConditionType, data->m_specialConditionFrames);
							dispatchRva001BE220((Rva001BE220Receiver *)target, data->m_specialConditionType, data->m_specialConditionFrames);
							if (obj->m_ai)
								obj->m_ai->m_commandInterface.rva001F1370(data->m_specialConditionFrames, CMD_FROM_AI);
						}
					}
				}
			}
		}
		break;
	}

	if (aborted)
	{
		if (data->m_paralyzeWhenAborted && ai)
			ai->m_commandInterface.rva001F1370(data->m_paralyzeWhenAborted, CMD_FROM_AI);
	}
	else if (data->m_paralyzeWhenCompleted && ai)
		ai->m_commandInterface.rva001F1370(data->m_paralyzeWhenCompleted, CMD_FROM_AI);

	if (!data->m_specialObjectsPersistent || cleanup && !data->m_specialObjectsPersistWhenOwnerDies)
		killSpecialObjects();

	if (m_fieldE4)
	{
		if (obj->m_ai)
			obj->m_ai->m_commandInterface.aiIdle(CMD_FROM_AI);
		m_fieldE4 = false;
	}
	if (!m_fieldDE)
		m_active = false;
	m_withinStartAbilityRange = false;
	m_packingState = 0;
	m_fieldE5 = false;

	if (data->m_killAttributeModifierOnExit)
	{
		Rva002A8540StringData *const *name = &data->m_attributeModifier;
		if (*name && (*name)->m_length)
			((BfmeOwnerXI *)obj)->bfmeSendXI((BfmeMsgXI *)name);
	}
}
