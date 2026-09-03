// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::generateFilenameExtension, retail 0x000B3630, 193B.
// Empty string, then for every AudioType except AT_Music set "." and concat
// AudioSettings::m_soundsExtension at +0x14 via TheAudio vslot 0x120.

typedef int Int;

enum AudioType
{
	AT_Music = 0
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

	void set(const char *text, Int length);
	void concat(const char *text, Int length);

	void concat(const AsciiString &other)
	{
		const Int length = other.m_data ? other.m_data->length : 0;
		const char *text = other.m_data ? &other.m_data->data[0] : "";
		concat(text, length);
	}

	static const AsciiString TheEmptyString;

private:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

class AudioSettings
{
public:
	char m_pad[0x14];
	AsciiString m_soundsExtension;
};

class AudioManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07)
	V(08) V(09) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
#undef V
	virtual AudioSettings *getAudioSettings(void);
};

extern AudioManager *TheAudio;

class AudioEventRTS
{
public:
	AsciiString generateFilenameExtension(AudioType audioTypeToPlay);
};

// ?generateFilenameExtension@AudioEventRTS@@QAE?AVAsciiString@@W4AudioType@@@Z
AsciiString AudioEventRTS::generateFilenameExtension(AudioType audioTypeToPlay)
{
	AsciiString retStr = AsciiString::TheEmptyString;
	if (audioTypeToPlay != AT_Music)
	{
		retStr.set(".", 1);
		retStr.concat(TheAudio->getAudioSettings()->m_soundsExtension);
	}
	return retStr;
}
