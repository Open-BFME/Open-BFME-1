// cl: /DNDEBUG /MD /EHsc
// Open-BFME: AudioEventRTS::adjustForLocalization, retail 0x000B3730, 272B.

typedef int Int;
typedef bool Bool;

enum AudioType
{
	AT_Music = 0
};

struct StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];

	__forceinline const char *peek(void) const
	{
		return &data[0];
	}
};

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	StringBase() : m_data(0) {}
	~StringBase()
	{
		releaseBuffer();
	}

	void set(const StringBase<T> &other);
	void concat(const char *text, Int length);

	StringHeader *m_data;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
};

extern const char g_bfmeEmptyAscii[];

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void set(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
	}
	AsciiString &operator=(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
		return *this;
	}
	void concat(const char *text, Int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}

	__forceinline void concat(const AsciiString &other)
	{
		const Int length = other.m_data ? other.m_data->length : 0;
		const char *text = other.m_data ? &other.m_data->data[0] : g_bfmeEmptyAscii;
		((StringBase<char> *)this)->concat(text, length);
	}

	const char *str(void) const
	{
		return m_data ? m_data->peek() : g_bfmeEmptyAscii;
	}

	const StringHeader *data(void) const
	{
		return m_data;
	}

	StringBase<char> &base(void)
	{
		return *this;
	}
};

class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

struct AudioEventInfo
{
	char m_pad[0x84];
	AudioType m_soundType;

	__forceinline AudioType getSoundType(void) const
	{
		return m_soundType;
	}
};

class AudioEventRTS
{
public:
	AsciiString generateFilenamePrefix(AudioType audioTypeToPlay, Bool localized);
};

__forceinline AudioType retainAudioType(AudioType type)
{
	return type;
}

class Rva000B3730AudioEventRTS
{
protected:
	void adjustForLocalization(AsciiString &strToAdjust);

	public:
	void *m_vftable;
	int m_filenameToLoad;
	AudioEventInfo *m_eventInfo;
};

// ?adjustForLocalization@AudioEventRTS@@IAEXAAVAsciiString@@@Z
void Rva000B3730AudioEventRTS::adjustForLocalization(AsciiString &strToAdjust)
{
	const char *path = strToAdjust.str();
	if (TheFileSystem->doesFileExist(path))
		return;

	StringBase<char> &string = *(StringBase<char> *)&strToAdjust;
	const char *start = string.m_data ? &string.m_data->data[0]
										: g_bfmeEmptyAscii;
	const StringHeader *data = string.m_data;
	const char *p = start + (data ? data->length : 0);
	for (; p != start; --p)
	{
		char seen = p[-1];
		if (seen == '\\')
		{
			AsciiString filename( p - 1 );
			const AudioEventInfo *eventInfo = m_eventInfo;
			const AudioType audioType = eventInfo->m_soundType;
			strToAdjust = reinterpret_cast<AudioEventRTS *>(this)->generateFilenamePrefix(retainAudioType(audioType), true);
			strToAdjust.concat(filename);
			return;
		}
	}
}
