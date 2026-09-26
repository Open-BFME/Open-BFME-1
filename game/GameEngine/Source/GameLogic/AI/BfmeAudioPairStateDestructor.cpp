// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, ObjectID objectID);
	// Non-virtual local view: retail encodes the ILT at 0x00026F35,
	// which the ledger names ??1AudioEventRTS@@QAE@XZ for the body at
	// 0x000B31F0. The vptr the virtual spelling added is folded back
	// into the padding so the layout is unchanged.
	~AudioEventRTS();

private:
	unsigned char m_pad04[0x70];
};

class BfmeAudioPairState
{
public:
	BfmeAudioPairState();
	~BfmeAudioPairState();

private:
	AsciiString m_firstName;
	AsciiString m_secondName;
	AudioEventRTS m_firstEvent;
	AudioEventRTS m_secondEvent;
};

extern AsciiString TheBfmeCrateNameDefault;

BfmeAudioPairState::BfmeAudioPairState() :
	m_firstName(),
	m_secondName(),
	m_firstEvent(TheBfmeCrateNameDefault, INVALID_OBJECT_ID),
	m_secondEvent(TheBfmeCrateNameDefault, INVALID_OBJECT_ID)
{
}

BfmeAudioPairState::~BfmeAudioPairState()
{
}
