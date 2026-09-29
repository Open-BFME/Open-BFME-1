// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?playerTooltip@@: game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanLobbyMenu.cpp
// LanLobbyMenu playerTooltip at 0x004CE850 (145 B). Retail's only reference to
// this body is the DIR32 at 0x004CFA12 inside the matched LanLobbyMenuInit
// (0x004CF440), where ZH installs listboxPlayers->winSetTooltipFunc(playerTooltip).
// BFME differs from the ZH source: the mouse word is split without sign
// extension, LookupPlayer takes BFME's {ip, port} address (TheLAN vtable slot
// 54, as in LANAPIHandleRequestLocationsThunk.cpp), and the tooltip is the
// player's name itself rather than the formatted TOOLTIP:LANPlayer string.
typedef unsigned short wchar_t;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
#include "Common/AsciiString.h"
// Local StringBase adapter also exposes str() for the inlined game-name copy.
class UnicodeString {
public:
    UnicodeString() { m_data = 0; }
    UnicodeString(const UnicodeString &that) {
        ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(*(const StringBase<wchar_t> *)&that);
    }
    explicit UnicodeString(const wchar_t *str) {
        ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(str);
    }
    ~UnicodeString();
    void set(const UnicodeString &that) {
        ((StringBase<wchar_t> *)this)->set(*(const StringBase<wchar_t> *)&that);
    }
    void translate(const AsciiString &that);
    const wchar_t *str() const {
        return m_data ? reinterpret_cast<const wchar_t *>(m_data) + 4 : L"";
    }
private:
    void *m_data;
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class LANPlayer
{
public:
	const UnicodeString &getName() const { return m_name; }
private:
	UnicodeString m_name;				// +0x00
};

class LANAPI
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void _bfme_slot9(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void _bfme_slot49(void) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual LANPlayer *LookupPlayer(BfmeNetAddress *who) = 0;		// slot 54, vtable+0xD8
};
extern LANAPI *TheLAN;

struct RGBColor;
class Mouse
{
public:
	void setCursorTooltip(UnicodeString tooltip, Int tooltipDelay = -1, const RGBColor *color = 0, Real width = 1.0f);
};
extern Mouse *TheMouse;

class GameWindow;
class WinInstanceData;
Int GadgetListBoxGetEntryBasedOnXY(GameWindow *listbox, Int x, Int y, Int &row, Int &column);
void *GadgetListBoxGetItemData(GameWindow *listbox, Int row, Int column);

// LanLobbyMenu.cpp's own file-static playerTooltip. WOLLobbyMenu's matched
// static of the same name already owns ?playerTooltip@@... (0x004FA800), so this
// one is claimed inside an address-keeping namespace, as with the
// Rva0050CA80Twin precedent.
namespace Rva004CE850LanLobbyMenu
{

// ?playerTooltip@Rva004CE850LanLobbyMenu@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z
void playerTooltip(GameWindow *window,
				   WinInstanceData *instData,
				   UnsignedInt mouse)
{
	Int x, y, row, col;
	x = mouse & 0xFFFF;
	y = mouse >> 16;

	GadgetListBoxGetEntryBasedOnXY(window, x, y, row, col);

	if (row == -1 || col == -1)
		return;

	LANPlayer *player;
	{
		BfmeNetAddress playerAddress;
		playerAddress.m_ip = (UnsignedInt)GadgetListBoxGetItemData( window, row, col );
		playerAddress.m_port = 0;
		player = TheLAN->LookupPlayer(&playerAddress);
	}
	if (!player)
		return;
	TheMouse->setCursorTooltip( player->getName() );
}

}
