// cl: /DNDEBUG /MD /EHsc

#include <string.h>

#pragma intrinsic(memcmp)

struct BfmeAsciiStringHeader
{
	int references;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

class BfmeStringPresenceValue;

class AsciiString
{
	friend class BfmeStringPresenceValue;

	private:
	BfmeAsciiStringHeader *m_data;

public:
	void releaseBuffer(void);

	~AsciiString(void)
	{
		releaseBuffer();
	}
};

class BfmeStringPresenceValue
{
private:
	BfmeAsciiStringHeader *m_data;

public:
	~BfmeStringPresenceValue(void)
	{
		reinterpret_cast<AsciiString *>(this)->releaseBuffer();
	}

	int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->length : 0;
		const char *otherData = other.m_data ? other.m_data->data : "";
		int thisLength = m_data ? m_data->length : 0;
		const char *thisData = m_data ? m_data->data : "";
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisData, otherData, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	bool operator==(const AsciiString &other) const
	{
		return compare(other) == 0;
	}
};

class GenKey
{
public:
	int fetch(void);
};

class BfmeStringPresenceDict
{
private:
	char m_data[0x14];

public:
	BfmeStringPresenceValue getAsciiString(int key, bool *exists) const;
};

extern GenKey GenKey0012A7918;

class SidesInfo
{
	public:
	char m_prefix[4];
	BfmeStringPresenceDict m_dict;
};

class SidesList
{
public:
	SidesInfo *findSkirmishSideInfo(AsciiString name, int *index = 0);

private:
	char m_prefix[0x32c];
	int m_numSkirmishSides;
	SidesInfo m_skirmishSides[1];
};

// The caller at 0x00196631 reaches this body through ParseTeamsDataChunk.
// The loop uses the SidesList count at +0x32c and records at +0x334.
SidesInfo *SidesList::findSkirmishSideInfo(AsciiString name, int *index)
{
	for (int i = 0; i < m_numSkirmishSides; ++i)
	{
		if (m_skirmishSides[i].m_dict.getAsciiString(GenKey0012A7918.fetch(), 0) == name)
		{
			if (index)
				*index = i;
			return &m_skirmishSides[i];
		}
	}
	return 0;
}
