// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: Shell::isAnimReversed, retail 0x0057F440.
//
// The Zero Hour body unchanged. One offset is BFME's: m_animateWindows sits at
// GlobalData+0xbc4, where this tree lands it at +0x835.
//
// That is the third field of GlobalData to disagree, and by a third amount --
// m_xResolution is 8 bytes out (0x2c against 0x24) and m_netMinPlayers 0x744
// out (0xecc against 0x788), both pinned in CommandLine.cpp. So BFME's
// GlobalData is not this tree's shifted by any constant, and the retail offsets
// are not even aligned the same way: 0x835 is not a multiple of four, 0xbc4 is.
//
// Kept out of Shell.cpp because pinning the offset there changes codegen enough
// to renumber the compiland's $L labels, which remaps the EH funclet rows that
// file already has matched (uw_00c367e8 and its siblings).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/AnimateWindowManager.h
class AnimateWindowManager
{
public:
	bool isReversed(void) const { return m_reversed; }

private:
	char m_unreconstructed_00[0x11];
	bool m_reversed;								///< retail this+0x11
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	bool isAnimReversed(void);

private:
	char m_unreconstructed_00[0x5c];
	AnimateWindowManager *m_animateWindowManager;	///< retail this+0x5c
};

// ?isAnimReversed@Shell@@QAE_NXZ
bool Shell::isAnimReversed(void)
{
	if (!m_animateWindowManager)
	{
		return true;
	}
	if (*((const char *)TheWritableGlobalData + 0xbc4))	// m_animateWindows
		return m_animateWindowManager->isReversed();

	return true;
}
