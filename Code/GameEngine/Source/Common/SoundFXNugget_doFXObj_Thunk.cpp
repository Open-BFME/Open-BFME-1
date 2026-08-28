// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	void *m_data;
};

enum ObjectID
{
	OBJECT_ID_UNUSED = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	int getPlayerIndex() const
	{
		return m_playerIndex;
	}

private:
	unsigned char m_pad[0x24];
	int m_playerIndex;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;

	const Coord3D *getPosition() const
	{
		return &m_cachedPos;
	}

private:
	unsigned char m_pad[0x38];
	Coord3D m_cachedPos;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString& eventName, ObjectID ownerID);
	virtual ~AudioEventRTS();

	void setPlayerIndex(int playerIndex);
	void setPosition(const Coord3D *position);

private:
	unsigned char m_pad[0x6c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual unsigned int addAudioEvent(const AudioEventRTS *event);
};

extern AudioManager *TheAudio;

class SoundFXNugget
{
public:
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	unsigned char m_pad[0xb0];
	AsciiString m_soundName;
};

// ?doFXObj@SoundFXNugget@@UBEXPBVObject@@0@Z
void SoundFXNugget::doFXObj(const Object *primary, const Object *) const
{
	AudioEventRTS sound(m_soundName, OBJECT_ID_UNUSED);
	if (primary)
	{
		sound.setPlayerIndex(primary->getControllingPlayer()->getPlayerIndex());
		sound.setPosition(primary->getPosition());
	}

	TheAudio->addAudioEvent(&sound);
}
