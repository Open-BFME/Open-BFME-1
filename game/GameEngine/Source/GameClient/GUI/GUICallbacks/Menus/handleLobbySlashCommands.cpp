// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/nat /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// ?handleLobbySlashCommands@@YA_NVUnicodeString@@@Z, retail 0x004FC510.
// stlport
// The caller and the WOL menu string literals prove the identity.  The
// nat/stringbaseunicode shims supply BFME's +8 data header;
// StringBase casts below are ABI views of those same one-pointer objects and
// are used only for the retail StringBase<char> helper calls.

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#include "string_base.h"

typedef bool Bool;

class GameWindow;

// The retail WOL interface has hasStagingRoomListChanged at slot 43, addText
// at slot 59, and sendChat at slot 62.  Only those slots are consumed here.
class GameSpyInfo
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0;
	virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0;
	virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual Bool hasStagingRoomListChanged() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0;
	virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0;
	virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void addText(UnicodeString message, int color, GameWindow *window) = 0;
	virtual void slot60() = 0; virtual void slot61() = 0;
	virtual Bool sendChat(UnicodeString message, Bool action, GameWindow *window) = 0;
};

extern GameSpyInfo *TheGameSpyInfo;
extern int GameSpyColor[];
extern GameWindow *listboxLobbyPlayers;
extern int isThreadHosting;
extern void j_000446ca(void);
extern void bfmeRefreshXE(void);
extern void PopulateLobbyPlayerListbox(void);
extern "C" int (__cdecl *g_bfmeNowVNH)(void);

typedef int (__cdecl *BfmeQr2StatusABI)(void);

static int gameListRefreshTime = 0;
static int playerListRefreshTime = 0;

static const unsigned short *bfmeUnicodeStr(const UnicodeString &value)
{
	const char *data = *(const char *const *)&value;
	static const unsigned short empty[1] = { 0 };
	return data ? (const unsigned short *)(data + 8) : empty;
}

static int bfmeUnicodeLength(const UnicodeString &value)
{
	const char *data = *(const char *const *)&value;
	return data ? *(const unsigned short *)(data + 4) : 0;
}

Bool handleLobbySlashCommands(UnicodeString uText)
{
	AsciiString message;
	message.translate(uText);
	if (message.getCharAt(0) != '/')
		return false;

	AsciiString remainder(message.str() + 1);
	AsciiString token;
	((StringBase<char> *)&remainder)->nextToken(
		(StringBase<char> *)&token, 0);
	((StringBase<char> *)&token)->toLower();

	if (((const StringBase<char> *)&token)->compare("host") == 0)
	{
		UnicodeString s;
			s.format(UnicodeString(L"Hosting qr2:%d thread:%d"),
			((BfmeQr2StatusABI)j_000446ca)(), isThreadHosting);
		TheGameSpyInfo->addText(s, GameSpyColor[0], 0);
		return true;
	}
	else if (((const StringBase<char> *)&token)->compare("me") == 0 &&
		bfmeUnicodeLength(uText) > 4)
	{
		TheGameSpyInfo->sendChat(UnicodeString(bfmeUnicodeStr(uText) + 4),
			true, listboxLobbyPlayers);
		return true;
	}
	else if (((const StringBase<char> *)&token)->compare("refresh") == 0)
	{
		// Both arms capture the clock after the virtual query; this preserves
		// retail scheduling while the player-list refresh stays unconditional.
		int (__cdecl *nowFunction)(void);
		if (TheGameSpyInfo->hasStagingRoomListChanged()
			? (nowFunction = g_bfmeNowVNH, true)
			: (nowFunction = g_bfmeNowVNH, false))
		{
			bfmeRefreshXE();
			gameListRefreshTime = nowFunction();
		}
		PopulateLobbyPlayerListbox();
		playerListRefreshTime = nowFunction();
		return true;
	}

	return false;
}
