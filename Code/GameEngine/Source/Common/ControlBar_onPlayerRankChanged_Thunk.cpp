// cl: /DNDEBUG /MD /EHsc
// readable body of ?onPlayerRankChanged@ControlBar@@QAEXPBVPlayer@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
// Open-BFME5: lift the ControlBar::onPlayerRankChanged MASM dump to clean C++.
//
// Zero Hour's body is ControlBar.cpp:1675 and BFME kept it, with two changes
// retail shows: setGroup takes a second argument, always zero, and
// getInputEnabled tests two bytes at +0xD and +0xE rather than one.
//
// getLocalPlayer, getSciencePurchasePoints, getInputEnabled and markUIDirty are
// all inlined to direct member access; only isLocalPlayer and setGroup are calls.
// The AsciiString argument is passed by value and destroyed by the callee, which
// is why no destructor and no EH frame appear here.

class AsciiString;

template <class T>
class StringBase
{
private:
	friend class AsciiString;

	StringBase(const char *s);			///< body at 0x00888BC0
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	bool isLocalPlayer(void) const;		///< ILT 0x00013877

	unsigned char m_unreconstructed_00[0x264];
	int m_sciencePurchasePoints;		///< retail player+0x264

	int getSciencePurchasePoints(void) const { return m_sciencePurchasePoints; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getLocalPlayer(void) const { return m_localPlayer; }

	unsigned char m_unreconstructed_00[0xC];
	Player *m_localPlayer;			///< retail list+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	bool getInputEnabled(void) const { return m_inputEnabled && m_inputAllowed; }

	unsigned char m_unreconstructed_00[0xD];
	bool m_inputEnabled;				///< retail ui+0x0D
	bool m_inputAllowed;				///< retail ui+0x0E
};

class TransitionHandler
{
public:
	void setGroup(AsciiString name, int flag);	///< ILT 0x00045C28
};

extern PlayerList *ThePlayerList;			///< retail [0x012ED748]
extern TransitionHandler *TheTransitionHandler;	///< retail [0x012F3330]
extern InGameUI *TheInGameUI;				///< retail [0x012F148C]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void onPlayerRankChanged(const Player *p);

private:
	void markUIDirty(void) { m_UIDirty = true; }

	unsigned char m_unreconstructed_00[0x24];
	bool m_UIDirty;					///< retail this+0x24
	unsigned char m_unreconstructed_25[0x2A3];
	bool m_genStarFlash;				///< retail this+0x2C8
	unsigned char m_unreconstructed_2c9[3];
	int m_lastFlashedAtPointValue;		///< retail this+0x2CC
};

// ?onPlayerRankChanged@ControlBar@@QAEXPBVPlayer@@@Z
void ControlBar::onPlayerRankChanged(const Player *p)
{
	if (!p->isLocalPlayer())
	{
		return;
	}

	if (!(m_lastFlashedAtPointValue > ThePlayerList->getLocalPlayer()->getSciencePurchasePoints()))
	{
		if (TheTransitionHandler && TheInGameUI->getInputEnabled())
		{
			TheTransitionHandler->setGroup("ControlBarArrow", 0);
		}
	}

	m_genStarFlash = true;
	markUIDirty();
}
