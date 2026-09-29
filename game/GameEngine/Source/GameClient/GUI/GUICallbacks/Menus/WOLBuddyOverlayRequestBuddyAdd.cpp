// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// RequestBuddyAdd, retail 0x004EDAD0, 818 bytes; ZH twin in WOLBuddyOverlay.cpp.
// Identity: WOLBuddyOverlayRCMenuSystem (0x004EFED0) calls it twice through
// ILT 0x0001672A with (profileID, AsciiString nick) cdecl, the two ZH call
// sites. The body fetches "GUI:BuddyAddReq", queues a BUDDYREQUEST_ADDBUDDY (5)
// request, fetches "Buddy:InviteSent" and "Buddy:InviteSentToPlayer", plays
// "GUIMessageReceived" and ends in showNotificationBox (0x004EBA70), line for
// line with the ZH twin, EH states 0..10 in ZH declaration order.
//
// STLport: _STLP_NO_EXCEPTIONS lets list::push_back inline _M_create_node
// (docs/shape_levers.md, InGameUISelectDrawable.cpp 0x004462D0 row), and
// _STLP_USE_STATIC_LIB makes the node allocate a direct call to
// __node_alloc::_M_allocate (0x0082E540) instead of a dllimport.

#define _STLP_NO_EXCEPTIONS 1
#include <time.h>
#include <list>

#include "string_base.h"
#include "ascii_string.h"
#include "unicode_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int GPProfile;
typedef wchar_t WideChar;

// Retail inlines the null-checked data pointer read at every str() site.

inline UnicodeString::UnicodeString()
{
	m_text = 0;
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

#define MAX_BUDDY_CHAT_LEN 128

// upstream layout: inputs/reference/shims/buddythread/GameNetwork/GameSpy/BuddyThread.h
class BuddyRequest
{
public:
	enum
	{
		BUDDYREQUEST_LOGIN,
		BUDDYREQUEST_RELOGIN,
		BUDDYREQUEST_LOGOUT,
		BUDDYREQUEST_MESSAGE,
		BUDDYREQUEST_LOGINNEW,
		BUDDYREQUEST_ADDBUDDY,
		BUDDYREQUEST_DELBUDDY,
		BUDDYREQUEST_OKADD,
		BUDDYREQUEST_DENYADD,
		BUDDYREQUEST_SETSTATUS,
		BUDDYREQUEST_DELETEACCT,
		BUDDYREQUEST_MAX
	} buddyRequestType;

	union
	{
		struct
		{
			GPProfile id;
			WideChar text[MAX_BUDDY_CHAT_LEN];
		} addbuddy;
		// BFME's BuddyRequest is 0x2B8 bytes (getRequest @0x0063C770 copies 0xAE dwords).
		char bytes[0x2B8 - 4];
	} arg;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/BuddyThread.h
class GameSpyBuddyMessageQueueInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void addRequest(const BuddyRequest &req) = 0;
};

extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameText.h
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
	virtual void slot24() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/BuddyDefs.h
class BuddyMessage
{
public:
	BuddyMessage() {}
	BuddyMessage(const BuddyMessage &);
	~BuddyMessage();

	UnsignedInt m_timestamp;
	GPProfile m_senderID;
	AsciiString m_senderNick;
	GPProfile m_recipientID;
	AsciiString m_recipientNick;
	UnicodeString m_message;
};

typedef _STL::list<BuddyMessage> BuddyMessageList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
// Slot +0x5C getBuddyMessages, +0x70 getLocalProfileID and +0x88
// getLocalBaseName are the ones the matched insertChat (0x004EB6B0) and
// addBuddyMessage (0x004EDFA0) TUs already use.
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
	virtual void slot_054();
	virtual void slot_058();
	virtual BuddyMessageList *getBuddyMessages(void);
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

// Retail AudioEventRTS is 0x70 bytes; the constructor and destructor are the
// ledger's out-of-line bodies at 0x000B2CC0 (ILT 0x00025306) and 0x000B31F0
// (ILT 0x00026F35).
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int arg);
	~AudioEventRTS();

private:
	unsigned int m_storage[0x70 / 4];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
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
	virtual UnsignedInt addAudioEvent(const AudioEventRTS *eventToAdd) = 0;
};

extern AudioManager *TheAudio;

// AsciiString::TheEmptyString (0x01336E50); ascii_string.h does not declare the
// static member, so the existing namespace-scope pin spelling is used.
extern const AsciiString Rva01336E50EmptyString;

// ZH file statics of WOLBuddyOverlay.cpp (retail 0x012F4240 / 0x012F4244).
extern Bool lastNotificationWasStatus;
extern Int numOnlineInNotification;

void insertChat(BuddyMessage msg);
// showNotificationBox (ZH) -- ledger name of the body at 0x004EBA70.
void Rva004EBA70NotificationDispatch(AsciiString nick, UnicodeString message);

// ?RequestBuddyAdd@@YAXHVAsciiString@@@Z
void RequestBuddyAdd(Int profileID, AsciiString nick)
{
	// request to add a buddy
	BuddyRequest req;
	req.buddyRequestType = BuddyRequest::BUDDYREQUEST_ADDBUDDY;
	req.arg.addbuddy.id = profileID;
	UnicodeString buddyAddstr;
	buddyAddstr = TheGameText->fetch("GUI:BuddyAddReq");
	wcsncpy(req.arg.addbuddy.text, buddyAddstr.str(), MAX_BUDDY_CHAT_LEN);
	req.arg.addbuddy.text[MAX_BUDDY_CHAT_LEN-1] = 0;
	TheGameSpyBuddyMessageQueue->addRequest(req);

	UnicodeString s;
	Bool exists = true;
	s.format(TheGameText->fetch("Buddy:InviteSent", &exists));
	if (!exists)
	{
		// no string yet.  don't display.
		return;
	}

	// save message for future incarnations of the buddy window
	BuddyMessageList *messages = TheGameSpyInfo->getBuddyMessages();
	BuddyMessage message;
	message.m_timestamp = time(0);
	message.m_senderID = 0;
	// ZH `m_senderNick = "";` -- retail calls the two-argument setter set("", 0).
	((StringBase<char> *)&message.m_senderNick)->set("", 0);
	message.m_recipientID = TheGameSpyInfo->getLocalProfileID();
	message.m_recipientNick = TheGameSpyInfo->getLocalBaseName();
	message.m_message.format(TheGameText->fetch("Buddy:InviteSentToPlayer"), nick.str());

	// insert status into box
	messages->push_back(message);

	// put message on screen
	insertChat(message);

	// play audio notification
	// ZH passes the name only; retail's constructor takes a second int, pushed as 2.
	AudioEventRTS buddyMsgAudio("GUIMessageReceived", 2);
	if (TheAudio)
	{
		TheAudio->addAudioEvent(&buddyMsgAudio);
	}

	lastNotificationWasStatus = false;
	numOnlineInNotification = 0;
	Rva004EBA70NotificationDispatch(Rva01336E50EmptyString, s);
}
