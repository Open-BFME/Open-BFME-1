// ?adjustForLocalization@AudioEventRTS@@IAEXAAVAsciiString@@@Z
// partial score=0.93 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::adjustForLocalization, retail 0x000B3730, 272B.
// Probe 276 vs 272. Prologue (edi=arg, esi=this in str() delay slot) and the
// found-path (filename at reused arg slot, prefix hidden-retval at the push-ecx
// slot, set from eax, dtor prefix, peek-concat leaf, dtor filename) already
// match. Wall: inlined reverseFind must return a pointer so the caller emits
// an extra test eax/je (+4). Putting the loop in this function removes that
// test but swaps esi/edi and drops the peek-concat. Start pointer is edx not
// ecx (lea edx,[eax+8] vs lea ecx). Pin generateFilenamePrefix at ILT
// 0x0003B769 before landing. TheFileSystem is DIR32 0x0134CB48.

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
	__forceinline const char *reverseFind(char c) const
	{
		char seen;
		const char *start = m_data ? &m_data->data[0] : "";
		const char *p = start + (m_data ? m_data->length : 0);
		if (p == start)
			return 0;
		while (p != start)
		{
			seen = p[-1];
			--p;
			if (seen == c)
				return p;
		}
		return 0;
	}

protected:
	const StringHeader *m_data;
};

class AsciiString : private StringBase<char>
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
		const char *text = other.m_data ? &other.m_data->data[0] : "";
		concat(text, length);
	}

	const char *str(void)
	{
		return m_data ? m_data->peek() : "";
	}

	const StringHeader *data(void) const
	{
		return m_data;
	}

	__forceinline const char *reverseFind(char c) const
	{
		return StringBase<char>::reverseFind(c);
	}

};

class FileSystem
{
public:
	Bool doesFileExist(const char *filename) const;
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
	if (TheFileSystem->doesFileExist(strToAdjust.str()))
		return;

	if (const char *str = strToAdjust.reverseFind('\\'))
	{
		AsciiString filename = str;
		strToAdjust = generateFilenamePrefix(m_eventInfo->m_soundType, true);
		strToAdjust.concat(filename);
	}
}
