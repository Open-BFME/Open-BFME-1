// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003C8A50. The 0x003C8880 constructor installs the
// LivingWorldRegionManager vtable, and its vtable-owned 0x003CA0E0 body calls
// this lookup with the manager receiver. The campaign parser builds the +0x30
// vector from 0xF4-byte LivingWorldRegion objects whose vtable names them.

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

struct LivingWorldAsciiStringData
{
	char m_pad00[4];
	unsigned short m_length;
	unsigned short m_pad06;
	char m_text[1];
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

	LivingWorldAsciiStringData *m_data;
};

class BorrowedAsciiStringView
{
public:
	int compare(const AsciiString &that) const
	{
		int thatLength = that.m_data ? that.m_data->m_length : 0;
		const char *thatText = that.m_data ? that.m_data->m_text : g_bfmeEmptyAscii;
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? m_data->m_text : g_bfmeEmptyAscii;
		int length = thisLength < thatLength ? thisLength : thatLength;
		int difference = memcmp(thisText, thatText, length);
		if (difference != 0)
			return difference;
		return thisLength - thatLength;
	}

	LivingWorldAsciiStringData *m_data;
};

class LivingWorldRegion
{
public:
	char m_pad00[4];
	AsciiString m_name;
};

struct LivingWorldRegionCampaign
{
	char m_pad00[0x30];
	LivingWorldRegion **m_begin;
	LivingWorldRegion **m_end;
};

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8A50(const AsciiString &regionName);

private:
	void *m_vtable;
	LivingWorldRegionCampaign *m_currentCampaign;
};

LivingWorldRegion *LivingWorldRegionManager::rva003C8A50(
	const AsciiString &regionName)
{
	LivingWorldRegionCampaign *campaign = m_currentCampaign;
	if (campaign == 0)
		return (LivingWorldRegion *)campaign;

	unsigned int index = 0;
	LivingWorldRegion **begin = campaign->m_begin;
	unsigned int count = (unsigned int)(campaign->m_end - begin);

	if (count > 0)
	{
		BorrowedAsciiStringView query = { regionName.m_data };
		LivingWorldRegion **regionCursor = begin;
		while (index < count)
		{
			LivingWorldRegion *candidate = *regionCursor;
			if (query.compare(candidate->m_name) == 0)
				return begin[index];

			++index;
			++regionCursor;
		}
	}

	return 0;
}
