// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the ControlBar::getStarImage naked dump to clean C++.
//
// Zero Hour's ControlBar.cpp body with one BFME difference: where ZH calls the
// gadget helper in all three arms, retail only calls it in the two flashing
// arms. The not-flashing arm sets the three window images itself -- the enabled
// image at index 0 and null at indices 5 and 6 -- through the same
// winSetEnabledImage already pinned for the transition work.
//
// The modulus independently confirms LOGICFRAMES_PER_SECOND is 5 here rather
// than ZH's 30: retail divides the frame by 5 and compares the remainder
// against 2, which is that constant and its half. That agrees with the
// ScriptActions::doNamedFlash conversion, which scaled seconds by the same 5.
//
// The points value is read once where ZH writes three calls, and the local
// player once where ZH writes three, both plain common-subexpression work.
//
// Retail pins the layout: the enabled and highlight images are at this+0x2C0
// and +0x2C4, the flash flag at +0x2C8 and the last flashed value at +0x2CC;
// the science purchase points are at player+0x264 and the frame at
// TheGameLogic+0x3C, which agrees with the DisconnectManager conversion.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Image;

enum { LOGICFRAMES_PER_SECOND = 5 };

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);			///< ILT thunk at 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;			///< retail [0x012ED600]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winSetEnabledImage(Int index, const Image *image);	///< ILT thunk at 0x00035E09
};

void GadgetButtonSetEnabledImage(GameWindow *win, const Image *image);	///< ILT thunk at 0x00038A23

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getSciencePurchasePoints(void) const { return m_sciencePurchasePoints; }

private:
	unsigned char m_unreconstructed_00[0x264];
	Int m_sciencePurchasePoints;						///< retail this+0x264
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getLocalPlayer(void) { return m_localPlayer; }

private:
	unsigned char m_unreconstructed_00[0x0C];
	Player *m_localPlayer;								///< retail this+0x0C
};

extern PlayerList *ThePlayerList;						///< retail [0x012ED748]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }

private:
	unsigned char m_unreconstructed_00[0x3C];
	UnsignedInt m_frame;								///< retail this+0x3C
};

extern GameLogic *TheGameLogic;							///< retail [0x012F0898]

// Only the lookup is reconstructed; the slots ahead of it place it.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();

	virtual GameWindow *winGetWindowFromId(GameWindow *window, NameKeyType id);	///< vtable +0xDC
};

extern GameWindowManager *TheWindowManager;				///< retail [0x012F1B40]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	const Image *getStarImage(void);

private:
	unsigned char m_unreconstructed_00[0x2C0];
	const Image *m_generalButtonEnable;					///< retail this+0x2C0
	const Image *m_generalButtonHighlight;				///< retail this+0x2C4
	Bool m_genStarFlash;								///< retail this+0x2C8
	unsigned char m_unreconstructed_2C9[3];
	Int m_lastFlashedAtPointValue;						///< retail this+0x2CC
};

// ?getStarImage@ControlBar@@QAEPBVImage@@XZ
const Image *ControlBar::getStarImage(void )
{
	if(m_lastFlashedAtPointValue > ThePlayerList->getLocalPlayer()->getSciencePurchasePoints() || ThePlayerList->getLocalPlayer()->getSciencePurchasePoints() <= 0)
		m_genStarFlash = false;
	else
		m_lastFlashedAtPointValue = ThePlayerList->getLocalPlayer()->getSciencePurchasePoints();

	GameWindow *win= TheWindowManager->winGetWindowFromId( 0, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonGeneral" ) );
	if(!win)
		return 0;
	if(!m_genStarFlash)
	{
		win->winSetEnabledImage(0, m_generalButtonEnable);
		win->winSetEnabledImage(5, 0);
		win->winSetEnabledImage(6, 0);
		return 0;
	}

	if(TheGameLogic->getFrame()% LOGICFRAMES_PER_SECOND > LOGICFRAMES_PER_SECOND/2)
	{
		GadgetButtonSetEnabledImage(win, m_generalButtonHighlight);
		return 0;
	}

	GadgetButtonSetEnabledImage(win, m_generalButtonEnable);

	return 0;

}
