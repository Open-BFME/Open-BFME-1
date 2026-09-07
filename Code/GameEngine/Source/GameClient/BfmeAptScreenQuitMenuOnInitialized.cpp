// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenQuitMenu::_bfme_onInitialized, retail 0x005691D0, 280 bytes.
// The callback disables the Restart action for an active game or playback,
// and disables the campaign Save/Load actions when the campaign state requires
// it.  The callback registration is in BfmeAptScreenQuitMenuConstructor.cpp.

class BfmeH1065;

class GenActionSink
{
public:
	unsigned char *invokeAtLevel( int level, const char *name, int kind,
		const char *value, int a, int b, int c, int d );
};

extern GenActionSink *TheGenActionSink;

int bfmeAptLevel00465CE0( BfmeH1065 *self );

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

class RecorderClass
{
public:
	RecorderModeType getMode();
};

extern RecorderClass *TheRecorder;

class GameLogic
{
public:
	char m_unmodelled[ 0x10C ];
	int m_gameMode;
};

extern GameLogic *TheBfmeGameLogic;

class Glo012F1028Type
{
public:
	char m_unmodelled[ 0x2C ];
	unsigned char m_campaignLoaded;
	unsigned char m_campaignActive;
};

extern Glo012F1028Type *Glo012F1028;

class Rva003BF540
{
public:
	bool allowed();
};

class Gen_00609320
{
public:
	char m_unmodelled[ 4 ];
	void *m_at04;
};

extern Gen_00609320 *g_bfmeStateDF;

class BfmeAptScreenQuitMenu
{
public:
	void _bfme_onInitialized( const char *name );
};

// ?_bfme_onInitialized@BfmeAptScreenQuitMenu@@QAEXPBD@Z
void BfmeAptScreenQuitMenu::_bfme_onInitialized( const char * )
{
	if( TheBfmeGameLogic &&
		( TheBfmeGameLogic->m_gameMode == 1 ||
		  TheBfmeGameLogic->m_gameMode == 5 ) )
		goto disableRestart;

	if( !TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK )
	{
		if( !Glo012F1028 || !Glo012F1028->m_campaignLoaded ||
			!Glo012F1028->m_campaignActive )
			return;

		TheGenActionSink->invokeAtLevel(
			bfmeAptLevel00465CE0( (BfmeH1065 *)this ), "disableButton", 1, "Restart",
			0, 0, 0, 0 );

		if( !((Rva003BF540 *)Glo012F1028)->allowed() )
			goto disableSaveLoad;
		if( g_bfmeStateDF->m_at04 )
			return;
		goto disableSaveLoad;
	}

	disableRestart:
	TheGenActionSink->invokeAtLevel(
		bfmeAptLevel00465CE0( (BfmeH1065 *)this ), "disableButton", 1, "Restart",
			0, 0, 0, 0 );

	/* The retail body jumps over the campaign checks from this path. */
	goto disableSaveLoad;

	disableSaveLoad:
	TheGenActionSink->invokeAtLevel(
		bfmeAptLevel00465CE0( (BfmeH1065 *)this ), "disableButton", 1, "Save",
			0, 0, 0, 0 );
	TheGenActionSink->invokeAtLevel(
			bfmeAptLevel00465CE0( (BfmeH1065 *)this ), "disableButton", 1, "Load",
			0, 0, 0, 0 );
}
