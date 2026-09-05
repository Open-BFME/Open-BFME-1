// ?adjustForLocalization@AudioEventRTS@@IAEXAAVAsciiString@@@Z
// partial score=0.99 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: AudioEventRTS::adjustForLocalization, retail 0x000B3730, 272B.

typedef int Int;
typedef unsigned char Bool;

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
public:
	StringHeader *m_data;
};

extern const char g_bfmeEmptyAscii[];

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *text);
	~AsciiString();

	void set(const AsciiString &other);
	AsciiString &operator=(const AsciiString &other);
	void concat(const char *text, Int length);

	__forceinline void concat(const AsciiString &other)
	{
		const Int length = other.m_data ? other.m_data->length : 0;
		const char *text = other.m_data ? &other.m_data->data[0] : g_bfmeEmptyAscii;
		concat(text, length);
	}

	const char *str(void) const
	{
		return m_data ? m_data->peek() : g_bfmeEmptyAscii;
	}

	const StringHeader *data(void) const
	{
		return m_data;
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
};

class AudioEventRTS
{
protected:
	void adjustForLocalization(AsciiString &strToAdjust);

public:
	AsciiString generateFilenamePrefix(AudioType audioTypeToPlay, bool localized);

	void *m_vftable;
	int m_filenameToLoad;
	AudioEventInfo *m_eventInfo;
};

// ?adjustForLocalization@AudioEventRTS@@IAEXAAVAsciiString@@@Z
void AudioEventRTS::adjustForLocalization(AsciiString &strToAdjust)
{
	const char *path = strToAdjust.str();
	if (TheFileSystem->doesFileExist(path))
		return;

	StringBase<char> &string = strToAdjust;
  const char *start = string.m_data ? &string.m_data->data[0]
                                    : g_bfmeEmptyAscii;
  const StringHeader *data = string.m_data;
  const char *p = start + (data ? data->length : 0);
  for (; p != start; --p)
  {
    char seen = p[-1];
    if (seen == '\\')
    {
			AsciiString filename = p - 1;
			const AudioType audioType = m_eventInfo->m_soundType;
			strToAdjust = generateFilenamePrefix(audioType, true);
			strToAdjust.concat(filename);
      return;
    }
  }
}
