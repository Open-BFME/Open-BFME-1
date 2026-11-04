// cl: /DNDEBUG /MD /EHsc

// LANAPI::OnChat, 0x00689BD0, 653 bytes (ret 0x10 at +0x28A, int3 from +0x28D).
//
// Identity: LANAPI vtable slot 35 (+0x8C); the matched LANAPI::handleChat
// (0x0068B6A0) and LANAPI::RequestChat (0x006865C0) dispatch through that slot
// with an address-pair pointer as the second argument
// (targets/game/reverse/identity_evidence/0x00689bd0-lanapi-onchat.md).
// The Zero Hour twin is LANAPICallbacks.cpp LANAPI::OnChat; BFME differs in
// three measured ways, each read off the retail body:
//   - one chat listbox, the member at this+0x5C, replaces ZH's three-way
//     lobby / score screen / game-options window choice;
//   - the "is this me" test compares the sender's IP/port pair with the pair
//     returned by virtual slot 55 (+0xDC) instead of ZH's m_localIP scalar;
//   - GadgetListBoxAddEntryText takes a trailing Bool (pushed as 1).
// The three color constants are the ZH LANAPICallbacks.cpp table at
// 0x012BA0C8 / 0x012BA0D0 / 0x012BA0D4 (retail values 0xFFFF00FF,
// 0xFF80FFFF, 0xFFFFFFFF in ZH declaration order).
//
// The UnicodeString view is TU-local: retail inlines concat(UnicodeString)
// (null-data test, +8 text, +4 word length), concat(const WideChar *) as a
// wcslen import call plus concat(text, len), concat(WideChar) through a stack
// slot, and assignment from a UnicodeString straight to StringBase::set,
// while assignment from a literal stays an out-of-line call.  No shared
// header carries that exact inline set.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;
typedef bool Bool;
typedef Int Color;

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const WideChar *text);

template <typename T> class StringBase
{
	friend class UnicodeString;

public:
	void concat(const T *text, int length);
	void set(const StringBase<T> &other);

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	void releaseBuffer();

	Header *m_data;
};

extern const WideChar BFMEEmptyUnicodeString;

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() { releaseBuffer(); }

	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}
	UnicodeString &operator=(const WideChar *text);

	const WideChar *str() const { return m_data ? m_data->m_text : &BFMEEmptyUnicodeString; }
	Int getLength() const { return m_data ? m_data->m_length : 0; }

	void concat(const UnicodeString &other) { StringBase<WideChar>::concat(other.str(), other.getLength()); }
	void concat(const WideChar *text) { StringBase<WideChar>::concat(text, wcslen(text)); }
	void concat(WideChar c) { StringBase<WideChar>::concat(&c, 1); }
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class GameWindow;

Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, Color color,
	Int row, Int column, Bool overwrite);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, Int row, Int column);

class LanguageFilter
{
public:
	void filterLine(UnicodeString &line);
};
extern LanguageFilter *TheLanguageFilter;

class MultiplayerColorDefinition
{
public:
	Color getColor(void) const { return m_color; }

	UnsignedByte m_bfmeBeforeColor[0x10];
	Color m_color;						// +0x10
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(Int which);
};
extern MultiplayerSettings *TheMultiplayerSettings;

class GameSlot
{
public:
	Int getColor(void) const { return m_color; }

	UnsignedByte m_bfmeBeforeColor[0x0c];
	Int m_color;						// +0x0c
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slotNum);
};

class LANGameInfo : public GameInfo
{
public:
	Int getSlotNum(UnicodeString userName);
};

extern const Color chatActionColor;
extern const Color chatLocalActionColor;
extern const Color chatSystemColor;

class LANAPIInterface
{
public:
	enum ChatType
	{
		LANCHAT_NORMAL = 0,
		LANCHAT_EMOTE,
		LANCHAT_SYSTEM
	};
};

class LANAPI : public LANAPIInterface
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void _bfme_slot06(void) = 0;
	virtual void _bfme_slot07(void) = 0;
	virtual void _bfme_slot08(void) = 0;
	virtual void _bfme_slot09(void) = 0;
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
	virtual void OnChat(UnicodeString player, BfmeNetAddress *address,
		UnicodeString message, ChatType format);	// slot 35, vtable+0x8C
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
	virtual void _bfme_slot54(void) = 0;
	virtual BfmeNetAddress *getLocalAddress(void) = 0;	// slot 55, vtable+0xDC

protected:
	UnsignedByte m_bfmeHeadA[0x40 - 4];
	LANGameInfo *m_currentGame;				// +0x40
	UnsignedByte m_bfmeHeadB[0x5c - 0x44];
	GameWindow *m_chatWindow;				// +0x5c
};

// ?OnChat@LANAPI@@UAEXVUnicodeString@@PAUBfmeNetAddress@@0W4ChatType@LANAPIInterface@@@Z
void LANAPI::OnChat(UnicodeString player, BfmeNetAddress *address,
	UnicodeString message, ChatType format)
{
	if (m_chatWindow == 0)
		return;

	Int index = -1;
	UnicodeString unicodeChat;
	switch (format)
	{
		case LANCHAT_SYSTEM:
			unicodeChat = L"";
			unicodeChat.concat(message);
			unicodeChat.concat(L"");
			index = GadgetListBoxAddEntryText(m_chatWindow, unicodeChat, chatSystemColor, -1, -1, true);
			break;
		case LANCHAT_EMOTE:
		{
			unicodeChat = player;
			unicodeChat.concat(L' ');
			unicodeChat.concat(message);
			BfmeNetAddress *local = getLocalAddress();
			if (address->m_ip == local->m_ip && address->m_port == local->m_port)
				index = GadgetListBoxAddEntryText(m_chatWindow, unicodeChat, chatLocalActionColor, -1, -1, true);
			else
				index = GadgetListBoxAddEntryText(m_chatWindow, unicodeChat, chatActionColor, -1, -1, true);
			break;
		}
		case LANCHAT_NORMAL:
		default:
		{
			TheLanguageFilter->filterLine(message);

			Color chatColor = -1;
			if (m_currentGame)
			{
				Int slotNum = m_currentGame->getSlotNum(player);
				if (slotNum >= 0)
				{
					GameSlot *gs = m_currentGame->getSlot(slotNum);
					if (gs)
					{
						MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(gs->getColor());
						if (def)
							chatColor = def->getColor();
					}
				}
			}

			unicodeChat = L"[";
			unicodeChat.concat(player);
			unicodeChat.concat(L"] ");
			unicodeChat.concat(message);
			BfmeNetAddress *local = getLocalAddress();
			if (address->m_ip == local->m_ip && address->m_port == local->m_port)
				index = GadgetListBoxAddEntryText(m_chatWindow, unicodeChat, chatColor, -1, -1, true);
			else
				index = GadgetListBoxAddEntryText(m_chatWindow, unicodeChat, chatColor, -1, -1, true);
			break;
		}
	}
	GadgetListBoxSetItemData(m_chatWindow, (void *)-1, index, 0);
}
