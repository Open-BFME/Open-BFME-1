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
extern char g_bfmeJpegSingleMessage;
extern char g_bfmeJpegExtendedMessage;

void __stdcall bfmeCopyJpegMessage(void *context, char *destination, char suppress)
{
	if (context == 0 && suppress == 0)
	{
		const char *source = &g_bfmeJpegSingleMessage;
		if (reinterpret_cast<BfmeJpegState *>(TheGameLODManager)->m_messageTableCount > 1)
			source = &g_bfmeJpegExtendedMessage;
		char value;
		do
		{
			value = *source++;
			*destination++ = value;
		} while (value != 0);
	}
}
