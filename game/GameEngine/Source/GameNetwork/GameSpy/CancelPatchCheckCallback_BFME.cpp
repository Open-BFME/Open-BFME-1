// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

typedef unsigned char Bool;

#include <list>

class QueuedDownload
{
public:
	~QueuedDownload();
};

struct BfmeThingBHG
{
	char m_bfmeHead[0x259];
	Bool m_bfmeFlag;
};

extern BfmeThingBHG *g_bfmeThingBHG;
extern Bool s_asyncDNSLookupInProgress;
extern volatile Bool reOpenPlayerInfoFlag;
extern Bool checkingForPatchBeforeGameSpy;
extern int checksLeftBeforeOnline;

void b_00042a50();

extern std::list<QueuedDownload> queuedDownloads;
extern char *MOTDBuffer;
extern char *configBuffer;

void CancelPatchCheckCallback(void)
{
	BfmeThingBHG *state = g_bfmeThingBHG;

	s_asyncDNSLookupInProgress = 0;
	if (state)
		state->m_bfmeFlag = 0;

	checkingForPatchBeforeGameSpy = 0;
	checksLeftBeforeOnline = 0;
	if (reOpenPlayerInfoFlag)
	{
		b_00042a50();
		reOpenPlayerInfoFlag = 0;
	}

	queuedDownloads.clear();

	if (MOTDBuffer)
	{
		delete[] MOTDBuffer;
		MOTDBuffer = 0;
	}
	if (configBuffer)
	{
		delete[] configBuffer;
		configBuffer = 0;
	}
}
