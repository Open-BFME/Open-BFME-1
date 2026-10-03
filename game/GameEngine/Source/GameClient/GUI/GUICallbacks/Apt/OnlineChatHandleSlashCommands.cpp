// cl: /DNDEBUG /MD /EHsc
//
// BfmeAptScreenOnlineChat slash commands, retail 0x00536530 (665 bytes, thiscall,
// ret 4). BFME's member form of Zero Hour's handleLobbySlashCommands
// (WOLLobbyMenu.cpp): the same "me" (0x01105890) and "refresh" (0x011070FC)
// commands.
// - Owner: the step-A call goes through ILT 0x00014182, already pinned as
//   BfmeAptScreenOnlineChat::Rva005337E0 (InitGadgets calls it with this).
// - The refresh tail repeats BfmeA1049::bfmeGo1049B (0x00535150) with force
//   set, sharing one timeGetTime import load: the +0x44 pointer and the +0x9C
//   timestamp are the same class.
// - The per-player caller is 0x00536870 via ILT 0x0044A7E1.
// The method name stays address-derived; the string model follows
// BfmeAptScreenLanLobby_sendChat.cpp.

typedef unsigned short WideChar;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

public:
	void set(const StringBase<T> &other);
	bool nextToken(StringBase<T> *out, const T *separators);
	void toLower();
	int compareNoCase(const T *text) const;

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

extern const char g_bfmeEmptyUnicode[];

class UnicodeString;

class AsciiString : private StringBase<char>
{
	friend class UnicodeString;

public:
	AsciiString() {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}

	const char *str() const
	{
		return m_data ? &m_data->data[0] : "";
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const WideChar *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	int getLength() const
	{
		return m_data ? m_data->length : 0;
	}

	WideChar getCharAt(int index) const
	{
		return m_data ? m_data->data[index] : 0;
	}

	const WideChar *str() const
	{
		return m_data ? &m_data->data[0]
		              : reinterpret_cast<const WideChar *>(g_bfmeEmptyUnicode);
	}

	bool nextToken(UnicodeString *out, const WideChar *separators)
	{
		return StringBase<unsigned short>::nextToken(out, separators);
	}

	void toLower()
	{
		StringBase<unsigned short>::toLower();
	}

	int compareNoCase(const WideChar *text) const
	{
		return StringBase<unsigned short>::compareNoCase(text);
	}

	void translate(const AsciiString &src);
	UnicodeString &operator+=(const UnicodeString &other);
};

class GameWindow;

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class GameSpyInfo
{
public:
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 ); GAMESPY_SLOT( 6 ); GAMESPY_SLOT( 7 );
	GAMESPY_SLOT( 8 ); GAMESPY_SLOT( 9 ); GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 );
	GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 ); GAMESPY_SLOT( 14 ); GAMESPY_SLOT( 15 );
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 );
	virtual const AsciiString *gamespySlot19( const char *name ) = 0;
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 );
	virtual AsciiString gamespySlot26() = 0;
	GAMESPY_SLOT( 27 );
	GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 ); GAMESPY_SLOT( 31 );
	GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 ); GAMESPY_SLOT( 35 );
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 ); GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 );
	GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 );
	virtual bool gamespySlot43() = 0;
	GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 ); GAMESPY_SLOT( 46 ); GAMESPY_SLOT( 47 );
	GAMESPY_SLOT( 48 ); GAMESPY_SLOT( 49 ); GAMESPY_SLOT( 50 ); GAMESPY_SLOT( 51 );
	GAMESPY_SLOT( 52 ); GAMESPY_SLOT( 53 ); GAMESPY_SLOT( 54 ); GAMESPY_SLOT( 55 );
	GAMESPY_SLOT( 56 ); GAMESPY_SLOT( 57 ); GAMESPY_SLOT( 58 ); GAMESPY_SLOT( 59 );
	GAMESPY_SLOT( 60 ); GAMESPY_SLOT( 61 );
	virtual void sendChat( UnicodeString message, bool isEmote, GameWindow *window ) = 0;
};
#undef GAMESPY_SLOT

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
void RefreshGameListBoxes();
void bfmeFree1049(void *p);

class BfmeAptScreenOnlineChat
{
public:
	bool Rva00536530HandleSlashCommands(UnicodeString uText);
	void Rva005337E0();
	void Rva00534380();

private:
	char m_unmodelled[0x40];
	GameWindow *m_window40;
	void *m_pointer44;
	char m_unmodelled48[0x9C - 0x48];
	unsigned m_time9C;
	unsigned m_timeA0;
};

bool BfmeAptScreenOnlineChat::Rva00536530HandleSlashCommands(UnicodeString uText)
{
	if (uText.getCharAt(0) != L'/')
		return false;

	UnicodeString remainder(uText.str() + 1);
	UnicodeString token;
	remainder.nextToken(&token, 0);
	token.toLower();

	if (token.compareNoCase(L"me") == 0 && uText.getLength() >= 3)
	{
		AsciiString name;
		UnicodeString message;
		const AsciiString *nick = reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->gamespySlot19(reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->gamespySlot26().str());
		if (nick)
			name = *nick;
		else
			name = reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->gamespySlot26();
		message.translate(name);
		message += UnicodeString(uText.str() + 3);
		reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->sendChat(message, false, m_window40);
		return true;
	}
	else if (token.compareNoCase(L"refresh") == 0)
	{
		bool refreshGames = reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->gamespySlot43();
		unsigned long (__stdcall *nowFunction)() = timeGetTime;
		if (refreshGames)
		{
			RefreshGameListBoxes();
			m_timeA0 = nowFunction();
		}
		// The body of 0x00535150 with force set, written out in place.
		Rva005337E0();
		bfmeFree1049(m_pointer44);
		Rva00534380();
		m_time9C = nowFunction();
		return true;
	}

	return false;
}
