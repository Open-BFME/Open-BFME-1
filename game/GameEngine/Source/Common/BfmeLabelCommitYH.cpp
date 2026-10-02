// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the label commit at retail 0x004D1080, 117 bytes.  The label
// arrives by value and is released at the end; the receiver for set is an
// embedded member of the global base, which is why its address is materialised
// with an add rather than folded into a displacement.

class AsciiStringYH
{
public:
	~AsciiStringYH(void);

	void set(const AsciiStringYH &other);
};

class BfmeBaseYH
{
public:
	char m_bfmePad000[0xB84];				// +0x000
	AsciiStringYH m_bfmeLabel;				// +0xB84
};

class BfmeThingYH
{
public:
	void bfmeNotifyYH(void);
};

class BfmeOtherYH
{
public:
	void bfmeRefreshYH(int mode);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// bfmeRefreshYH() through it, so the pointee stays the local BfmeOtherYH view
// and the access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

// Canonical identity of the retail global at 0x012ED5C8, defined once by
// game/GameEngine/Source/Common/GlobalData.cpp as
// ?TheWritableGlobalData@@3PAVGlobalData@@A.  The member address keeps the local
// view and casts at the use.
class GlobalData;
extern GlobalData *TheWritableGlobalData;		// retail 0x012ED5C8
// Retail global 0x012F4B58; EA's own name for this pointer is
// `Shell *TheShell`, defined once in
// game/GameEngine/Source/GameClient/GUI/Shell/Shell.cpp.  BfmeThingYH above
// is this TU's view of the pointee, so the call casts at the use.
class Shell;

extern Shell *TheShell;						// retail 0x012F4B58
extern bool g_bfmeDirtyYH;					// retail 0x012F3E6D

// ?bfmeCommitYH@@YAXVAsciiStringYH@@@Z
void __cdecl bfmeCommitYH(AsciiStringYH label)
{
	g_bfmeDirtyYH = true;

	AsciiStringYH *slot = &((BfmeBaseYH *)TheWritableGlobalData)->m_bfmeLabel;

	slot->set(label);

	((BfmeThingYH *)TheShell)->bfmeNotifyYH();

	if (g_rva012F19E8WindowManager != 0)
		((BfmeOtherYH *)g_rva012F19E8WindowManager)->bfmeRefreshYH(0);
}
