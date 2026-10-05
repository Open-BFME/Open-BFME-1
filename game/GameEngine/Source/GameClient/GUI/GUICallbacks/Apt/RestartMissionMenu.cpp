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

// The retail global at 0x012F19E8, named by its one linked-build definition
// (WindowManager *g_rva012F19E8WindowManager).  Rva00465B80 is this TU's view
// of the one member reached on it: the 8-byte flag setter matched as
// ?apply@Rva00465B80@@QAEXXZ (retail body 0x00465B80, called through the ILT
// thunk at RVA 0x000290D2); the cast at the use is pointer-size neutral.
class Rva00465B80
{
public:
	void apply();
};

class WindowManager;

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

// This TU's view of the one game-logic object reached on the retail
// singleton at 0x012F0898: three inline field reads plus the two-Bool
// clearGameData, whose pinned retail ILT spelling carries this class name.
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

class BfmeAptScreenQuitMenu;
extern BfmeAptScreenQuitMenu *g_obj12F4B40;

// Retail singleton globals, named per targets/game/reverse/symbols.csv.
extern Shell *TheShell;					// ?TheShell@@3PAVShell@@A @ 0x012F4B58
extern WindowManager *g_rva012F19E8WindowManager;	// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A @ 0x012F19E8
class GameLogic;	// pointer-type only: retail's global is ?TheBfmeGameLogic@@3PAVGameLogic@@A
extern GameLogic *TheBfmeGameLogic;	// @ 0x012F0898
extern GlobalData *TheWritableGlobalData;	// ?TheWritableGlobalData@@3PAVGlobalData@@A @ 0x012ED5C8
extern GameState *TheGameState;			// ?TheGameState@@3PAVGameState@@A @ 0x012EF190
extern RecorderClass *TheRecorder;		// ?TheRecorder@@3PAVRecorderClass@@A @ 0x012ED62C
extern GameEngine *TheGameEngine;		// ?TheGameEngine@@3PAVGameEngine@@A @ 0x012ED524
extern Glo012F1028Type *Glo012F1028;	// ?Glo012F1028@@3PAVGlo012F1028Type@@A @ 0x012F1028
extern MessageStream *TheMessageStream;	// ?TheMessageStream@@3PAVMessageStream@@A @ 0x012ED5EC
extern InGameUI *TheInGameUI;			// ?TheInGameUI@@3PAVInGameUI@@A @ 0x012F148C

#define TheLivingWorldLogic Glo012F1028

__declspec(noinline) void restartMissionMenu()
{
	BfmeObj947C *menu = reinterpret_cast<BfmeObj947C * &>(g_obj12F4B40);
	if (menu != 0 && !menu->m_hidden)
	{
		menu->m_hidden = true;
		reinterpret_cast<BfmeObj947C * &>(g_obj12F4B40)->m_field25c = 2;
		TheShell->m_isShellActive = true;
		((Rva00465B80 *)g_rva012F19E8WindowManager)->apply();
	}

	Int gameMode = ((BfmeGameLogicPause *)TheBfmeGameLogic)->getGameMode();
	AsciiString mapName = TheWritableGlobalData->m_mapName;
	if (TheGameState->isInSaveDirectory(mapName))
		mapName.set(TheGameState->getPristineMapName());

	AsciiString replayFile = TheRecorder->getCurrentReplayFilename();
	if (TheRecorder->getMode() == 0)
		TheRecorder->stopRecording();

	Int rankPointsStartedWith = ((BfmeGameLogicPause *)TheBfmeGameLogic)->getRankPointsToAddAtGameStart();
	Int diff = ((BfmeGameLogicPause *)TheBfmeGameLogic)->getGlobalDifficulty();
	Int fps = TheGameEngine->getFramesPerSecondLimit();

	((BfmeGameLogicPause *)TheBfmeGameLogic)->clearGameData(false, false);
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
