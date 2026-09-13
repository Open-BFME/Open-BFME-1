// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME's Shell::showShellMap keeps the Zero Hour control flow, but uses the
// BFME GlobalData and Shell layouts and drops the blank-window fallback.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

struct BfmeStringData
{
	Int m_refCount;
	unsigned short m_length;
};

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &that);

	Bool isNotEmpty() const
	{
		return m_data != 0 && ((const BfmeStringData *)m_data)->m_length != 0;
	}

private:
	void *m_data;
};

class BfmeGlobalData
{
public:
	unsigned char m_unmodelled000[0xb80];
	AsciiString m_initialFile;
	AsciiString m_pendingFile;
	unsigned char m_unmodelledB88[0xbb0 - 0xb88];
	AsciiString m_shellMapName;
	Bool m_shellMapOn;
};

extern BfmeGlobalData *TheWritableGlobalData;

class BfmeGameLogic
{
public:
	unsigned char m_unmodelled000[0x10c];
	Int m_gameMode;
};

extern BfmeGameLogic *TheBfmeGameLogic;

class Display
{
public:
	void bfmeStopMovie();
};

extern Display *TheDisplay;

extern void j_0004393c();

class BfmeShellAudioRelease
{
public:
	void releaseViaThunk()
	{
		typedef void (BfmeShellAudioRelease::*MemberThunk)();
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_0004393c;
		(this->*thunk.member)();
	}
};

class GameMessage
{
public:
	void appendIntegerArgument(Int value);
};

class MessageStream
{
public:
#define MESSAGE_STREAM_SLOT(n) virtual void slot##n() = 0
	MESSAGE_STREAM_SLOT(00); MESSAGE_STREAM_SLOT(01); MESSAGE_STREAM_SLOT(02);
	MESSAGE_STREAM_SLOT(03); MESSAGE_STREAM_SLOT(04); MESSAGE_STREAM_SLOT(05);
	MESSAGE_STREAM_SLOT(06); MESSAGE_STREAM_SLOT(07); MESSAGE_STREAM_SLOT(08);
	MESSAGE_STREAM_SLOT(09); MESSAGE_STREAM_SLOT(10); MESSAGE_STREAM_SLOT(11);
	MESSAGE_STREAM_SLOT(12);
#undef MESSAGE_STREAM_SLOT
	virtual GameMessage *appendMessage(Int type) = 0;
};

extern MessageStream *TheMessageStream;

class BfmeAudioClient
{
public:
#define AUDIO_SLOT(n) virtual void slot##n() = 0
	AUDIO_SLOT(00); AUDIO_SLOT(01); AUDIO_SLOT(02); AUDIO_SLOT(03);
	AUDIO_SLOT(04); AUDIO_SLOT(05); AUDIO_SLOT(06); AUDIO_SLOT(07);
	AUDIO_SLOT(08); AUDIO_SLOT(09); AUDIO_SLOT(10); AUDIO_SLOT(11);
	AUDIO_SLOT(12); AUDIO_SLOT(13); AUDIO_SLOT(14); AUDIO_SLOT(15);
	AUDIO_SLOT(16); AUDIO_SLOT(17); AUDIO_SLOT(18);
#undef AUDIO_SLOT
	virtual void stopAudioEvent(UnsignedInt handle) = 0;
};

extern BfmeAudioClient *TheAudioClientUpdate;

void InitGameLogicRandom(UnsignedInt seed);

enum BfmeGameMode
{
	BFME_GAME_SHELL = 4,
	BFME_GAME_NONE = 8
};

enum BfmeMessageType
{
	BFME_MSG_CLEAR_GAME_DATA = 0x1d,
	BFME_MSG_NEW_GAME = 0x1e
};

class Shell
{
public:
	Bool showShellMap(Bool useShellMap);

private:
	unsigned char m_unmodelled000[0x4e];
	Bool m_shellMapRequested;
	Bool m_clearBackground;
	unsigned char m_unmodelled050[0x64 - 0x50];
	UnsignedInt m_shellAudioHandle;
};

Bool Shell::showShellMap(Bool useShellMap)
{
	m_shellMapRequested = useShellMap && !TheWritableGlobalData->m_shellMapOn;

	if (TheWritableGlobalData->m_initialFile.isNotEmpty() || TheBfmeGameLogic == 0)
		return false;

	m_clearBackground = false;
	if (useShellMap && TheWritableGlobalData->m_shellMapOn)
	{
		TheDisplay->bfmeStopMovie();
		((BfmeShellAudioRelease *)this)->releaseViaThunk();

		if (TheBfmeGameLogic->m_gameMode == BFME_GAME_SHELL)
			return true;

		if (TheBfmeGameLogic->m_gameMode != BFME_GAME_NONE)
			TheMessageStream->appendMessage(BFME_MSG_CLEAR_GAME_DATA);

		TheWritableGlobalData->m_pendingFile = TheWritableGlobalData->m_shellMapName;
		InitGameLogicRandom(0);
		GameMessage *message = TheMessageStream->appendMessage(BFME_MSG_NEW_GAME);
		message->appendIntegerArgument(BFME_GAME_SHELL);
		return true;
	}
	else
	{
		TheDisplay->bfmeStopMovie();

		if (TheAudioClientUpdate != 0)
		{
			TheAudioClientUpdate->stopAudioEvent(m_shellAudioHandle);
			m_shellAudioHandle = 1;
		}

		if (TheBfmeGameLogic->m_gameMode == BFME_GAME_SHELL)
			TheMessageStream->appendMessage(BFME_MSG_CLEAR_GAME_DATA);

		return false;
	}
}
