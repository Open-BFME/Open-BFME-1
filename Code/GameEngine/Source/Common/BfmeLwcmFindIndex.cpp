// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: index form of BfmeLwcmFindByKey. Retail 0x003B40A0, 203 bytes.
// Same 32-byte record vector at this+0x10 and inlined AsciiString compare
// against the name at record+4; returns the matching index or -1.

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

typedef int Int;
typedef unsigned short UnsignedShort;

struct BfmeAsciiStringData
{
	char m_pad00[4];
	UnsignedShort m_length;
	UnsignedShort m_pad06;
	char m_text[1];
};

class AsciiString
{
public:
	Int compare(const AsciiString &other) const
	{
		const AsciiString *that = &other;
		const AsciiString *self = this;
		Int thatLen = that->m_data ? that->m_data->m_length : 0;
		const char *thatData = that->m_data ? &that->m_data->m_text[0] : g_bfmeEmptyAscii;
		Int thisLen = self->m_data ? self->m_data->m_length : 0;
		const char *thisData = self->m_data ? &self->m_data->m_text[0] : g_bfmeEmptyAscii;
		Int c = memcmp(thisData, thatData, (unsigned int)(thisLen < thatLen ? thisLen : thatLen));
		if (c != 0)
			return c;
		return thisLen - thatLen;
	}
	BfmeAsciiStringData *m_data;
};

class BfmeLwcmFindResult
{
public:
	char m_pad00[4];
	AsciiString m_name;
	char m_rest[0x18];
};

class BfmeVec32
{
public:
	unsigned int size(void) const
	{
		BfmeLwcmFindResult *finish = m_end;
		BfmeLwcmFindResult *start = m_begin;
		return (unsigned int)(finish - start);
	}
	BfmeLwcmFindResult *m_begin;
	BfmeLwcmFindResult *m_end;
};

class BfmeLivingWorldCampaignManager
{
public:
	int findIndex(void *key);

private:
	char m_pad00[0x10];
	BfmeVec32 m_items;
};

int BfmeLivingWorldCampaignManager::findIndex(void *key)
{
	unsigned int i = 0;
	for (; i < m_items.size(); ++i)
	{
		if (m_items.m_begin[i].m_name.compare(*(const AsciiString *)key) == 0)
			return (int)i;
	}
	return -1;
}
