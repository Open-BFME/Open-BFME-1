// ?Rva002A71E0@SpecialAbilityUpdate@@QAE_NXZ
// partial score=0.25 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;
enum Relationship { ALLIES = 2 };
class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

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
	virtual ~AudioEventRTS();
	AudioEventRTS(const AudioEventRTS &source);
	void setObjectID(ObjectID id);

private:
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

class RGBColor
{
public:
	void rva0002cdc7(Int value);
private:
	UnsignedInt m_value;
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
	Overridable *friend_getFinalOverride();
	void *m_vtable;
	Overridable *m_nextOverride;
};

class SpecialPowerTemplate : public Overridable
{
public:
	Int rva00040a3e() const;
	unsigned char m_prefix[0x0c];
	Int m_type;
};

class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_prefix[0x1d8];
	SpecialPowerTemplate *m_specialPowerTemplate;
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

class AudioManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual UnsignedInt addAudioEvent(const AudioEventRTS *event);
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual RvaAudioMisc *rvaSlot124();
};

extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
extern AudioManager *TheAudio;
extern const Real Rva00C75334One;

#pragma comment(linker, "/alternatename:?rva002a65c0@SpecialAbilityUpdate@@QAE_NXZ=?j_0004b466@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0002cdc7@RGBColor@@QAEXH@Z=?j_0002cdc7@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000120ad@Drawable@@QAEXAAURGBColor@@M@Z=?j_000120ad@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva0004067e@Drawable@@QAEXPBVRGBColor@@@Z=?j_0004067e@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva00040a3e@SpecialPowerTemplate@@QBEHXZ=?j_00040a3e@@YAXXZ")

class SpecialAbilityUpdate
{
public:
	Bool Rva002A71E0();
	Bool rva002a65c0();
	Bool initLaser(Object *specialObject, Object *target);
	Object *getObject() const { return m_object; }

private:
	void *m_vtable;
	SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_prefix00c[0x9c];
	UnsignedInt m_prepFrames;
	ObjectID m_targetID;
	unsigned char m_prefix0b0[0x1c];
	_STL::list<ObjectID> m_specialObjectIDList;
	unsigned char m_prefix0d4[4];
	Real m_captureFlashPhase;
};

Bool SpecialAbilityUpdate::Rva002A71E0()
{
	SpecialAbilityUpdateModuleData *data = m_moduleData;
	SpecialPowerTemplate *spTemplate = data->m_specialPowerTemplate;
	if (data->m_abilityAbortRange < 10000000.0f)
	{
		if (!rva002a65c0())
			return false;
	}

	SpecialPowerTemplate *resolvedTemplate = spTemplate;
	if (resolvedTemplate->m_nextOverride)
	{
		if (resolvedTemplate->m_nextOverride->m_nextOverride)
		{
			resolvedTemplate = (SpecialPowerTemplate *)
				resolvedTemplate->m_nextOverride->friend_getFinalOverride();
		}
	}

	switch (resolvedTemplate->m_type)
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
				UnsignedInt denominator = data->m_preparationFrames;
				if (denominator < 1)
					denominator = 1;
				Real increment = 1.0f - ((Real)m_prepFrames / denominator);
				m_captureFlashPhase += increment / 3.0f;
				Bool thisPhase = ((Int)m_captureFlashPhase) & 1;
				if (lastPhase && !thisPhase)
				{
					RGBColor myHouseColor;
					myHouseColor.rva0002cdc7((Int)getObject()->getIndicatorColor());
					Real saturation = TheWritableGlobalData->m_selectionFlashSaturationFactor;
					targetDraw->rva000120ad(myHouseColor, saturation);
					targetDraw->rva0004067e(&myHouseColor);
					AudioEventRTS defectorTimerSound =
						TheAudio->rvaSlot124()->m_defectorTimerTickSound;
					defectorTimerSound.setObjectID(m_targetID);
					TheAudio->addAudioEvent(&defectorTimerSound);
				}
			}
		}
		break;
	}
	}

	SpecialPowerModuleInterface *spmInterface = getObject()->getSpecialPowerModule(
		data->m_specialPowerTemplate);
	if (spmInterface && spTemplate->rva00040a3e() == 0x1d)
		spmInterface->rvaSlot40();
	return true;
}




