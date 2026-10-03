// cl: /DNDEBUG /MD /EHsc

struct BfmeJpegState
{
	unsigned char m_pad00[0x16c4];
	int m_messageTableCount;
};

// retail 0x012ED5AC is ?TheGameLODManager@@3PAVGameLODManager@@A; this TU
// keeps its own view of the object and casts at the read.
class GameLODManager;
extern GameLODManager *TheGameLODManager;
// Retail .rdata at 0x01080FC0 contains "1" (31 00), copied bytewise below
// through its terminator. GeneralsMD Common/UserPreferences.cpp also uses
// the literal "1" in QuickMatchPreferences::setMapSelected; no global name
// is proven for this pooled string.
extern const char g_rva01080FC0[2] = "1";
// Retail VA 0x01081238: the two-byte string "0\0" in .rdata. The reference
// GeneralsMD Common/UserPreferences.cpp setter uses the literal "0"; no EA
// global name is evidenced. This matched byte-copy loop reads through its NUL.
extern const char g_rva01081238[] = "0";

void __stdcall bfmeCopyJpegMessage(void *context, char *destination, char suppress)
{
	if (context == 0 && suppress == 0)
	{
		const char *source = g_rva01080FC0;
		if (reinterpret_cast<BfmeJpegState *>(TheGameLODManager)->m_messageTableCount > 1)
			source = g_rva01081238;
		char value;
		do
		{
			value = *source++;
			*destination++ = value;
		} while (value != 0);
	}
}
