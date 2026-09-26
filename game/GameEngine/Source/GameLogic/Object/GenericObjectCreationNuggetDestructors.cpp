// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Complete destructor 0x001D8220 also emits protected scalar wrapper 0x001D81F0.
// Constructor 0x001D7D70, the parser, and named asset methods establish class
// identity; wrapper ILT 0x0004706E reaches this complete teardown.

#include "ascii_string.h"

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
private:
	unsigned char m_data[0xb4];

public:
	// Non-virtual local view: retail encodes the ILT at 0x00026F35,
	// which the ledger names ??1AudioEventRTS@@QAE@XZ for the body at
	// 0x000B31F0. The vptr the virtual spelling added is folded back
	// into the padding so the layout is unchanged.
	~AudioEventRTS();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
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
