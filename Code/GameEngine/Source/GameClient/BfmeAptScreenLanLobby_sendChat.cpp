// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/asciistring_downloadmanager /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
//
// BfmeAptScreenLanLobby chat submission, retail 0x00518350 (553 bytes).
// The +0x390 LanLobbyUserNamePrefs and +0x3BC chat-entry GameWindow are the
// offsets established by BfmeAptScreenLanLobby_submitName.cpp.  The trim loop
// and the RequestChat tail are the ZH LanLobbyMenu GEM_EDIT_DONE chat path;
// the leading-slash branch is BFME's addition, keyed on L"me" at 0x01105890.

typedef unsigned short wchar_t;
typedef unsigned short WideChar;

template <typename T>
class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void releaseBuffer();

public:
	void set(const StringBase<T> &other);
	bool nextToken(StringBase<T> *out, const T *separators);
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

extern "C" __declspec(dllimport) int __cdecl iswspace(WideChar c);

extern const char g_bfmeEmptyUnicode[];

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const WideChar *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	static UnicodeString TheEmptyString;

	void set(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(other);
	}

	bool isEmpty() const
	{
		return !m_data || m_data->length == 0;
	}

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

	int compareNoCase(const WideChar *text) const
	{
		return StringBase<unsigned short>::compareNoCase(text);
	}

	UnicodeString &operator+=(const WideChar *text);
};

class GameWindow;
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);

class LANAPIInterface
{
public:
	enum ChatType
	{
		LANCHAT_NORMAL = 0,
		LANCHAT_EMOTE = 1,
		LANCHAT_SYSTEM = 2,
		LANCHAT_MAX = 3
	};
};

class LANAPI
{
public:
#define LANAPI_SLOT(N) virtual void bfmeRetailSlot##N() = 0;
	LANAPI_SLOT(00) LANAPI_SLOT(01) LANAPI_SLOT(02) LANAPI_SLOT(03)
	LANAPI_SLOT(04) LANAPI_SLOT(05) LANAPI_SLOT(06) LANAPI_SLOT(07)
	LANAPI_SLOT(08) LANAPI_SLOT(09) LANAPI_SLOT(10) LANAPI_SLOT(11)
	LANAPI_SLOT(12) LANAPI_SLOT(13) LANAPI_SLOT(14) LANAPI_SLOT(15)
#undef LANAPI_SLOT
	virtual void RequestChat(UnicodeString message,
		LANAPIInterface::ChatType format) = 0;
};

extern LANAPI *TheLAN;

class LanLobbyUserNamePrefs
{
public:
	UnicodeString getUserName();

	char m_unmodelled[0x14];
	UnicodeString m_userName;
};

class Gen_00479A60
{
public:
	int *m_table;
	int m_value;
	GameWindow *m_owner;
};

class BfmeAptScreenLanLobby
{
public:
	void sendChatRva00518350();

private:
	char m_unmodelled[0x390];
	LanLobbyUserNamePrefs m_userNamePrefs;
	int m_state;
	GameWindow *m_gameInfo;
	GameWindow *m_chat;
	GameWindow *m_customGamesList;
	GameWindow *m_customPlayerList;
	GameWindow *m_chatEntry;
	Gen_00479A60 m_nameEntry;
	GameWindow *m_startingResources;
};

// ?sendChatRva00518350@BfmeAptScreenLanLobby@@QAEXXZ
void BfmeAptScreenLanLobby::sendChatRva00518350()
{
	if (m_chatEntry == 0)
		return;

	UnicodeString txtInput;
	UnicodeString message;

	txtInput.set(GadgetTextEntryGetText(m_chatEntry));
	GadgetTextEntrySetText(m_chatEntry, UnicodeString::TheEmptyString);

	while (!txtInput.isEmpty() && iswspace(txtInput.getCharAt(0)))
		txtInput.set(UnicodeString(txtInput.str() + 1));

	if (txtInput.isEmpty())
		return;

	message.set(txtInput);

	if (message.getCharAt(0) == L'/')
	{
		UnicodeString remainder(message.str() + 1);
		UnicodeString token;
		remainder.nextToken(&token, 0);
		if (token.compareNoCase(L"me") == 0 && txtInput.getLength() >= 3)
		{
			message.set(m_userNamePrefs.getUserName());
			message += remainder.str();
		}
	}

	TheLAN->RequestChat(message, LANAPIInterface::LANCHAT_NORMAL);
}
