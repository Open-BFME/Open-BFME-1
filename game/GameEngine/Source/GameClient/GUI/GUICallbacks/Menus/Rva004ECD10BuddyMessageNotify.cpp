// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Rva004ECD10BuddyMessageNotify retail 0x004ECD10 557 bytes; ZH-family home is
// WOLBuddyOverlay.cpp (the wb1-run attribute) and the BFME2 twin
// Rva00416589 (BuddyDefsSendMessage.cpp) is the same body: format
// "[%hs] %s", hand the text to the in-game chat, and when the chat did not
// take it play "GUIMessageReceived" and pop the notification box.
//
// IDENTITY.  The Open-BFME5 lift's name
// ?showNotificationBox@@YAXVAsciiString@@VUnicodeString@@@Z is REFUTED: the
// body takes ONE BuddyMessage BY VALUE (24 bytes at [esp+0x9c..0xb0] on
// entry, destroyed at 0x004ECF22 by ~BuddyMessage 0x004EA4B0 with this =
// the argument slot itself).  Matched callers HandleBuddyResponses
// (0x004EE510, four sites) and Rva004EDED0BuddyMessageNotification
// (0x004EDED0) each build 0x18 bytes of by-value argument and the caller
// cleans them (cdecl), and dup_004EE1C0 calls through the raw ILT thunk
// 0x00037FC9.  No FunctionLexicon row names this address, so the row keeps
// the address token; the second Rva005127A0Forward argument is
// GameSpyColor[8] (0x012B9220 = GSCOLOR_PLAYER_BUDDY, the same color the
// BFME2 twin passes), not an unidentified channel global.
//
// ABIs: UnicodeString::format is the __cdecl (UnicodeString, ...) overload
// 0x00889190 with the fmt word constructed in place (the L"[%hs] %s" temp
// through StringBase<unsigned short>::StringBase(const unsigned short *)
// 0x00888DE0, the fetch result written straight into the slot by the
// sret-qualified virtual fetch at vtable +0x28).  AudioEventRTS is the
// two-argument constructor 0x000B2CC0 (ILT 0x00025306); the snippet cap is
// 30 characters while BFME2's twin caps at 11.

#include "string_base.h"
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef int Color;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int GPProfile;

// Retail inlines the null-checked data pointer read at every str() site.

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

// ZH file statics of WOLBuddyOverlay.cpp (retail 0x012F4240 / 0x012F4244).
extern Bool lastNotificationWasStatus;
extern Int numOnlineInNotification;

// GSCOLOR_PLAYER_BUDDY is index 8 (retail reads 0x012B9220 = GameSpyColor +0x20).
extern Color GameSpyColor[];

// Native bodies: Rva005127A0InGameChatForward.cpp and Rva004EBA70NotificationDispatch.cpp.
bool Rva005127A0Forward(UnicodeString text, int channel);
void Rva004EBA70NotificationDispatch(AsciiString nick, UnicodeString message);

// ?Rva004ECD10BuddyMessageNotify@@YAXVBuddyMessage@@@Z
void Rva004ECD10BuddyMessageNotify(BuddyMessage message)
{
	UnicodeString text;
	text.format(L"[%hs] %s", message.m_senderNick.str(), message.m_message.str());
	if (!Rva005127A0Forward(text, GameSpyColor[8]))
	{
		// play audio notification
		AudioEventRTS buddyMsgAudio("GUIMessageReceived", 2);
		if (TheAudio)
		{
			TheAudio->addAudioEvent(&buddyMsgAudio);
		}

		UnicodeString snippet = message.m_message;
		while (snippet.getLength() > 30)
			((StringBase<unsigned short> *)&snippet)->removeLastChar();

		UnicodeString notification;
		notification.format(TheGameText->fetch("Buddy:MessageNotification"), message.m_senderNick.str(), snippet.str());

		lastNotificationWasStatus = false;
		numOnlineInNotification = 0;
		Rva004EBA70NotificationDispatch(AsciiString::TheEmptyString, notification);
	}
}
