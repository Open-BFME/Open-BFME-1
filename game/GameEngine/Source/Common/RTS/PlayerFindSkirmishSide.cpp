// ?findSkirmishSide@Player@@QAE_NPAH@Z

#include <string.h>

#pragma intrinsic(memcmp)

typedef bool Bool;

class BFMERetailAsciiString
{
private:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;

	public:
	void releaseBuffer(void);

	int compare(const BFMERetailAsciiString &other) const
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

	bool operator==(const BFMERetailAsciiString &other) const
	{
		return compare(other) == 0;
	}
};

class BfmeStringPresenceValue : public BFMERetailAsciiString
{
public:
	~BfmeStringPresenceValue(void)
	{
		reinterpret_cast<BFMERetailAsciiString *>(this)->releaseBuffer();
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

struct BfmeSkirmishSide
{
	char m_prefix[4];
	BfmeStringPresenceDict m_dict;
};

class BfmeSidesList
{
public:
	char m_prefix[0x32c];
	int m_numSkirmishSides;
	BfmeSkirmishSide m_skirmishSides[1];

	BfmeSkirmishSide *getSkirmishSideInfo(int index)
	{
		if (index >= 0 && index < m_numSkirmishSides)
			return &m_skirmishSides[index];
		return 0;
	}
};

extern BfmeSidesList *TheSidesList;

class Player
{
public:
	Bool findSkirmishSide(int *index);

private:
	char m_prefix[0x1c];
	BFMERetailAsciiString m_playerName;
};

// ?findSkirmishSide@Player@@QAE_NPAH@Z
Bool Player::findSkirmishSide(int *index)
{
	int count = TheSidesList->m_numSkirmishSides;
	*index = 0;
	for (int i = 0; i < count; ++i)
	{
		BfmeStringPresenceValue playerName =
			TheSidesList->getSkirmishSideInfo(i)->m_dict.getAsciiString(
				GenKey0012A7918.fetch(), 0);
		if (playerName == m_playerName)
		{
			*index = i;
			return true;
		}
	}
	return false;
}
