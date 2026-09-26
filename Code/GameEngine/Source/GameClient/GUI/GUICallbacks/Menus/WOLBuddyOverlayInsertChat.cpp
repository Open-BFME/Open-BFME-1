// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// insertChat retail 0x004EB6B0 596 bytes; ZH twin in WOLBuddyOverlay.cpp.
// Matched callers PopulateOldBuddyMessages (0x004EB9A0) and BuddyControlSystem
// (0x004ED400) call it by this name. GameSpyInfo slot +0x5C is getBuddyMessages
// (PopulateOldBuddyMessages) and +0x60 isBuddy (removeBuddy 0x00637BD0), so ZH
// declaration order puts getBuddyMap at +0x54, getLocalProfileID at +0x70 and
// getLocalBaseName at +0x88. BFME dropped ZH's two unused BuddyInfoMap::find
// lookups: retail makes the getBuddyMap call and discards the result.

#include "string_base.h"
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef int Color;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int GPProfile;

// Retail inlines the null-checked data pointer read at every str() site.
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template <> inline const wchar_t *StringBase<wchar_t>::str() const { return m_data ? m_data->data : L""; }

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}

inline UnicodeString::UnicodeString(const wchar_t *str)
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(str);
}

inline UnicodeString::UnicodeString(const UnicodeString &that)
{
	((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
		*(const StringBase<wchar_t> *)&that);
}

inline UnicodeString::~UnicodeString()
{
	((StringBase<wchar_t> *)this)->releaseBuffer();
}

inline UnicodeString &UnicodeString::operator=(const UnicodeString &that)
{
	((StringBase<wchar_t> *)this)->set(*(const StringBase<wchar_t> *)&that);
	return *this;
}

class GameWindow;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/BuddyDefs.h
class BuddyMessage
{
public:
	~BuddyMessage();

	UnsignedInt m_timestamp;
	GPProfile m_senderID;
	AsciiString m_senderNick;
	GPProfile m_recipientID;
	AsciiString m_recipientNick;
	UnicodeString m_message;
};

class BuddyInfoMap;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyInfo
{
public:
	virtual void slot_000();
	virtual void slot_004();
	virtual void slot_008();
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual void slot_02c();
	virtual void slot_030();
	virtual void slot_034();
	virtual void slot_038();
	virtual void slot_03c();
	virtual void slot_040();
	virtual void slot_044();
	virtual void slot_048();
	virtual void slot_04c();
	virtual void slot_050();
	virtual BuddyInfoMap *getBuddyMap(void);
	virtual void slot_058();
	virtual void slot_05c();
	virtual void slot_060();
	virtual void slot_064();
	virtual void slot_068();
	virtual void slot_06c();
	virtual Int getLocalProfileID(void);
	virtual void slot_074();
	virtual void slot_078();
	virtual void slot_07c();
	virtual void slot_080();
	virtual void slot_084();
	virtual AsciiString getLocalBaseName(void);
};

extern GameSpyInfo *TheGameSpyInfo;

// Retail reads +0x00, +0x20 and +0x28 of this table (ZH's GSCOLOR_DEFAULT and
// GSCOLOR_PLAYER_BUDDY sit at 0 and 8; ZH's GSCOLOR_PLAYER_SELF is 9, so BFME
// moved the self entry and the index stays numeric here).
extern Color GameSpyColor[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlay.cpp
class BuddyControls
{
public:
	GameWindow *listboxChat;
};

extern BuddyControls buddyControls;

Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, Color color, Int row, Int column = -1, bool overwrite = true);

// ?insertChat@@YAXVBuddyMessage@@@Z
void insertChat( BuddyMessage msg )
{
	if (buddyControls.listboxChat)
	{
		BuddyInfoMap *m = TheGameSpyInfo->getBuddyMap();
		Bool localSender = (msg.m_senderID == TheGameSpyInfo->getLocalProfileID());
		UnicodeString s;
		UnicodeString timeStr;
		if (localSender)
		{
			s.format(L"[%hs -> %hs] %s", TheGameSpyInfo->getLocalBaseName().str(), msg.m_recipientNick.str(), msg.m_message.str());
			Int index = GadgetListBoxAddEntryText( buddyControls.listboxChat, s, GameSpyColor[10], -1, -1 );
			GadgetListBoxAddEntryText( buddyControls.listboxChat, timeStr, GameSpyColor[10], index, 1);
		}
		else if (!localSender)
		{
			if (!msg.m_senderID)
			{
				s = msg.m_message;
				Int index = GadgetListBoxAddEntryText( buddyControls.listboxChat, s, GameSpyColor[0], -1, -1 );
				GadgetListBoxAddEntryText( buddyControls.listboxChat, timeStr, GameSpyColor[0], index, 1);
			}
			else
			{
				s.format(L"[%hs] %s", msg.m_senderNick.str(), msg.m_message.str());
				Int index = GadgetListBoxAddEntryText( buddyControls.listboxChat, s, GameSpyColor[8], -1, -1 );
				GadgetListBoxAddEntryText( buddyControls.listboxChat, timeStr, GameSpyColor[8], index, 1);
			}
		}
	}
}
