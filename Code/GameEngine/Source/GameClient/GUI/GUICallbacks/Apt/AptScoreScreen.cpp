// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x005774E0. Open the BFME score screen after game cleanup and fill
// the screen with the single-player or multiplayer score data.

typedef bool Bool;
typedef int Int;

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

class RecorderClass
{
public:
	RecorderModeType getMode(void);
};

class GameLogic
{
public:
	char m_bfmeHead[0x10C];
	Int m_bfmeMode;
	Bool isInSinglePlayerGame(void);
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class Rva0069AEB0Node
{
public:
	virtual void slot00(void);
	void stop(Int which);
};

class AudioEventRTS : public Rva0069AEB0Node
{
public:
	virtual void slot00(void);
	AudioEventRTS(const AsciiString &eventName, Int extra);
	~AudioEventRTS();

private:
	char m_data[0x6C];
};

class AudioClientUpdate
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void addAudioEvent(AudioEventRTS *event) = 0;
};

class Shell
{
public:
	void push(AsciiString filename, Bool shutdownImmediate = false);
};

class BfmeAptScreenScoreScreen
{
public:
	void _bfme_populateSinglePlayer(void);
	void _bfme_populateMultiPlayer(Int type);
};

extern RecorderClass *TheRecorder;
extern GameLogic *TheBfmeGameLogic;
extern AudioClientUpdate *TheAudioClientUpdate;
extern Shell *TheShell;
extern void *g_obj12F4B50;

// ?_bfme_showScoreScreen@@YA_NXZ
Bool _bfme_showScoreScreen(void)
{
	Int type = 0;

	if (g_obj12F4B50 != 0)
		goto success;

	if (TheRecorder != 0 && TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK)
	{
		type = 4;
	}
	else if (TheBfmeGameLogic->m_bfmeMode == 5)
	{
		type = 3;
	}
	else if (TheBfmeGameLogic->m_bfmeMode == 1)
	{
		type = 2;
	}
	else if (TheBfmeGameLogic->m_bfmeMode == 2)
	{
		type = 1;
	}
	else if (!TheBfmeGameLogic->isInSinglePlayerGame() &&
		TheBfmeGameLogic->m_bfmeMode != 6)
	{
		return false;
	}
	else
	{
		type = 0;
	}

	{
		AudioEventRTS audioEvent(AsciiString("ScoreScreenMusic"), 2);
		audioEvent.stop(1);
		TheAudioClientUpdate->addAudioEvent(&audioEvent);
		TheShell->push(AsciiString("ScoreScreen.apt"), false);

		if (type == 0)
			((BfmeAptScreenScoreScreen *)g_obj12F4B50)->_bfme_populateSinglePlayer();
		else
			((BfmeAptScreenScoreScreen *)g_obj12F4B50)->_bfme_populateMultiPlayer(type);
	}

success:
	return true;
}
