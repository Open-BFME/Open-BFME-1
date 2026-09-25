// ?continuePreparation@SpecialAbilityUpdate@@IAE_NXZ
// BFME continuePreparation twin, with current ledger-proven helper declarations.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "ascii_string.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;
enum Relationship { ALLIES = 2 };
class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

extern void j_0004b466();
extern void j_0002cdc7();
extern void j_000120ad();
extern void j_0004067e();
extern void j_00040a3e();

struct Coord3D
{
	UnsignedInt x;
	UnsignedInt y;
	UnsignedInt z;
};

class Counted
{
public:
	long m_refCount;
};

class CountedPtr
{
public:
	Counted *m_ptr;
};

class AudioEventRTS
{
public:
	~AudioEventRTS();
	AudioEventRTS(const AudioEventRTS &source);
	void setObjectID(ObjectID id);

private:
	void *m_vtable;
	AsciiString m_filenameToLoad;
	CountedPtr m_eventInfo;
	UnsignedInt m_playingHandle;
	UnsignedInt m_killThisHandle;
	AsciiString m_eventName;
	AsciiString m_attackName;
	AsciiString m_decayName;
	UnsignedInt m_pitchShift;
	UnsignedInt m_volume;
	UnsignedInt m_timeOfDay;
	UnsignedInt m_objectID;
	Int m_ownerType;
	Coord3D m_position;
	unsigned char m_shouldFade;
	unsigned char m_isLogicalAudio;
	unsigned char m_uninterruptable;
	unsigned char m_flag43;
	unsigned char m_flag44;
	unsigned char m_flag45;
	unsigned char m_flag46;
	unsigned char m_flag47;
	unsigned char m_flag48;
	unsigned char m_flag49;
	unsigned char m_pad4A[2];
	UnsignedInt m_float4C;
	UnsignedInt m_volumeShift;
	UnsignedInt m_delay;
	UnsignedInt m_int58;
	UnsignedInt m_playerIndex;
	UnsignedInt m_portionToPlayNext;
	UnsignedInt m_loopCount;
	UnsignedInt m_int68;
	AsciiString m_tail;
};

#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")

class RGBColor
{
public:
	void rva0002cdc7(Int value);
private:
	Real m_red;
	Real m_green;
	Real m_blue;
};

class Drawable
{
public:
	void rva000120ad(RGBColor &color, Real saturation);
	void rva0004067e(const RGBColor *color);
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
	virtual Drawable *getDrawable();
	Relationship getRelationship(const Object *other) const;
	UnsignedInt getIndicatorColor() const;
	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *power) const;
};

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->m_nextOverride
				? m_nextOverride->m_nextOverride->friend_getFinalOverride()
				: m_nextOverride;
		return this;
	}
	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	Int getSpecialPowerType() const
	{
		SpecialPowerTemplate *self = const_cast<SpecialPowerTemplate *>(this);
		return ((const SpecialPowerTemplate *)self->friend_getFinalOverride())->m_type;
	}
	Int rva00040a3e() const;
	unsigned char m_prefix[0x0c];
	Int m_type;
};

class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_prefix[0x1d8];
	const SpecialPowerTemplate *m_specialPowerTemplate;
	unsigned char m_prefix1dc[0x14];
	Real m_abilityAbortRange;
	unsigned char m_prefix1f4[0x18];
	UnsignedInt m_preparationFrames;
	unsigned char m_prefix210[0x37];
	Bool m_doCaptureFX;
};

class SpecialPowerModuleInterface
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
	virtual void rvaSlot40();
};

class GlobalData
{
public:
	unsigned char m_prefix[0xbf0];
	Real m_selectionFlashSaturationFactor;
};

class RvaAudioMisc
{
public:
	unsigned char m_prefix[0x230];
	AudioEventRTS m_defectorTimerTickSound;
};

class ClientSubsystem
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3c();
	virtual void slot40();
	virtual UnsignedInt addAudioEvent(AudioEventRTS *event);
	#define CLIENT_SUBSYSTEM_PAD(n) virtual void pad##n();
	CLIENT_SUBSYSTEM_PAD(18) CLIENT_SUBSYSTEM_PAD(19)
	CLIENT_SUBSYSTEM_PAD(20) CLIENT_SUBSYSTEM_PAD(21)
	CLIENT_SUBSYSTEM_PAD(22) CLIENT_SUBSYSTEM_PAD(23)
	CLIENT_SUBSYSTEM_PAD(24) CLIENT_SUBSYSTEM_PAD(25)
	CLIENT_SUBSYSTEM_PAD(26) CLIENT_SUBSYSTEM_PAD(27)
	CLIENT_SUBSYSTEM_PAD(28) CLIENT_SUBSYSTEM_PAD(29)
	CLIENT_SUBSYSTEM_PAD(30) CLIENT_SUBSYSTEM_PAD(31)
	CLIENT_SUBSYSTEM_PAD(32) CLIENT_SUBSYSTEM_PAD(33)
	CLIENT_SUBSYSTEM_PAD(34) CLIENT_SUBSYSTEM_PAD(35)
	CLIENT_SUBSYSTEM_PAD(36) CLIENT_SUBSYSTEM_PAD(37)
	CLIENT_SUBSYSTEM_PAD(38) CLIENT_SUBSYSTEM_PAD(39)
	CLIENT_SUBSYSTEM_PAD(40) CLIENT_SUBSYSTEM_PAD(41)
	CLIENT_SUBSYSTEM_PAD(42) CLIENT_SUBSYSTEM_PAD(43)
	CLIENT_SUBSYSTEM_PAD(44) CLIENT_SUBSYSTEM_PAD(45)
	CLIENT_SUBSYSTEM_PAD(46) CLIENT_SUBSYSTEM_PAD(47)
	CLIENT_SUBSYSTEM_PAD(48) CLIENT_SUBSYSTEM_PAD(49)
	CLIENT_SUBSYSTEM_PAD(50) CLIENT_SUBSYSTEM_PAD(51)
	CLIENT_SUBSYSTEM_PAD(52) CLIENT_SUBSYSTEM_PAD(53)
	CLIENT_SUBSYSTEM_PAD(54) CLIENT_SUBSYSTEM_PAD(55)
	CLIENT_SUBSYSTEM_PAD(56) CLIENT_SUBSYSTEM_PAD(57)
	CLIENT_SUBSYSTEM_PAD(58) CLIENT_SUBSYSTEM_PAD(59)
	CLIENT_SUBSYSTEM_PAD(60) CLIENT_SUBSYSTEM_PAD(61)
	CLIENT_SUBSYSTEM_PAD(62) CLIENT_SUBSYSTEM_PAD(63)
	CLIENT_SUBSYSTEM_PAD(64) CLIENT_SUBSYSTEM_PAD(65)
	CLIENT_SUBSYSTEM_PAD(66) CLIENT_SUBSYSTEM_PAD(67)
	CLIENT_SUBSYSTEM_PAD(68) CLIENT_SUBSYSTEM_PAD(69)
	CLIENT_SUBSYSTEM_PAD(70) CLIENT_SUBSYSTEM_PAD(71)
	CLIENT_SUBSYSTEM_PAD(72)
	#undef CLIENT_SUBSYSTEM_PAD
	virtual RvaAudioMisc *getMiscAudio();
};

extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
extern ClientSubsystem *TheAudioClientUpdate;
extern const Real Rva00C75334One;

#pragma comment(linker, "/alternatename:?rva002a65c0@SpecialAbilityUpdate@@QAE_NXZ=?j_0004b466@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0002cdc7@RGBColor@@QAEXH@Z=?j_0002cdc7@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000120ad@Drawable@@QAEXAAURGBColor@@M@Z=?j_000120ad@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0004067e@Drawable@@QAEXPBVRGBColor@@@Z=?j_0004067e@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00040a3e@SpecialPowerTemplate@@QBEHXZ=?j_00040a3e@@YAXXZ")

class SpecialAbilityUpdate
{
public:
	Bool rva002a65c0();
	Bool initLaser(Object *specialObject, Object *target);
	Object *getObject() const { return m_object; }
	SpecialPowerModuleInterface *getMySPM() const
	{
		SpecialAbilityUpdateModuleData *moduleData = m_moduleData;
		Object *object = m_object;
		return object->getSpecialPowerModule(moduleData->m_specialPowerTemplate);
	}

protected:
	Bool continuePreparation();

private:
	void *m_vtable;
	SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_prefix00c[0x9c];
	UnsignedInt m_animFrames;
	ObjectID m_targetID;
	unsigned char m_prefix0b0[0x1c];
	_STL::list<ObjectID> m_specialObjectIDList;
	UnsignedInt m_specialObjectEntries;
	unsigned char m_prefix0d4[4];
	Real m_captureFlashPhase;
};

typedef Bool (SpecialAbilityUpdate::*AbortRangeCall)();
typedef void (RGBColor::*SetColorCall)(Int);
typedef void (Drawable::*SaturateCall)(RGBColor &, Real);
typedef void (Drawable::*FlashCall)(const RGBColor *);
typedef Int (SpecialPowerTemplate::*OutTypeCall)() const;

Bool SpecialAbilityUpdate::continuePreparation()
{
	SpecialAbilityUpdateModuleData *data = m_moduleData;
	const SpecialPowerTemplate *spTemplate = data->m_specialPowerTemplate;
	if (data->m_abilityAbortRange < 10000000.0f)
	{
		union { void (*raw)(void); AbortRangeCall member; } abortRange;
		abortRange.raw = j_0004b466;
		if (!(this->*abortRange.member)())
			return false;
	}

	switch (spTemplate->getSpecialPowerType())
	{
	case 0x15:
	{
		Object *target = TheGameLogic->findObjectByID((Int)m_targetID);
		if (!target)
			return false;
		if (getObject()->getRelationship(target) == 2)
			return false;
		for (_STL::list<ObjectID>::iterator it = m_specialObjectIDList.begin();
			it != m_specialObjectIDList.end(); ++it)
		{
			Object *specialObject = TheGameLogic->findObjectByID((Int)*it);
			if (specialObject && !initLaser(specialObject, target))
				return false;
		}
		return true;
	}
	case 0x1a:
	case 0x1d:
	{
		Object *target = TheGameLogic->findObjectByID((Int)m_targetID);
		if (!target)
			return false;
		if (getObject()->getRelationship(target) == 2)
			return false;
		if (data->m_doCaptureFX)
		{
			Drawable *targetDraw = target->getDrawable();
			if (targetDraw)
			{
				Bool lastPhase = ((Int)m_captureFlashPhase) & 1;
				Real denominator[2];
				denominator[0] = MAX(1, data->m_preparationFrames);
				Real increment = 1.0f - ((Real)m_animFrames / denominator[0]);
				m_captureFlashPhase += increment / 3.0f;
				Bool thisPhase = ((Int)m_captureFlashPhase) & 1;
				if (lastPhase && !thisPhase)
				{
					RGBColor myHouseColor;
					union { void (*raw)(void); SetColorCall member; } setColor;
					setColor.raw = j_0002cdc7;
					(myHouseColor.*setColor.member)(
						(Int)getObject()->getIndicatorColor());
					Real saturation = TheWritableGlobalData->m_selectionFlashSaturationFactor;
					union { void (*raw)(void); SaturateCall member; } saturate;
					saturate.raw = j_000120ad;
					(targetDraw->*saturate.member)(myHouseColor, saturation);
					union { void (*raw)(void); FlashCall member; } flash;
					flash.raw = j_0004067e;
					(targetDraw->*flash.member)(&myHouseColor);
					AudioEventRTS defectorTimerSound =
						TheAudioClientUpdate->getMiscAudio()->m_defectorTimerTickSound;
					defectorTimerSound.setObjectID(m_targetID);
					TheAudioClientUpdate->addAudioEvent(&defectorTimerSound);
				}
			}
		}
		SpecialPowerModuleInterface *spmInterface = getMySPM();
		union { void (*raw)(void); OutTypeCall member; } outType;
		outType.raw = j_00040a3e;
		if (spmInterface && (((SpecialPowerTemplate *)spTemplate)->*outType.member)()
			== 0x1d)
			spmInterface->rvaSlot40();
		break;
	}
	}
	return true;
}
