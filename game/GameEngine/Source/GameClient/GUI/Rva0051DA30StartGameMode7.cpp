// cl: /DNDEBUG /MD

// FILE: Rva0051DA30StartGameMode7.cpp
// Another leftover on d_0050fec0.asm, beside Rva0051D960ShellPush.cpp: a
// shell callback that ignores its int argument and records a number in the
// field at +0x264, the same field Rva0051D9D0Host::checkDefaultSave writes.
//
// It starts a game in mode 7.  It flushes the game logic, copies the pending
// map name out of GlobalData +0x1200, posts BFME_MSG_NEW_GAME (0x1E) with
// mode 7 and two zero arguments, and hides the shell.  The mode number stays
// a number here because Shell_showShellMap.cpp only pins 4 (shell) and 8
// (none), and nothing in the image names 7.
//
// GlobalData +0xB84 is the pending map name and the isNotEmpty test reads the
// length at +4 of the string buffer; both come from Shell_showShellMap.cpp,
// which is byte-matched.

typedef bool Bool;
typedef int Int;

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unmodelled000[0xB84];
	AsciiString m_pendingFile;
	unsigned char m_unmodelledB88[0x1200 - 0xB88];
	AsciiString m_field1200;
	void *m_field1204;
};

extern GlobalData *TheWritableGlobalData;

class GameLogic;

extern GameLogic *TheBfmeGameLogic;

// game/GameEngine/Source/Common/U4Sink0060D3B0_push.cpp owns the body at
// 0x00396B00 this reaches through ILT 0x0001C46D.
class U4Sink0060D3B0
{
public:
	void push(Bool a, Bool b);
};

class Rva0036CA00Str;

// game/GameEngine/Source/Common/Rva00386090Set.cpp owns the body at
// 0x00386090 this reaches through ILT 0x00010FC8.
class Rva00386090
{
public:
	void set(Rva0036CA00Str *a);
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

class Shell
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;

	void hide(Bool hidden);
};

extern Shell *TheShell;

enum BfmeMessageType
{
	BFME_MSG_NEW_GAME = 0x1e
};

class Rva0051DA30Host
{
public:
	void startGameMode7(Int unused);

private:
	char m_lead[0x264];
	Int m_264;
};

// @?startGameMode7@Rva0051DA30Host@@QAEXH@Z 0x0051DA30
void Rva0051DA30Host::startGameMode7(Int)
{
	((U4Sink0060D3B0 *)TheBfmeGameLogic)->push(false, false);

	if (TheWritableGlobalData->m_field1200.isNotEmpty())
	{
		TheWritableGlobalData->m_pendingFile = TheWritableGlobalData->m_field1200;
		((Rva00386090 *)TheBfmeGameLogic)->set(
			(Rva0036CA00Str *)&TheWritableGlobalData->m_field1204);

		GameMessage *message = TheMessageStream->appendMessage(BFME_MSG_NEW_GAME);
		message->appendIntegerArgument(7);
		message->appendIntegerArgument(0);
		message->appendIntegerArgument(0);

		TheShell->hide(true);
		TheShell->slot05();
	}

	m_264 = 7;
}
