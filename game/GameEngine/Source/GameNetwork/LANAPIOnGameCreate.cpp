// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// C++ recovery for LANAPI::OnGameCreate.
// Retail RVA 0x00689910, complete extent 243 bytes [0x00689910,0x00689A03).
// The neutral gen-dump row is an identity placeholder; no real OnGameCreate
// row currently owns this range.
//
// Identity anchors:
//  * LANAPI vtable VA 0x0111AF50 slot 40 (+0xA0) is thunk RVA 0x0001CC15,
//    whose E9 target is 0x00689910.
//  * Retail uses LANAPI slot 25 (+0x64) for RequestLobbyLeave(false).
//  * The success fallback uses TheShell::push(AsciiString,bool), while the
//    non-fallback branch calls the BFME helper reached through ILT 0x2A5B8.
//  * Failure text uses m_chatWindow at LANAPI+0x5C and the established
//    GameText fetch / GadgetListBoxAddEntryText ABI.

#include "StringInline.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef int Color;

class GameWindow;

// The function's body reads this cell at retail VA 0x012BA0D4.
extern const Color chatSystemColor;
extern bool LANbuttonPushed;

// Retail global at VA 0x012F4998.  Its helper is called only on the success
// path when the pointer is present; the helper identity remains address based.
struct BfmeObj935C;
extern BfmeObj935C *g_bfme935GlobC;

// Address-qualified view of the actual no-argument thiscall helper.
// ILT2A5B8 enters body51A5D0 directly; no this adjustment is needed here.
class Rva0051A5D0Receiver
{
public:
    void Rva0051A5D0Advance(void);
};

class Shell
{
public:
	void push(AsciiString filename, bool shutdownImmediate = false);
};
extern Shell *TheShell;

class GameTextInterface
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

extern Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	Color color, Int row, Int column, bool overwrite = true);

class LANAPIInterface
{
public:
	enum ReturnType
	{
		RET_OK = 0,
		RET_TIMEOUT,
		RET_GAME_FULL,
		RET_DUPLICATE_NAME,
		RET_CRC_MISMATCH,
		RET_SERIAL_DUPE,
		RET_GAME_STARTED,
		RET_GAME_EXISTS,
		RET_GAME_GONE,
		RET_BUSY,
		RET_UNKNOWN,
		RET_MAX
	};
};

// Keep only the proven LANAPI prefix and virtual slots needed by this body.
// This object's member at +0x5C is the chat GameWindow in retail.
class LANAPI
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
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void RequestLobbyLeave(bool forced) = 0; // slot 25 (+0x64)
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void OnGameCreate(LANAPIInterface::ReturnType ret);

protected:
	unsigned char m_beforeLobby[0x3D - 4];
	bool m_inLobby;                         // +0x3D
	unsigned char m_betweenLobbyAndChat[0x5C - 0x3E];
	GameWindow *m_chatWindow;               // +0x5C
};

// ?OnGameCreate@LANAPI@@UAEXW4ReturnType@LANAPIInterface@@@Z
void LANAPI::OnGameCreate(LANAPIInterface::ReturnType ret)
{
	if (ret == LANAPIInterface::RET_OK)
	{
		if (g_bfme935GlobC)
		{
			reinterpret_cast<Rva0051A5D0Receiver *>(g_bfme935GlobC)->Rva0051A5D0Advance();
		}
		else
		{
			LANbuttonPushed = true;
			TheShell->push(AsciiString("Menus/LanGameOptionsMenu.wnd"), false);
		}
		RequestLobbyLeave(false);
	}
	else if (m_inLobby)
	{
		switch (ret)
		{
		case LANAPIInterface::RET_GAME_EXISTS:
			GadgetListBoxAddEntryText(m_chatWindow,
				TheGameText->fetch("LAN:ErrorGameExists"), chatSystemColor, -1, -1);
			break;
		case LANAPIInterface::RET_BUSY:
			GadgetListBoxAddEntryText(m_chatWindow,
				TheGameText->fetch("LAN:ErrorBusy"), chatSystemColor, -1, -1);
			break;
		default:
			GadgetListBoxAddEntryText(m_chatWindow,
				TheGameText->fetch("LAN:ErrorUnknown"), chatSystemColor, -1, -1);
			break;
		}
	}
}
