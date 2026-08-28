// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of the GenericObjectCreationNugget destructor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	char *m_text;

public:
	~AsciiString();
};

class GenericObjectCreationNuggetNames
{
private:
	void *m_begin;
	void *m_end;
	void *m_capacity;

public:
	~GenericObjectCreationNuggetNames();
};

class GenericObjectCreationNuggetAnimSets
{
private:
	void *m_begin;
	void *m_end;
	void *m_capacity;

public:
	~GenericObjectCreationNuggetAnimSets();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
private:
	unsigned char m_data[0xb0];

public:
	virtual ~AudioEventRTS();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationNugget
{
public:
	virtual ~ObjectCreationNugget() {}
};

class GenericObjectCreationNugget : public ObjectCreationNugget
{
private:
	GenericObjectCreationNuggetNames m_names;
	AsciiString m_putInContainer;
	GenericObjectCreationNuggetAnimSets m_animSets;
	void *m_fxFinal;
	AsciiString m_particleSysName;
	unsigned char m_data[0x58];
	AsciiString m_fadeSoundName;
	unsigned char m_tail[0x10];
	AudioEventRTS m_bounceSound;

protected:
	virtual ~GenericObjectCreationNugget();
};

// ??1GenericObjectCreationNugget@@MAE@XZ
GenericObjectCreationNugget::~GenericObjectCreationNugget()
{
}
