// ?SetInGameChatType@@YAXW4InGameChatType@@@Z
// partial score=0.98 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc
// BFME SetInGameChatType, retail 0x00511CC0 (450 bytes).
//
// This is the BFME APT implementation, not the Zero Hour window/gadget
// implementation.  The caller at 0x0055D7F0 passes mode 3 through ILT 28A51;
// the body stores it at InGameChat+0x25c, creates InGameChat.apt, localizes
// the selected Chat:* label, and writes APT:InGameChatReceivers.

typedef bool Bool;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};


template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	AsciiString &operator=(const char *text);
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

class WindowLayout
{
public:
	virtual void hide(Bool hide);
};

class GameWindowManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1A();
	virtual WindowLayout *winCreateLayout(AsciiString filename);
};

#define TheWindowManager (*(GameWindowManager **)0x012F1B40)

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1A();
	virtual void slot1B();
	virtual void slot1C();
	virtual void slot1D();
	virtual void slot1E();
	virtual void slot1F();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2A();
	virtual void slot2B();
	virtual void slot2C();
	virtual void slot2D();
	virtual void slot2E();
	virtual void slot2F();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3A();
	virtual void slot3B();
	virtual void slot3C();
	virtual void slot3D();
	virtual void slot3E();
	virtual void slot3F();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot4A();
	virtual void slot4B();
	virtual void slot4C();
	virtual void slot4D();
	virtual void slot4E();
	virtual void slot4F();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual Bool slot154();
};

#define TheInGameUI (*(InGameUI **)0x012F148C)
#define TheDisconnectMenu (*(void **)0x012F4964)

class Rva00367E30Logic
{
private:
	char m_pad10C[0x10c];

public:
	int m_field10C;
	char m_pad110[8];
	void *m_field118;
};

#define TheBfmeGameLogic (*(Rva00367E30Logic **)0x012F0898)

class GameInfo
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual Bool slot02C();
};

#define TheGameInfo (*(GameInfo **)0x012F708C)

class Rva006C9270GlobalData
{
private:
	char m_padB0C[0xb0c];

public:
	int m_fieldB0C;
};

#define TheWritableGlobalData (*(Rva006C9270GlobalData **)0x012ED5C8)

class Rva005127A0InGameChat
{
public:
	char m_pad25C[0x25c];
	int m_chatType;
};

#define g_Rva005127A0InGameChat (*(Rva005127A0InGameChat **)0x012F4988)

class Player
{
public:
	bool isPlayerActive() const;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const
	{
		return *(Player **)((const char *)this + 0xc);
	}
};

#define ThePlayers (*(PlayerList **)0x012ED748)

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);
};

#define TheGameText (*(GameTextInterface **)0x012F147C)

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};

#define g_theWindowManager (*(WindowManager **)0x012F19E8)

enum InGameChatType
{
	INGAME_CHAT_ALLIES = 0,
	INGAME_CHAT_EVERYONE = 1,
	INGAME_CHAT_PLAYERS = 2,
	INGAME_CHAT_BUDDIES = 3
};

void SetInGameChatType(InGameChatType chatType)
{
	if (TheBfmeGameLogic->m_field10C == 3)
		return;

	if (TheInGameUI->slot154())
		return;

	if (TheDisconnectMenu != 0)
		return;

	if (TheBfmeGameLogic != 0 && TheBfmeGameLogic->m_field118 != 0)
		return;

	if (chatType != INGAME_CHAT_BUDDIES)
	{
		if (!TheGameInfo->slot02C() && TheWritableGlobalData->m_fieldB0C != 0)
			return;
	}

	if (g_Rva005127A0InGameChat != 0)
		return;

	TheWindowManager->winCreateLayout(AsciiString("InGameChat.apt"))->hide(0);

	if (g_Rva005127A0InGameChat == 0)
		return;

	g_Rva005127A0InGameChat->m_chatType = chatType;

	AsciiString label;
	if (chatType == INGAME_CHAT_EVERYONE)
	{
		if (ThePlayers->getLocalPlayer()->isPlayerActive())
			label = "Chat:Everyone";
		else
			label = "Chat:Observers";
	}
	else if (chatType == INGAME_CHAT_ALLIES)
		label = "Chat:Allies";
	else if (chatType == INGAME_CHAT_PLAYERS)
		label = "Chat:Players";
	else if (chatType == INGAME_CHAT_BUDDIES)
		label = "Chat:Buddies";

	AsciiString variableName("APT:InGameChatReceivers");
	g_theWindowManager->bfme_setAptText(variableName, TheGameText->fetch(label, 0));
}
