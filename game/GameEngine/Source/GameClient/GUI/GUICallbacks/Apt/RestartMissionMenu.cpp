// BFME restartMissionMenu at retail RVA 0x00569E10.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2

typedef bool Bool;
typedef int Int;
enum RecorderModeType { RECORDER_MODE_RECORD = 0, RECORDER_MODE_PLAYBACK = 1, RECORDER_MODE_NONE = 2 };

template <class T> class StringBase
{
protected:
	StringBase() {}
	StringBase(const StringBase &other);
	T *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &other)
		: StringBase<char>(other) {}
	~AsciiString() { releaseBuffer(); }
	void set(const AsciiString &other);
	AsciiString &operator=(const AsciiString &other);
	void releaseBuffer();
	Bool isNotEmpty() const
	{
		return m_data != 0 && *((unsigned short *)((char *)m_data + 4)) != 0;
	}
};

extern void bfmeClearAAV(int);

struct BfmeObj947C
{
	char m_head[0x254];
	Bool m_hidden;
	char m_gap[0x25c - 0x255];
	Int m_field25c;
};

class Shell
{
public:
	char m_head[0x50];
	Bool m_isShellActive;
};

class Rva00579160Manager
{
public:
	void notify();
};

class GameState
{
public:
	Bool isInSaveDirectory(const AsciiString &name) const throw();
	AsciiString getPristineMapName() throw();
};

class RecorderClass
{
public:
	AsciiString getCurrentReplayFilename() throw();
	RecorderModeType getMode() throw();
	void stopRecording() throw();
	Bool playbackFile(AsciiString file);
};

class BfmeGameLogicPause
{
public:
	__forceinline Int getGameMode() const { return *(const Int *)((const char *)this + 0x10c); }
	__forceinline Int getRankPointsToAddAtGameStart() const { return *(const Int *)((const char *)this + 0x8c); }
	__forceinline Int getGlobalDifficulty() const { return *(const Int *)((const char *)this + 0x9c); }

	void clearGameData(Bool a, Bool b);
};

class GameEngine
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual Int getFramesPerSecondLimit();
	virtual void setQuitting(Bool quitting);
};

class Glo012F1028Type
{
public:
	void rva0003b313();
};

class GameMessage
{
public:
	void appendIntegerArgument(Int value);
};

class MessageStream
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual GameMessage *appendMessage(Int type);
};

class InGameUI
{
public:
	char m_head[0x12be];
	Bool m_clientQuiet;
};


class GlobalData
{
public:
	char m_head[8];
	AsciiString m_mapName;
	char m_gap[0xb84 - 0xc];
	AsciiString m_pendingFile;
};

extern BfmeObj947C *g_bfme947ObjC;
#define TheShell (*(Shell **)0x012F4B58)
#define TheManager (*(Rva00579160Manager **)0x012F19E8)
#define TheBfmeGameLogic (*(BfmeGameLogicPause **)0x012F0898)
#define TheWritableGlobalData (*(GlobalData **)0x012ED5C8)
#define TheGameState (*(GameState **)0x012EF190)
#define TheRecorder (*(RecorderClass **)0x012ED62C)
#define TheGameEngine (*(GameEngine **)0x012ED524)
#define TheLivingWorldLogic (*(Glo012F1028Type **)0x012F1028)
#define TheMessageStream (*(MessageStream **)0x012ED5EC)
#define TheInGameUI (*(InGameUI **)0x012F148C)

__declspec(noinline) void restartMissionMenu()
{
	BfmeObj947C *menu = g_bfme947ObjC;
	if (menu != 0 && !menu->m_hidden)
	{
		menu->m_hidden = true;
		g_bfme947ObjC->m_field25c = 2;
		TheShell->m_isShellActive = true;
		TheManager->notify();
	}

	Int gameMode = TheBfmeGameLogic->getGameMode();
	AsciiString mapName = TheWritableGlobalData->m_mapName;
	if (TheGameState->isInSaveDirectory(mapName))
		mapName.set(TheGameState->getPristineMapName());

	AsciiString replayFile = TheRecorder->getCurrentReplayFilename();
	if (TheRecorder->getMode() == 0)
		TheRecorder->stopRecording();

	Int rankPointsStartedWith = TheBfmeGameLogic->getRankPointsToAddAtGameStart();
	Int diff = TheBfmeGameLogic->getGlobalDifficulty();
	Int fps = TheGameEngine->getFramesPerSecondLimit();

	TheBfmeGameLogic->clearGameData(false, false);
	TheGameEngine->setQuitting(false);

	if (TheLivingWorldLogic != 0)
		TheLivingWorldLogic->rva0003b313();
	if (replayFile.isNotEmpty())
		TheRecorder->playbackFile(replayFile);
	else
	{
		AsciiString *pendingFile = &TheWritableGlobalData->m_pendingFile;
		pendingFile->set(mapName);
		GameMessage *msg = TheMessageStream->appendMessage(0x1e);
		msg->appendIntegerArgument(gameMode);
		msg->appendIntegerArgument(diff);
		msg->appendIntegerArgument(rankPointsStartedWith);
		msg->appendIntegerArgument(fps);
		bfmeClearAAV(0);
	}
	TheInGameUI->m_clientQuiet = true;
}
