// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep
// stlport
// BFME HandleBuddyResponses, RVA 004EE510, full 3624-byte extent including
// its seven-entry switch table. Native reconstruction from the canonical
// WOLBuddyOverlay.cpp body (Copyright 2025 Electronic Arts; GPL-3.0-or-later).
// BFME event kinds and call contracts are documented in
// targets/game/reverse/identity_evidence/004ee510-buddy-contracts.md.
// This local view preserves BFME queue/vtable layouts without changing the
// older ZH declarations used by the remaining overlay functions.
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
typedef int GPEnum;
typedef bool Bool;
#define TRUE true
#define FALSE false
#define GP_OFFLINE 0
#define GP_ONLINE 1
#define GP_RECV_GAME_INVITE 4
class BuddyInfo
{
  public:
	int m_id;
	AsciiString m_name, m_email, m_countryCode;
	int m_status;
	UnicodeString m_statusString, m_locationString;
	BuddyInfo &operator=(const BuddyInfo &);
	~BuddyInfo();
};
typedef std::map<int, BuddyInfo> BuddyInfoMap;
// The map's tree insert is retail 0x004EBC90 (stlport_rb_tree_int_buddyinfo_insert.cpp);
// instantiated here it came out as a different COMDAT copy (link_census
// RetailTruth: "wrong") that the link keeps ahead of retail's, so this TU only
// declares it.
typedef _STL::pair<const int, BuddyInfo> BuddyInfoPair;
template <>
_STL::_Rb_tree<int, BuddyInfoPair, _STL::_Select1st<BuddyInfoPair>, _STL::less<int>,
	_STL::allocator<BuddyInfoPair> >::iterator
_STL::_Rb_tree<int, BuddyInfoPair, _STL::_Select1st<BuddyInfoPair>, _STL::less<int>,
	_STL::allocator<BuddyInfoPair> >::_M_insert(
	_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const BuddyInfoPair &,
	_STL::_Rb_tree_node_base * );
class BuddyMessage
{
  public:
	unsigned int m_timestamp;
	int m_senderID;
	AsciiString m_senderNick;
	int m_recipientID;
	AsciiString m_recipientNick;
	UnicodeString m_message;
	BuddyMessage()
	{
	}
	BuddyMessage(const BuddyMessage &);
	~BuddyMessage();
};
// The independently matched PeerResponse copy/queue bodies prove size 0x330
// and the payload union at +0xF4; its prefix is constructed by the real ctor.
class PeerResponse
{
  public:
	PeerResponse();
	~PeerResponse();
	int peerResponseType;
	char opaque04[0xf4 - 4];
	int reason;
	char opaqueF8[0x330 - 0xf8];
};
// The response deque copies 0x864 bytes. Named GP payload fields are witnessed
// here; the unused union tail and two BFME-only event kinds stay opaque.
struct BuddyResponse
{
	enum
	{
		BUDDYRESPONSE_LOGIN,
		BUDDYRESPONSE_DISCONNECT,
		BUDDYRESPONSE_MESSAGE,
		BUDDYRESPONSE_REQUEST,
		BUDDYRESPONSE_STATUS,
		RVA_KIND_5,
		RVA_KIND_6
	} buddyResponseType;
	int profile, result;
	union {
		struct
		{
			unsigned int date;
			char nick[31];
			unsigned short text[1];
		} message;
		struct
		{
			char nick[31], email[51], countrycode[3];
			unsigned short text[1];
		} request;
		struct
		{
			char nick[31], email[51], countrycode[3], location[256];
			int status;
			char statusString[256];
		} status;
		int words[0x858 / 4];
	} arg;
};
struct BuddyRequest
{
	int type, profile;
	char rest[0x2b8 - 8];
};
class GameSpyInfoInterface
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
	virtual void slot130() = 0;
	virtual void slot134() = 0;
	virtual void slot138() = 0;
	virtual void slot13C() = 0;
	virtual void slot140() = 0;
	virtual void slot144() = 0;
	virtual void slot148() = 0;
	virtual void slot14C() = 0;
	virtual void slot150() = 0;
	virtual void slot154() = 0;
	virtual void slot158() = 0;
	virtual void slot15C() = 0;
	virtual void slot160() = 0;
	virtual void slot164() = 0;
	virtual void slot168() = 0;
	virtual void slot16C() = 0;
	virtual void slot170() = 0;
	virtual void slot174() = 0;
	virtual void slot178() = 0;
	virtual void slot17C() = 0;
	virtual void rvaSlot180(bool) = 0;
};
class GameSpyBuddyMessageQueueInterface
{
  public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void addRequest(const BuddyRequest &) = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual bool getResponse(BuddyResponse &) = 0;
};
class GameSpyPeerMessageQueueInterface
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
	virtual void addResponse(const PeerResponse &) = 0;
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
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
extern GameTextInterface *TheGameText;
static bool lastNotificationWasStatus = 0;
static int numOnlineInNotification = 0;
static bool Rva012F4248NotificationActive = 0;
static unsigned int noticeExpires = 0;
extern const AsciiString Rva01336E50EmptyString;
#define EmptyAsciiString Rva01336E50EmptyString
struct Rva004EE510Login
{
	char prefix[0xa0];
	bool atA0;
	char gap[11];
	bool atAC;
};
extern Rva004EE510Login *Rva012F4AACLoginScreen;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
void bfmeGo1086B();
void Rva004EBA70NotificationDispatch(AsciiString, UnicodeString);
// A distinct retail STL tree copy from the canonical BuddyInfo erase symbol.
// The independent 91-byte body returns an unsigned count and ends in RET 4.
class Rva004EE060Tree
{
  public:
	unsigned int erase(const int &key);
};
void addBuddyMessage(const BuddyMessage &);
// Existing address-bearing symbol: the old row's two-string signature is
// stale. The full body consumes and destroys a 24-byte BuddyMessage by value.
extern "C" void bfme_showNotificationBox_4ECD10(BuddyMessage);
void updateBuddyInfo();
void PopulateLobbyPlayerListbox();
void RefreshGameListBoxes();
void GSMessageBoxOk(UnicodeString, UnicodeString, void (*)());
std::wstring MultiByteToWideCharSingleLine(const char *);

void HandleBuddyResponses(void)
{
	if (TheGameSpyBuddyMessageQueue)
	{
		BuddyResponse resp;
		if (TheGameSpyBuddyMessageQueue->getResponse(resp))
		{
			switch (resp.buddyResponseType)
			{
			case BuddyResponse::BUDDYRESPONSE_LOGIN: {
				bfmeGo1086B();
				TheGameSpyInfo->rvaSlot180(true);
			}
			break;
			case BuddyResponse::RVA_KIND_6: {
				if (Rva012F4AACLoginScreen)
					Rva012F4AACLoginScreen->atA0 = true;
				if (TheGameSpyPeerMessageQueue)
				{
					PeerResponse response;
					response.peerResponseType = 1;
					response.reason = 21;
					TheGameSpyPeerMessageQueue->addResponse(response);
				}
				TheGameSpyInfo->rvaSlot180(false);
			}
			break;
			case BuddyResponse::BUDDYRESPONSE_DISCONNECT: {
				lastNotificationWasStatus = false;
				numOnlineInNotification = 0;
				Rva004EBA70NotificationDispatch(EmptyAsciiString,
				                                TheGameText->fetch("Buddy:MessageDisconnected"));
				UnicodeString title, message;
				AsciiString key;
				key.format("GUI:GSGPDisconReason%d", resp.arg.words[1]);
				title = TheGameText->fetch("GUI:GSErrorTitle");
				message = TheGameText->fetch(key);
				GSMessageBoxOk(title, message, 0);
				if (Rva012F4AACLoginScreen)
				{
					Rva012F4AACLoginScreen->atA0 = true;
				}
				if (TheGameSpyPeerMessageQueue)
				{
					PeerResponse response;
					response.peerResponseType = 1;
					response.reason = 3;
					TheGameSpyPeerMessageQueue->addResponse(response);
				}
				TheGameSpyInfo->rvaSlot180(false);
			}
			break;
			case BuddyResponse::RVA_KIND_5: {
				lastNotificationWasStatus = false;
				numOnlineInNotification = 0;
				Rva004EBA70NotificationDispatch(EmptyAsciiString,
				                                TheGameText->fetch("Buddy:MessageDisconnected"));
				UnicodeString title, message;
				AsciiString key;
				key.format("FESL:FESL%d", resp.arg.words[0]);
				title = TheGameText->fetch("GUI:GSErrorTitle");
				message = TheGameText->fetch(key);
				GSMessageBoxOk(title, message, 0);
				if (Rva012F4AACLoginScreen)
				{
					Rva012F4AACLoginScreen->atA0 = true;
					if (resp.arg.words[0] == 0x26ad)
						Rva012F4AACLoginScreen->atAC = true;
				}
				if (TheGameSpyPeerMessageQueue)
				{
					PeerResponse response;
					response.peerResponseType = 1;
					response.reason = 3;
					TheGameSpyPeerMessageQueue->addResponse(response);
				}
				TheGameSpyInfo->rvaSlot180(false);
			}
			break;
			case BuddyResponse::BUDDYRESPONSE_MESSAGE: {
				if (!wcscmp(resp.arg.message.text,
				            L"I have authorized your request to add me to your list"))
					break;

				if (TheGameSpyInfo->isSavedIgnored(resp.profile))
				{
					//
					break; // no buddy messages from ignored people
				}

				// save message for future incarnations of the buddy window

				BuddyMessage message;
				message.m_timestamp = resp.arg.message.date;
				message.m_senderID = resp.profile;
				message.m_recipientID = TheGameSpyInfo->getLocalProfileID();
				message.m_recipientNick = TheGameSpyInfo->getLocalBaseName();
				message.m_message = resp.arg.message.text;
				// insert status into box
				BuddyInfoMap *m = TheGameSpyInfo->getBuddyMap();
				BuddyInfoMap::iterator senderIt = m->find(message.m_senderID);
				AsciiString nick;
				if (senderIt != m->end())
					nick = senderIt->second.m_name.str();
				else
					nick = resp.arg.message.nick;
				message.m_senderNick = nick;
				addBuddyMessage(message);

				bfme_showNotificationBox_4ECD10(message);
			}
			break;
			case BuddyResponse::BUDDYRESPONSE_REQUEST: {
				if (TheGameSpyInfo->isSavedIgnored(resp.profile))
				{
					BuddyRequest request;
					request.type = 8;
					request.profile = resp.profile;
					TheGameSpyBuddyMessageQueue->addRequest(request);
					break;
				}
				BuddyInfoMap *existing = TheGameSpyInfo->getBuddyMap();
				BuddyInfoMap::iterator existingIt = existing->find(resp.profile);
				if (existingIt != existing->end())
				{
					BuddyRequest request;
					request.type = 7;
					request.profile = resp.profile;
					TheGameSpyBuddyMessageQueue->addRequest(request);
					break;
				}
				// save request for future incarnations of the buddy window
				BuddyInfoMap *m = TheGameSpyInfo->getBuddyRequestMap();
				BuddyInfo info;
				info.m_countryCode = resp.arg.request.countrycode;
				info.m_email = resp.arg.request.email;
				info.m_name = resp.arg.request.nick;
				info.m_id = resp.profile;
				info.m_status = (GPEnum)0;
				info.m_statusString = resp.arg.request.text;
				(*m)[resp.profile] = info;

				updateBuddyInfo();
				// insert status into box
				lastNotificationWasStatus = FALSE;
				numOnlineInNotification = 0;
				BuddyMessage message;
				message.m_timestamp = 0;
				message.m_recipientID = TheGameSpyInfo->getLocalProfileID();
				message.m_recipientNick = TheGameSpyInfo->getLocalBaseName();
				message.m_senderNick = info.m_name;
				message.m_message = TheGameText->fetch("Buddy:AddNotification");
				message.m_message.format(message.m_message, message.m_senderNick.str());
				addBuddyMessage(message);
				bfme_showNotificationBox_4ECD10(message);
			}
			break;
			case BuddyResponse::BUDDYRESPONSE_STATUS: {
				BuddyInfoMap *m = TheGameSpyInfo->getBuddyMap();
				BuddyInfoMap::const_iterator bit = m->find(resp.profile);
				Bool seenPreviously = FALSE;
				GPEnum oldStatus = GP_OFFLINE;
				GPEnum newStatus = resp.arg.status.status;
				if (bit != m->end())
				{
					seenPreviously = TRUE;
					oldStatus = (*m)[resp.profile].m_status;
				}
				BuddyInfo info;
				info.m_countryCode = resp.arg.status.countrycode;
				info.m_email = resp.arg.status.email;
				info.m_name = resp.arg.status.nick;
				info.m_id = resp.profile;
				info.m_status = newStatus;
				info.m_statusString = UnicodeString(
				    MultiByteToWideCharSingleLine(resp.arg.status.statusString).c_str());
				info.m_locationString =
				    UnicodeString(MultiByteToWideCharSingleLine(resp.arg.status.location).c_str());
				(*m)[resp.profile] = info;

				if (TheGameSpyInfo->isBuddy(resp.profile))
				{
					BuddyInfoMap *requests = TheGameSpyInfo->getBuddyRequestMap();
					if (requests->find(resp.profile) != requests->end())
					{
						BuddyRequest request;
						request.type = 7;
						request.profile = resp.profile;
						TheGameSpyBuddyMessageQueue->addRequest(request);
						reinterpret_cast<Rva004EE060Tree *>(requests)->erase(resp.profile);
					}
				}
				updateBuddyInfo();
				PopulateLobbyPlayerListbox();
				RefreshGameListBoxes();
				BuddyMessage message;
				message.m_timestamp = 0;
				message.m_recipientID = TheGameSpyInfo->getLocalProfileID();
				message.m_recipientNick = TheGameSpyInfo->getLocalBaseName();
				message.m_senderNick = info.m_name;

				if ((newStatus == GP_OFFLINE && seenPreviously) ||
				    (newStatus == GP_ONLINE && (oldStatus == GP_OFFLINE || !seenPreviously)))
				{
					// insert status into box
					AsciiString marker;
					marker.format("Buddy:%lsNotification", info.m_statusString.str());

					lastNotificationWasStatus = TRUE;
					if (newStatus != GP_OFFLINE)
						++numOnlineInNotification;

					message.m_message = TheGameText->fetch(marker);
					message.m_message.format(message.m_message, message.m_senderNick.str());
					addBuddyMessage(message);
					bfme_showNotificationBox_4ECD10(message);
				}
				else if (newStatus == GP_RECV_GAME_INVITE && !seenPreviously)
				{
					lastNotificationWasStatus = TRUE;
					if (newStatus != GP_OFFLINE)
						++numOnlineInNotification;

					message.m_message = TheGameText->fetch("Buddy:OnlineNotification");
					message.m_message.format(message.m_message, message.m_senderNick.str());
					addBuddyMessage(message);
					bfme_showNotificationBox_4ECD10(message);
				}
			}
			break;
			}
		}
	}
	if (Rva012F4248NotificationActive && timeGetTime() > noticeExpires)
	{
		bfmeGo1086B();
	}
}

// The retail tree insert above constructs its node through this _Construct; the
// insert used to instantiate it here, so it is instantiated explicitly to keep
// supplying it.
template void _STL::_Construct<BuddyInfoPair, BuddyInfoPair>( BuddyInfoPair *, const BuddyInfoPair & );
