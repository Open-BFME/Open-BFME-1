// ?findByKey@BfmeLivingWorldCampaignManager@@QAEPAVBfmeLwcmFindResult@@PAX@Z
// partial score=0.88 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// PARTIAL 0x003B4590 findByKey 216B
// Wall: MSVC will not emit retail's early mov ebp,ecx / sub esp,0xc / end-then-begin
// load order; every shape that reaches ~210-216B still opens with a direct
// [ecx+0x10] load and a larger frame. Inlined AsciiString compare (empty at
// 0x0107388B, movzx length at +4, repe cmpsb) and 32-byte vector at +0x10 are
// certain. Same family as 0x003B40A0.

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
	Int getLength(void) const { return m_data ? m_data->m_length : 0; }
	const char *str(void) const
	{
		return m_data ? m_data->m_text : g_bfmeEmptyAscii;
	}
	Int compare(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;
		Int diff = memcmp(pThis, pOther, (unsigned int)shorter);
		if (diff == 0)
			diff = lenThis - lenOther;
		return diff;
	}
	bool operator==(const AsciiString &rhs) const { return compare(rhs) == 0; }
	BfmeAsciiStringData *m_data;
};

class BfmeLwcmFindResult
{
public:
	char m_pad00[4];
	AsciiString m_name;
	char m_rest[0x18];
};

class BfmeLivingWorldCampaignManager
{
public:
	BfmeLwcmFindResult *findByKey(void *key);

private:
	char m_pad00[0x10];
	BfmeLwcmFindResult *m_begin;
	BfmeLwcmFindResult *m_end;
};

BfmeLwcmFindResult *BfmeLivingWorldCampaignManager::findByKey(void *key)
{
	BfmeLwcmFindResult *finish = m_end;
	BfmeLwcmFindResult *start = m_begin;
	unsigned int n = (unsigned int)(finish - start);
	if (n == 0)
		return 0;
	const AsciiString query = *(const AsciiString *)key;
	for (unsigned int i = 0; i < n; ++i)
	{
		if (start[i].m_name == query)
			return &start[i];
	}
	return 0;
}
