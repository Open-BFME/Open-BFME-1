// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep
// stlport
// BFME updateBuddyInfo, RVA 004EBE30, 1771-byte native body.
// Reconstructed from WOLBuddyOverlay.cpp (Copyright 2025 Electronic Arts;
// GPL-3.0-or-later), using independently verified BFME string and map ABIs.
// See targets/game/reverse/identity_evidence/004ebe30-update-buddy-info.md.
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
#include <string>

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}
inline UnicodeString::UnicodeString(const wchar_t *s)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(s);
}
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)
		->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
	return *this;
}

typedef int GPProfile;
typedef int Color;
// Layout independently matched by PeerDefsGroupRoomMapOperator.cpp and
// the 32-byte copy at 004F97B0. The list only reads the name at offset 0.
class GameSpyGroupRoom
{
  public:
	AsciiString m_name;
	UnicodeString m_translatedName;
	int m_groupID, m_numWaiting, m_maxWaiting, m_numGames, m_numPlaying;
	int rvaField1C;
};
typedef std::map<int, GameSpyGroupRoom> GroupRoomMap;
class BuddyInfo
{
  public:
	int m_id;
	AsciiString m_name, m_email, m_countryCode;
	int m_status;
	UnicodeString m_statusString, m_locationString;
	BuddyInfo(const BuddyInfo &);
	BuddyInfo &operator=(const BuddyInfo &);
	~BuddyInfo();
};
typedef std::map<int, BuddyInfo> BuddyInfoMap;
class GameSpyInfoInterface
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual GroupRoomMap *getGroupRoomList() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual BuddyInfoMap *getBuddyMap() = 0;
	virtual BuddyInfoMap *getBuddyRequestMap() = 0;
	virtual void slot5C() = 0;
	virtual bool isBuddy(int) = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual int getLocalProfileID() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual AsciiString getLocalBaseName() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual void slotDC() = 0;
	virtual void slotE0() = 0;
	virtual void slotE4() = 0;
	virtual void slotE8() = 0;
	virtual void slotEC() = 0;
	virtual void slotF0() = 0;
	virtual void slotF4() = 0;
	virtual void slotF8() = 0;
	virtual void slotFC() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10C() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11C() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual bool isSavedIgnored(int) = 0;
};
class GameSpyBuddyMessageQueueInterface
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual bool isConnected() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
};
class GameTextInterface
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch(const char *, bool * = 0) = 0;
	virtual UnicodeString fetch(AsciiString, bool * = 0) = 0;
};

extern GameSpyInfoInterface *TheGameSpyInfo;
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
extern GameTextInterface *TheGameText;

class GameWindow;
void GadgetListBoxReset(GameWindow *);
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxGetSelected(GameWindow *, int *);
void *GadgetListBoxGetItemData(GameWindow *, int, int = 0);
int GadgetListBoxAddEntryText(GameWindow *, UnicodeString, int, int, int = -1, bool = true);
void GadgetListBoxSetItemData(GameWindow *, void *, int, int = 0);
void GadgetListBoxSetSelected(GameWindow *, int);
void GadgetListBoxSetTopVisibleEntry(GameWindow *, int);
// BFME listboxBuddies and isInit are at global 012F4268 and 012F4278.
struct BuddyControls
{
	GameWindow *listboxChat;
	int listboxChatID;
	GameWindow *listboxBuddies;
	int listboxBuddiesID;
	GameWindow *textEntryEdit;
	int textEntryEditID;
	bool isInit;
};
static BuddyControls buddyControls;
extern int GameSpyColor[];
enum
{
	GSCOLOR_DEFAULT = 0,
	GSCOLOR_PLAYER_BUDDY = 8,
	GSCOLOR_PLAYER_IGNORED = 11,
	ITEM_BUDDY = 0,
	ITEM_REQUEST = 1
};
extern "C" __declspec(dllimport) int __cdecl _wtoi(const wchar_t *);
extern "C" __declspec(dllimport) unsigned short __cdecl towlower(unsigned short);
// The 89-byte retail comparator never accesses its receiver. Keeping that
// authentic body visible lets VC7.1 reuse the stateless traits temporary's
// stack slot while retaining the out-of-line retail call.
struct Rva0009ECA0NoCaseTraits
{
	__declspec(noinline) int compareNoCaseRaw(const wchar_t *left, const wchar_t *right, int length) const
	{
		while (length > 0)
		{
			const wchar_t leftLower = (wchar_t)towlower(*left);
			const wchar_t rightLower = (wchar_t)towlower(*right);
			if (leftLower != rightLower)
				return (int)leftLower - (int)rightLower;
			++left;
			++right;
			--length;
		}
		return 0;
	}
};
template <> inline int StringBase<unsigned short>::compareNoCase(const unsigned short *str, int len) const
{
	const int myLen = m_data ? m_data->length : 0;
	const unsigned short *data = m_data ? &m_data->data[0] : (const unsigned short *)L"";
	Rva0009ECA0NoCaseTraits traits;
	const int result = traits.compareNoCaseRaw(data, str, myLen < len ? myLen : len);
	return result == 0 ? myLen - len : result;
}
template <> inline int StringBase<unsigned short>::compareNoCase(const unsigned short *str) const
{
	return compareNoCase(str, str ? (int)wcslen(str) : 0);
}
void updateBuddyInfo(void)
{
	if (!TheGameSpyBuddyMessageQueue->isConnected())
	{
		GadgetListBoxReset(buddyControls.listboxBuddies);
		return;
	}

	if (!buddyControls.isInit)
		return;

	int selected;
	GPProfile selectedProfile = 0;
	int visiblePos = GadgetListBoxGetTopVisibleEntry(buddyControls.listboxBuddies);

	GadgetListBoxGetSelected(buddyControls.listboxBuddies, &selected);
	if (selected >= 0)
		selectedProfile = (GPProfile)GadgetListBoxGetItemData(buddyControls.listboxBuddies, selected);

	selected = -1;
	GadgetListBoxReset(buddyControls.listboxBuddies);

	// Add buddies
	BuddyInfoMap *buddies = TheGameSpyInfo->getBuddyMap();
	BuddyInfoMap::iterator bIt;
	for (bIt = buddies->begin(); bIt != buddies->end(); ++bIt)
	{
		BuddyInfo info = bIt->second;
		GPProfile profileID = bIt->first;

		// insert name into box
		UnicodeString formatStr;
		formatStr.translate(
			info.m_name.str()); //, info.m_status, info.m_statusString.str(), info.m_locationString.str());
		Color nameColor = (TheGameSpyInfo->isSavedIgnored(profileID)) ? GameSpyColor[GSCOLOR_PLAYER_IGNORED]
																	  : GameSpyColor[GSCOLOR_PLAYER_BUDDY];
		int index = GadgetListBoxAddEntryText(buddyControls.listboxBuddies, formatStr, nameColor, -1, -1);

		// insert status into box
		AsciiString marker;
		marker.format("Buddy:%ls", info.m_statusString.str());
		if (!((const StringBase<unsigned short> *)&info.m_statusString)->compareNoCase(L"Offline") ||
			!((const StringBase<unsigned short> *)&info.m_statusString)->compareNoCase(L"Online") ||
			!((const StringBase<unsigned short> *)&info.m_statusString)->compareNoCase(L"Matching"))
		{
			formatStr = TheGameText->fetch(marker);
		}
		else if (!((const StringBase<unsigned short> *)&info.m_statusString)->compareNoCase(L"Staging") ||
				 !((const StringBase<unsigned short> *)&info.m_statusString)->compareNoCase(L"Loading") ||
				 !((const StringBase<unsigned short> *)&info.m_statusString)->compareNoCase(L"Playing"))
		{
			formatStr.format(TheGameText->fetch(marker), info.m_locationString.str());
		}
		else if (!((const StringBase<unsigned short> *)&info.m_statusString)->compareNoCase(L"Chatting"))
		{
			UnicodeString roomName;
			GroupRoomMap::iterator gIt = TheGameSpyInfo->getGroupRoomList()->find(_wtoi(info.m_locationString.str()));
			if (gIt != TheGameSpyInfo->getGroupRoomList()->end())
			{
				AsciiString s;
				s.format("GUI:%s", gIt->second.m_name.str());
				roomName = TheGameText->fetch(s);
			}
			formatStr.format(TheGameText->fetch(marker), roomName.str());
		}
		else
		{
			formatStr = info.m_statusString;
		}
		GadgetListBoxAddEntryText(buddyControls.listboxBuddies, formatStr, GameSpyColor[GSCOLOR_DEFAULT], index, 1);
		GadgetListBoxSetItemData(buddyControls.listboxBuddies, (void *)(profileID), index, 0);
		GadgetListBoxSetItemData(buddyControls.listboxBuddies, (void *)(ITEM_BUDDY), index, 1);

		if (profileID == selectedProfile)
			selected = index;
	}

	// add requests
	buddies = TheGameSpyInfo->getBuddyRequestMap();
	for (bIt = buddies->begin(); bIt != buddies->end(); ++bIt)
	{
		BuddyInfo info = bIt->second;
		GPProfile profileID = bIt->first;

		// insert name into box
		UnicodeString formatStr;
		formatStr.translate(info.m_name.str());
		int index =
			GadgetListBoxAddEntryText(buddyControls.listboxBuddies, formatStr, GameSpyColor[GSCOLOR_DEFAULT], -1, -1);
		GadgetListBoxSetItemData(buddyControls.listboxBuddies, (void *)(profileID), index, 0);

		// insert status into box
		formatStr = TheGameText->fetch("GUI:BuddyAddReq");
		GadgetListBoxAddEntryText(buddyControls.listboxBuddies, formatStr, GameSpyColor[GSCOLOR_DEFAULT], index, 1);
		GadgetListBoxSetItemData(buddyControls.listboxBuddies, (void *)(ITEM_REQUEST), index, 1);

		if (profileID == selectedProfile)
			selected = index;
	}

	// select the same guy
	if (selected >= 0)
	{
		GadgetListBoxSetSelected(buddyControls.listboxBuddies, selected);
	}

	// view the same spot
	GadgetListBoxSetTopVisibleEntry(buddyControls.listboxBuddies, visiblePos);
}
