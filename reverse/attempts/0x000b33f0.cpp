// ?generateFilenamePrefix@AudioEventRTS@@QAE?AVAsciiString@@W4AudioType@@_N@Z
// partial score=0.91 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::generateFilenamePrefix, retail 0x000B33F0, 429B.
// Localized prefix is "lang\\" + GlobalLanguage+0x1C + "\\", then audioRoot,
// "\\", the type folder, and a trailing "\\". Folder 2/4 inline-peek concat;
// folders 0/1/3 call StringBase::concat(const StringBase&).

typedef int Int;

enum AudioType
{
	AT_Music = 0,
	AT_Streaming = 1,
	AT_SoundEffect = 2,
	AT_AmbientStream = 3,
	AT_SoundEffectAlt = 4
};

struct StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

template <typename T> class StringBase
{
public:
	void concat(const StringBase<T> &other);
	void concat(const T *text, Int length);

	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	friend class AsciiString;

	private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	StringBase<char>::Header *getData() const { return m_data; }

	void concat(const AsciiString &other)
	{
		StringBase<char>::concat(*(const StringBase<char> *)&other);
	}

	void concat(const char *text, Int length)
	{
		StringBase<char>::concat(text, length);
	}

	void concatPeek(const AsciiString &other)
	{
		const Int length = other.m_data ? other.m_data->length : 0;
		const char *text = other.m_data ? &other.m_data->data[0] : "";
		StringBase<char>::concat(text, length);
	}

	private:
};

class AudioSettings
{
public:
	AsciiString m_audioRoot;
	AsciiString m_soundsFolder;
	AsciiString m_musicFolder;
	AsciiString m_streamingFolder;
	AsciiString m_ambientStreams;
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

class GlobalLanguage
{
public:
	char m_pad[0x1C];
	AsciiString m_language;
};

extern AudioManager *TheAudio;
extern GlobalLanguage *TheGlobalLanguageData;

class AudioEventRTS
{
public:
	AsciiString generateFilenamePrefix(AudioType audioTypeToPlay, bool localized);
};

// ?generateFilenamePrefix@AudioEventRTS@@QAE?AVAsciiString@@W4AudioType@@_N@Z
AsciiString AudioEventRTS::generateFilenamePrefix(AudioType audioTypeToPlay, bool localized)
{
	AsciiString retStr;

	if (localized)
	{
		retStr.concat("lang\\", 5);
		retStr.concatPeek(TheGlobalLanguageData->m_language);
		retStr.concat("\\", 1);
	}

	retStr.concatPeek(TheAudio->getAudioSettings()->m_audioRoot);
	retStr.concat("\\", 1);

	switch (audioTypeToPlay)
	{
	case AT_Music:
		retStr.concat(TheAudio->getAudioSettings()->m_musicFolder);
		break;
	case AT_Streaming:
		retStr.concat(TheAudio->getAudioSettings()->m_streamingFolder);
		break;
	case AT_SoundEffect:
	case AT_SoundEffectAlt:
	{
		const AsciiString &folder = TheAudio->getAudioSettings()->m_soundsFolder;
		const Int length = folder.getData() ? folder.getData()->length : 0;
		if (folder.getData())
			retStr.concat((const char *)folder.getData() + 8, length);
		else
			retStr.concat("", length);
		break;
	}
	case AT_AmbientStream:
		retStr.concat(TheAudio->getAudioSettings()->m_ambientStreams);
		break;
	}

	retStr.concat("\\", 1);
	return retStr;
}
