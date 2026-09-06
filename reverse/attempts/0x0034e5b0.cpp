// ?isAudioComplete@ScriptEngine@@UAE_NABVAsciiString@@_N@Z
// partial score=0.9 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /EHa /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "string_base.h"
#include <list>
#include <utility>

typedef float Real;
typedef unsigned int UnsignedInt;
extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString();

	AsciiString &operator=(const AsciiString &that)
	{
		StringBase<char>::set(that);
		return *this;
	}

	int compare(const AsciiString &that) const
	{
		const StringBase<char> *self = (const StringBase<char> *)this;
		const StringBase<char> *other = (const StringBase<char> *)&that;
		int otherLength = other->m_data ? other->m_data->length : 0;
		const char *otherData = other->m_data ? &other->m_data->data[0] : (const char *)"";
		int selfLength = self->m_data ? self->m_data->length : 0;
		const char *selfData = self->m_data ? &self->m_data->data[0] : (const char *)"";
		int count = selfLength < otherLength ? selfLength : otherLength;
		int result = memcmp(selfData, otherData, count);
		if (result != 0)
			return result;
		return selfLength - otherLength;
	}

};

extern const Real MSEC_PER_LOGICFRAME_REAL;

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name);
	~AudioEventRTS();

private:
	unsigned char m_raw[0x70];
};

class ClientSubsystem
{
public:
#define SLOT(n) virtual void slot##n();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71)
	SLOT(72) SLOT(73) SLOT(74) SLOT(75)
	virtual float getAudioLengthMS(const AudioEventRTS *event);
#undef SLOT
};

extern ClientSubsystem *TheAudioClientUpdate;

class GameLogic
{
public:
	unsigned char m_pad[0x3c];
	UnsignedInt m_frame;
	UnsignedInt getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

typedef std::pair<AsciiString, UnsignedInt> PairAsciiStringUINT;
typedef std::list<PairAsciiStringUINT> ListAsciiStringUINT;
typedef ListAsciiStringUINT::iterator ListAsciiStringUINTIt;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class ScriptEngine : public SubsystemInterface, public Snapshot
{
public:
	virtual bool isAudioComplete(const AsciiString &completedAudio, bool removeFromList);

private:
	char m_pad[0x1725c];
	ListAsciiStringUINT m_testingAudio;
};

bool ScriptEngine::isAudioComplete(const AsciiString &testAudio, bool removeFromList)
{
	ListAsciiStringUINTIt findIt;
	for (findIt = m_testingAudio.begin(); findIt != m_testingAudio.end(); ++findIt)
	{
		if (findIt->first.compare(testAudio) == 0)
			break;
	}

	if (findIt == m_testingAudio.end())
	{
		PairAsciiStringUINT newPair;
		AudioEventRTS event(testAudio);
		Real audioLength = TheAudioClientUpdate->getAudioLengthMS(&event);
		UnsignedInt frameCount = (UnsignedInt)(audioLength / MSEC_PER_LOGICFRAME_REAL);

		newPair.first = testAudio;
		newPair.second = frameCount + TheGameLogic->getFrame();
		m_testingAudio.push_front(newPair);
		findIt = m_testingAudio.begin();
	}

	if (TheGameLogic->getFrame() >= findIt->second)
	{
		if (removeFromList)
			m_testingAudio.erase(findIt);
		return true;
	}

	return false;
}
