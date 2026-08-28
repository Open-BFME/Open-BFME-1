// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of BFME's positional sound FX dispatch.

class AsciiString
{
private:
	void *m_data;
};

enum ObjectID
{
	OBJECT_ID_UNUSED = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D;

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, ObjectID ownerID);
	virtual ~AudioEventRTS();

	void setPosition(const Coord3D *position);

private:
	unsigned char m_pad[0x6C];
};

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
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx,
		float primarySpeed, const Coord3D *secondary) const;

private:
	unsigned char m_pad[0xB0];
	AsciiString m_soundName;
};

void SoundFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *,
	float, const Coord3D *) const
{
	AudioEventRTS sound(m_soundName, OBJECT_ID_UNUSED);

	if (primary)
	{
		sound.setPosition(primary);
	}

	TheAudio->addAudioEvent(&sound);
}
