// cl: /DNDEBUG /MD /EHsc
// readable body of ?startRotOrPitchSound@TurretAI@@AAEXXZ: Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp

typedef unsigned int AudioHandle;
typedef bool Bool;

enum ObjectID {
	INVALID_OBJECT_ID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString {
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS {
public:
	AudioEventRTS &operator=(const AudioEventRTS &that);
	void setPlayingHandle(AudioHandle handle);
	void setObjectID(ObjectID id);
	Bool isCurrentlyPlaying() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate {
public:
	const AudioEventRTS *getPerUnitSound(const AsciiString &name) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object {
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
	virtual const ThingTemplate *getTemplate() const = 0;

	__forceinline ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(reinterpret_cast<const unsigned char *>(this) + 0x74);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager {
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
	virtual void slot0A() = 0;
	virtual void slot0B() = 0;
	virtual void slot0C() = 0;
	virtual void slot0D() = 0;
	virtual void slot0E() = 0;
	virtual void slot0F() = 0;
	virtual void slot10() = 0;
	virtual AudioHandle addAudioEvent(AudioEventRTS *event) = 0;
};

extern AudioManager *TheAudio;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TurretAI.h
class TurretAI {
private:
	void startRotOrPitchSound();

	unsigned char m_gap00[0x10];
	Object *m_owner;
	unsigned char m_gap14[0x0c];
	AudioEventRTS m_turretRotOrPitchSound;
};

// ?startRotOrPitchSound@TurretAI@@AAEXXZ
void TurretAI::startRotOrPitchSound()
{
	if (!m_turretRotOrPitchSound.isCurrentlyPlaying())
	{
		const ThingTemplate *thingTemplate = m_owner->getTemplate();
		if (thingTemplate)
		{
			{
				AsciiString soundName("TurretMoveLoop");
				m_turretRotOrPitchSound = *thingTemplate->getPerUnitSound(soundName);
			}
			m_turretRotOrPitchSound.setObjectID(m_owner->getID());
			m_turretRotOrPitchSound.setPlayingHandle(TheAudio->addAudioEvent(&m_turretRotOrPitchSound));
		}
	}
}
