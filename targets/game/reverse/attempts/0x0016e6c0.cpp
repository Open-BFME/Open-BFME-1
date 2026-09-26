// ?startMoveSound@AIInternalMoveToState@@AAEXXZ
// partial score=0.45 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "Common/AudioEventRTS.h"
#include "GameLogic/Module/BodyModule.h"

// The indexed accessor is the BFME body already owned by
// ThingTemplateSounds.cpp.  The public ZH header exposes only inline named
// accessors, which cannot reproduce BFME's call to getSound(index).
class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int index) const;
};

struct BfmeStartMoveSoundObject
{
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
	virtual const ThingTemplate *getTemplate() const = 0;
	UnsignedByte padToID[0x70];
	ObjectID id;
	UnsignedByte padToBody[0x188];
	BodyModuleInterface *body;
};

struct BfmeStartMoveSoundMachine
{
	UnsignedByte padToOwner[0x10];
	BfmeStartMoveSoundObject *owner;
};

struct BfmeStartMoveSoundState
{
	UnsignedByte padToMachine[0x1c];
	BfmeStartMoveSoundMachine *machine;
};

struct BfmeStartMoveSoundAudio
{
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
	virtual AudioHandle addAudioEvent(const AudioEventRTS *eventToAdd) = 0;
};

extern void *TheAudioClientUpdate;

class AIInternalMoveToState
{
	void startMoveSound(void);
};

// ?startMoveSound@AIInternalMoveToState@@AAEXXZ
void AIInternalMoveToState::startMoveSound(void)
{
	BfmeStartMoveSoundObject *obj =
		((BfmeStartMoveSoundState *)this)->machine->owner;
	const BodyModuleInterface *objBody = obj->body;
	const ThingTemplate *objTemplate = obj->getTemplate();
	if (objBody && IS_CONDITION_WORSE(objBody->getDamageState(), BODY_DAMAGED))
	{
		AudioEventRTS soundEventMoveDamaged = *objTemplate->getSound(0x54);
		if (!soundEventMoveDamaged.getEventName().isEmpty())
		{
			soundEventMoveDamaged.setObjectID(obj->id);
			((BfmeStartMoveSoundAudio *)TheAudioClientUpdate)->addAudioEvent(
				&soundEventMoveDamaged);
		}
		else
		{
			soundEventMoveDamaged = *objTemplate->getSound(0x56);
			if (!soundEventMoveDamaged.getEventName().isEmpty())
			{
				soundEventMoveDamaged.setObjectID(obj->id);
				*(AudioHandle *)((UnsignedByte *)this + 0x40) =
					((BfmeStartMoveSoundAudio *)TheAudioClientUpdate)->addAudioEvent(
						&soundEventMoveDamaged);
			}
		}
	}
	else
	{
		AudioEventRTS soundEventMove = *objTemplate->getSound(0x53);
		soundEventMove.setObjectID(obj->id);

		if (!soundEventMove.getEventName().isEmpty())
		{
			((BfmeStartMoveSoundAudio *)TheAudioClientUpdate)->addAudioEvent(
				&soundEventMove);
		}
		else
		{
			soundEventMove = *objTemplate->getSound(0x55);
			soundEventMove.setObjectID(obj->id);
			if (!soundEventMove.getEventName().isEmpty())
			{
				*(AudioHandle *)((UnsignedByte *)this + 0x40) =
					((BfmeStartMoveSoundAudio *)TheAudioClientUpdate)->addAudioEvent(
						&soundEventMove);
			}
		}
	}
}
