// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// SpecialAbilityUpdate's retail destructor has a BFME-specific multiple
// inheritance and member layout.  Keep the recovered view in the proper
// source family rather than changing shared module headers.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <bitset>

class Object;
class SpecialAbilityUpdateModuleData;

class Gen_dtor_00113f20
{
public:
	virtual ~Gen_dtor_00113f20();

protected:
	SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_object;
};

class SpecialAbilityUpdateBaseInterface1
{
public:
	virtual void slot();
};

class SpecialAbilityUpdateBaseInterface2
{
public:
	virtual void slot();

private:
	unsigned char m_pad[0xC];
};

class SpecialAbilityUpdateObjectModule : public Gen_dtor_00113f20
{
};

class SpecialAbilityUpdateBehaviorModule : public SpecialAbilityUpdateObjectModule,
	public SpecialAbilityUpdateBaseInterface1
{
public:
	virtual ~SpecialAbilityUpdateBehaviorModule() {}
};

class SpecialAbilityUpdateUpdateModule : public SpecialAbilityUpdateBehaviorModule,
	public SpecialAbilityUpdateBaseInterface2
{
public:
	virtual ~SpecialAbilityUpdateUpdateModule() {}
};

class SpecialAbilityUpdateInterface
{
public:
	virtual void slot();
};

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef unsigned int AudioHandle;
typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

template<int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };

	BitFlags() { }
	BitFlags(BogusInitType, int bit) { m_bits.set(bit); }
	BitFlags(BogusInitType, int bit1, int bit2)
	{
		m_bits.set(bit1);
		m_bits.set(bit2);
	}
	BitFlags(BogusInitType, int bit1, int bit2, int bit3)
	{
		m_bits.set(bit1);
		m_bits.set(bit2);
		m_bits.set(bit3);
	}
	void set(int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;
class AutoHealBehavior;
class OCLUpdate;
class Object;
class SpecialAbilityUpdateModuleData;

class AIUpdateInterface
{
public:
	unsigned char m_unmodelled_000[0x338];
	unsigned char m_isInUpdate;
};

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &, Bool set = true);
	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *) const;
	OCLUpdate *findUpdateModule(NameKeyType);

	unsigned char m_unmodelled_000[0x118];
	UnsignedInt m_modelConditionWord0;
	unsigned char m_unmodelled_11c[0x124 - 0x11c];
	UnsignedInt m_modelConditionWord1;
	unsigned char m_unmodelled_128[0x1fc - 0x128];
	void *m_field1fc;
	void *m_field200;
	void *m_ai;
	unsigned char m_unmodelled_208[0x3a0 - 0x208];
	UnsignedInt m_field3a0;
};

class GameLogic
{
};

extern GameLogic *TheGameLogic;

class SpecialPowerModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void invoke() = 0;
};

class RvaField1FC
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void dispatch(Object *, UnsignedInt, Object *) = 0;
};

class RvaField200
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void call(Real value, UnsignedInt mode) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();

private:
	unsigned char m_data[0x6c];
};

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

extern ClientSubsystem *TheAudioClientUpdate;

static __forceinline AudioHandle getPlayingHandle(const AudioEventRTS *audio)
{
	return *reinterpret_cast<const AudioHandle *>(
		reinterpret_cast<const unsigned char *>(audio) + 0x0c);
}

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();
	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_08[0x0c];
	UnsignedInt m_specialPowerType;
};

class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[0x1c8];
	UnsignedInt m_field1c8;
	UnsignedInt m_field1cc;
	UnsignedInt m_field1d0;
	UnsignedInt m_field1d4;
	const SpecialPowerTemplate *m_specialPowerTemplate;
	unsigned char m_unmodelled_1dc[0x1e8 - 0x1dc];
	void *m_field1e8;
	unsigned char m_unmodelled_1ec[0x228 - 0x1ec];
	UnsignedInt m_field228;
	UnsignedInt m_field22c;
	unsigned char m_unmodelled_230[0x241 - 0x230];
	UnsignedByte m_specialObjectsPersistent;
	UnsignedByte m_field242;
	UnsignedByte m_specialObjectsPersistWhenOwnerDies;
	unsigned char m_unmodelled_244[0x24b - 0x244];
	UnsignedByte m_field24b;
};

struct BfmeNoArgCall
{
	void call();
};

struct BfmeOneArgCall
{
	void call(UnsignedInt);
};

struct BfmeTwoArgCall
{
	void call(UnsignedInt, UnsignedInt);
};

struct BfmeFindObjectCall
{
	Object *call(UnsignedInt);
};

struct BfmeGetSpecialPowerCall
{
	SpecialPowerModuleInterface *call(const SpecialPowerTemplate *);
};

struct BfmeKindOfCall
{
	Bool call(UnsignedInt);
};

struct BfmeOnePointerCall
{
	void call(void *);
};

#define BFME_CALL_NOARG(type, receiver, callee) \
	do { typedef void (type::*Function)(); \
	union { void (*raw)(); Function member; } fn; \
	fn.raw = callee; (reinterpret_cast<type *>(receiver)->*fn.member)(); } while (0)

#define BFME_CALL_ONEARG(type, receiver, callee, arg) \
	do { typedef void (type::*Function)(UnsignedInt); \
	union { void (*raw)(); Function member; } fn; \
	fn.raw = callee; (reinterpret_cast<type *>(receiver)->*fn.member)(arg); } while (0)

#define BFME_CALL_TWOARG(type, receiver, callee, arg1, arg2) \
	do { typedef void (type::*Function)(UnsignedInt, UnsignedInt); \
	union { void (*raw)(); Function member; } fn; \
	fn.raw = callee; (reinterpret_cast<type *>(receiver)->*fn.member)(arg1, arg2); } while (0)

#define BFME_CALL_ONEPTR(type, receiver, callee, arg) \
	do { typedef void (type::*Function)(void *); \
	union { void (*raw)(); Function member; } fn; \
	fn.raw = callee; (reinterpret_cast<type *>(receiver)->*fn.member)(arg); } while (0)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate : public SpecialAbilityUpdateUpdateModule,
	public SpecialAbilityUpdateInterface
{
public:
	virtual ~SpecialAbilityUpdate();

private:
	void onExit(bool, bool);

	UnsignedInt m_field24;
	UnsignedInt m_field28;
	UnsignedInt m_field2c;
	UnsignedInt m_field30;
	AudioEventRTS m_prepSoundLoop;
	UnsignedInt m_prepFrames;
	UnsignedInt m_animFrames;
	UnsignedInt m_targetID;
	UnsignedInt m_targetX;
	UnsignedInt m_targetY;
	UnsignedInt m_targetZ;
	UnsignedInt m_locationCount;
	UnsignedInt m_preList0;
	UnsignedInt m_preList1;
	UnsignedInt m_preList2;
	_STL::list<int> m_specialObjectIDList;
	UnsignedInt m_specialObjectEntries;
	UnsignedInt m_fieldD4;
	UnsignedInt m_packingState;
	UnsignedByte m_fieldDC;
	UnsignedByte m_fieldDD;
	UnsignedByte m_fieldDE;
	UnsignedByte m_fieldDF;
	UnsignedByte m_fieldE0;
	UnsignedByte m_fieldE1;
	UnsignedByte m_fieldE2;
	UnsignedByte m_fieldE3;
	UnsignedByte m_fieldE4;
	UnsignedByte m_fieldE5;

	SpecialAbilityUpdateModuleData *getModuleData() const
	{
		return m_moduleData;
	}

	Object *getObject() const
	{
		return m_object;
	}
};

// ??1SpecialAbilityUpdate@@UAE@XZ
SpecialAbilityUpdate::~SpecialAbilityUpdate()
{
	onExit(true, true);
}

extern void j_0001ef9c();
extern void j_0001f253();
extern void j_00020c89();
extern void j_0002191d();
extern void j_0002333a();
extern void j_00024d70();
extern void j_0002852e();
extern void j_00031f7a();
extern void j_0003251f();
extern void j_00035706();
extern void j_000359bd();
extern void j_000401bf();
extern void j_000434c3();
extern void j_0001336d();

// ?onExit@SpecialAbilityUpdate@@AAEX_N0@Z
void SpecialAbilityUpdate::onExit(bool cleanup, bool aborted)
{
	void *ai;
	register Object *object = getObject();
	register const SpecialAbilityUpdateModuleData *data = getModuleData();

	j_0002333a();
	object->setStatus(
		ObjectStatusMaskType(ObjectStatusMaskType::kInit, 23, 24, 37), false);

	ai = object->m_ai;
	if (ai != 0)
	{
		*((unsigned char *)ai + 0x338) = 0;
		BFME_CALL_NOARG(BfmeNoArgCall, ai, j_000359bd);
	}

	TheAudioClientUpdate->removeAudioEvent(getPlayingHandle(&m_prepSoundLoop));
	m_prepFrames = 1;
	BFME_CALL_NOARG(BfmeNoArgCall, this, j_00020c89);

	typedef SpecialPowerModuleInterface *
		(BfmeGetSpecialPowerCall::*GetSpecialPowerFunction)(
			const SpecialPowerTemplate *);
	union { void (*raw)(); GetSpecialPowerFunction member; }
		getSpecialPowerCast;
	getSpecialPowerCast.raw = j_000401bf;
	SpecialPowerModuleInterface *specialPowerModule =
		(reinterpret_cast<BfmeGetSpecialPowerCall *>(object)->*
			getSpecialPowerCast.member)(data->m_specialPowerTemplate);
	if (specialPowerModule != 0)
		specialPowerModule->invoke();

	const SpecialPowerTemplate *specialPowerTemplate =
		data->m_specialPowerTemplate;
	Overridable *overrideTemplate = specialPowerTemplate->m_nextOverride;
	if (overrideTemplate != 0)
	{
		if (overrideTemplate->m_nextOverride != 0)
			overrideTemplate =
				overrideTemplate->m_nextOverride->friend_getFinalOverride();
		specialPowerTemplate =
			(const SpecialPowerTemplate *)overrideTemplate;
	}

	switch (specialPowerTemplate->m_specialPowerType)
	{
	case 0x66:
		{
			static const NameKeyType key_AutoHealBehavior =
				NAMEKEY("AutoHealBehavior");
			AutoHealBehavior *autoHeal =
				(AutoHealBehavior *)object->findUpdateModule(
					key_AutoHealBehavior);
			if (autoHeal != 0)
				BFME_CALL_NOARG(BfmeNoArgCall, autoHeal, j_00035706);
		}
		break;

	case 0x27:
	case 0x28:
		{
			typedef Object *(BfmeFindObjectCall::*FindObjectFunction)(
			UnsignedInt);
			union { void (*raw)(); FindObjectFunction member; }
				findObjectCast;
			findObjectCast.raw = j_0001f253;
			Object *target =
				(reinterpret_cast<BfmeFindObjectCall *>(TheGameLogic)->*
					findObjectCast.member)(m_targetID);
			object->m_field3a0 = 0;
			if (target != 0)
			{
				BFME_CALL_ONEARG(BfmeOneArgCall, target, j_00031f7a, 0x3e);
				if (m_field24 == 1)
				{
					typedef Bool (BfmeKindOfCall::*KindOfFunction)(UnsignedInt);
					union { void (*raw)(); KindOfFunction member; }
						kindOfCast;
					kindOfCast.raw = j_0003251f;
					if ((reinterpret_cast<BfmeKindOfCall *>(target)->*
						kindOfCast.member)(6))
					{
						UnsignedInt flags = target->m_modelConditionWord0;
						if ((flags & 0x04000000) == 0)
						{
							flags |= 0x04000000;
							target->m_modelConditionWord0 = flags;
							BFME_CALL_NOARG(BfmeNoArgCall, target, j_0002191d);
						}
					}
					else if ((reinterpret_cast<BfmeKindOfCall *>(target)->*
						kindOfCast.member)(0x83) &&
						(object->m_modelConditionWord1 & 0x40) != 0)
					{
						object->m_modelConditionWord1 &= ~0x40u;
						BFME_CALL_NOARG(BfmeNoArgCall, object, j_0002191d);
					}
				}

				UnsignedInt captureFlags = m_fieldD4;
				if ((captureFlags & 0x4000) != 0)
				{
					RvaField1FC *field1fc =
						(RvaField1FC *)object->m_field1fc;
					void *field200 = object->m_field200;
					if (field1fc != 0)
					{
						field1fc->dispatch(target, data->m_field1d0, object);
						RvaField200 *field = (RvaField200 *)field200;
						if (field != 0)
							field->call(100.0f, 0);
						BFME_CALL_TWOARG(BfmeTwoArgCall, object, j_0002852e,
							data->m_field1c8, data->m_field1cc);
						BFME_CALL_TWOARG(BfmeTwoArgCall, target, j_0002852e,
							data->m_field1c8, data->m_field1cc);
						void *targetAI = object->m_ai;
						if (targetAI != 0)
							BFME_CALL_TWOARG(BfmeTwoArgCall,
								(unsigned char *)targetAI + 0x20,
								j_0001336d, data->m_field1cc, 2);
					}
				}
			}
		}
		break;
	}

	UnsignedInt commandValue = aborted ? data->m_field22c : data->m_field228;
	if (commandValue != 0 && ai != 0)
		BFME_CALL_TWOARG(BfmeTwoArgCall, (unsigned char *)ai + 0x20,
			j_0001336d, commandValue, 2);

	if (!data->m_specialObjectsPersistent ||
		(cleanup && !data->m_specialObjectsPersistWhenOwnerDies))
		BFME_CALL_NOARG(BfmeNoArgCall, this, j_000434c3);

	if (m_fieldE4 != 0)
	{
		if (ai != 0)
			BFME_CALL_ONEARG(BfmeOneArgCall, (unsigned char *)ai + 0x20,
				j_00024d70, 2);
		m_fieldE4 = 0;
	}
	if (m_fieldDE == 0)
		m_fieldDC = 0;
	m_fieldE2 = 0;
	m_field30 = 0;
	m_fieldE5 = 0;

	if (data->m_field24b != 0 && data->m_field1e8 != 0 &&
		*((unsigned short *)data->m_field1e8 + 2) != 0)
		BFME_CALL_ONEPTR(BfmeOnePointerCall, object, j_0001ef9c,
			data->m_field1e8);
}
