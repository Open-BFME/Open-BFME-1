// Open-BFME5: ScriptEngine::isAudioComplete, retail 0x0034E5B0, 482 bytes.
// The BFME body uses LOGICFRAMES_PER_MSEC_REAL (5 logic frames per second),
// not the Zero Hour MSEC_PER_LOGICFRAME_REAL division.
// ScriptEngine::m_testingAudio is witnessed at +0x17264 by the retail body;
// this TU-local mirror avoids changing the shared BFME header.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <utility>

typedef float Real;
typedef unsigned int UnsignedInt;
extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

template <class T>
struct BfmeStringHeader
{
	int references;
	unsigned short length;
	unsigned short capacity;
	T data[1];
};

template <class T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &source);
	void set(const StringBase &source);
	void releaseBuffer();

protected:
	BfmeStringHeader<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString() { StringBase<char>::releaseBuffer(); }

	AsciiString &operator=(const AsciiString &that)
	{
		StringBase<char>::set(that);
		return *this;
	}

	int compare(const AsciiString &that) const
	{
		int otherLength = that.m_data ? that.m_data->length : 0;
		const char *otherData = that.m_data ? that.m_data->data : (const char *)0x0107388B;
		int selfLength = m_data ? m_data->length : 0;
		const char *selfData = m_data ? m_data->data : (const char *)0x0107388B;
		int count = selfLength < otherLength ? selfLength : otherLength;
		int result = memcmp(selfData, otherData, count);
		if (result != 0)
			return result;
		return selfLength - otherLength;
	}
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

extern const Real LOGICFRAMES_PER_MSEC_REAL;

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, int extra);
	virtual void slot00();
	~AudioEventRTS();

private:
	unsigned char m_raw[0x6c];
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
	virtual void init() = 0;
	virtual void reset() = 0;
};

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(void *) = 0;
	virtual void xfer(void *) = 0;
};

class Rva0034E5B0ScriptEngine : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Rva0034E5B0ScriptEngine();
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
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual bool isAudioComplete(const AsciiString &completedAudio, bool removeFromList);

private:
	char m_pad[0x1725c];
	ListAsciiStringUINT m_testingAudio;
};

// ?isAudioComplete@ScriptEngine@@UAE_NABVAsciiString@@_N@Z
bool Rva0034E5B0ScriptEngine::isAudioComplete(const AsciiString &testAudio, bool removeFromList)
{
	ListAsciiStringUINTIt findIt;
	for (findIt = m_testingAudio.begin(); findIt != m_testingAudio.end(); ++findIt)
	{
		if (findIt->first == testAudio)
			break;
	}

	if (findIt == m_testingAudio.end())
	{
		PairAsciiStringUINT newPair;
		AudioEventRTS event(testAudio, 0);
		UnsignedInt frameCount = (UnsignedInt)(TheAudioClientUpdate->getAudioLengthMS(&event) * LOGICFRAMES_PER_MSEC_REAL);

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
