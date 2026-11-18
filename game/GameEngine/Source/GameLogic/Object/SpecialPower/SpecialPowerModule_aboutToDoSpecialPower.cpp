// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// SpecialPowerModule::aboutToDoSpecialPower at 0x00268CB0 (379 bytes, ret 4).
// ilt_oracle CONFIRMS ?aboutToDoSpecialPower@SpecialPowerModule@@IAEXPBVCoord3D@@@Z
// at ILT 0x00046C13; the matched PlayerHealSpecialPower body 0x00263CA0 calls it
// on the module base (interface - 0x10). Zero Hour's body minus the EVA
// announcements: notify the script engine, then play the template's initiate
// sound and, given a location, its initiate-at-target sound.
// The template accessors walk Overridable::friend_getFinalOverride inline;
// retail unrolls that walk twice inside this caller, hence the pinned depth.
#pragma inline_recursion(on)
#pragma inline_depth(3)
#include "ascii_string.h"

class Coord3D;
extern void j_00001e88();
#include "../../../../Include/Common/ObjectID.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable *friend_getFinalOverride(void)
	{
		if (m_next)
			return m_next->friend_getFinalOverride();
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_next;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &);
	~AudioEventRTS();
	void setObjectID(ObjectID id);
	// ILT 0x00001E88 -> 0x000B2210; ilt_oracle confirms the class-tagged
	// ?setPosition@AudioEventRTS@@QAEXPBVCoord3D@@@Z the ledger carries as PBU.
	void setPosition(const Coord3D *pos)
	{
		typedef void (AudioEventRTS::*Fn)(const Coord3D *);
		union {
			void (*raw)();
			Fn member;
		} c;
		c.raw = j_00001e88;
		(this->*c.member)(pos);
	}
	void setPlayerIndex(int playerIndex);

private:
	unsigned char m_unreconstructed[0x70];
};

class SpecialPowerTemplate : public Overridable
{
public:
	AsciiString getName(void) const;
	const AudioEventRTS *getInitiateSound(void) const
	{
		return &((SpecialPowerTemplate *)const_cast<SpecialPowerTemplate *>(this)->friend_getFinalOverride())->m_initiateSound;
	}
	const AudioEventRTS *getInitiateAtTargetSound(void) const
	{
		return &((SpecialPowerTemplate *)const_cast<SpecialPowerTemplate *>(this)->friend_getFinalOverride())->m_initiateAtLocationSound;
	}

private:
	unsigned char m_unreconstructed_08[0x1c];
	AudioEventRTS m_initiateSound;
	AudioEventRTS m_initiateAtLocationSound;
};

class SpecialPowerModuleData
{
public:
	unsigned char m_unreconstructed_00[8];
	const SpecialPowerTemplate *m_specialPowerTemplate;
};

class Player
{
public:
	int getPlayerIndex(void) const { return m_playerIndex; }

private:
	unsigned char m_unreconstructed_00[0x24];
	int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer(void) const;
	ObjectID getID(void) const { return m_id; }

private:
	unsigned char m_unreconstructed_00[0x74];
	ObjectID m_id;
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void notifyOfTriggeredSpecialPower(int playerIndex, const AsciiString &completedPower, ObjectID sourceObj);
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual unsigned addAudioEvent(const AudioEventRTS *eventToAdd);
};

extern ScriptEngine *TheScriptEngine;
extern AudioManager *TheAudio;

class SpecialPowerModule
{
public:
	const SpecialPowerModuleData *getSpecialPowerModuleData(void) const { return m_moduleData; }
	Object *getObject(void) const { return m_object; }

protected:
	void aboutToDoSpecialPower(const Coord3D *location);

private:
	void *m_vtable;
	const SpecialPowerModuleData *m_moduleData;
	Object *m_object;
};

void SpecialPowerModule::aboutToDoSpecialPower(const Coord3D *location)
{
	// Tell the scripting engine!
	TheScriptEngine->notifyOfTriggeredSpecialPower(
		getObject()->getControllingPlayer()->getPlayerIndex(),
		getSpecialPowerModuleData()->m_specialPowerTemplate->getName(),
		getObject()->getID());

	// get module data
	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();

	// play our initiate sound if we have one
	AudioEventRTS audioEvent = *modData->m_specialPowerTemplate->getInitiateSound();
	audioEvent.setObjectID(getObject()->getID());
	TheAudio->addAudioEvent(&audioEvent);

	// play sound at target location if specified
	if (location)
	{
		AudioEventRTS soundAtLocation = *modData->m_specialPowerTemplate->getInitiateAtTargetSound();
		soundAtLocation.setPosition(location);
		soundAtLocation.setPlayerIndex(getObject()->getControllingPlayer()->getPlayerIndex());
		TheAudio->addAudioEvent(&soundAtLocation);
	}
}
