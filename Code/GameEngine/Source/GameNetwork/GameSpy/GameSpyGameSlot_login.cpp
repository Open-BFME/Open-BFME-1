// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// GameSpyGameSlot's login and locale strings.
//
// Two adjacent AsciiStrings at +0x70 and +0x74, which is what the reference's
// m_gameSpyLogin and m_gameSpyLocale are. The GameSpy stats-authkey command
// carries both, and processing it writes them straight onto the slot the
// command names -- which is how these three came to be on the delay-path call
// graph at all.
//
// The reference declares all three inline in the header; retail emits them, so
// they are out of line here. See NetCommandMsg_text.cpp for why AsciiString is
// StringBase<char> itself and why holders have to be friends of it.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

template <typename T>
class StringBase
{
	friend class GameSpyGameSlot;

public:
	void set(const StringBase<T> &src);
	StringBase<T> &operator=(const StringBase<T> &src) { set(src); return *this; }

private:
	StringBase(const StringBase<T> &src);
	~StringBase();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

typedef StringBase<char> AsciiString;

class GameSpyGameSlot
{
public:
	AsciiString getLoginName() const;
	void setLoginName(AsciiString name);
	void setLocale(AsciiString name);

	char m_padToLogin[0x70];						// GameSlot base, unpinned
	AsciiString m_gameSpyLogin;						// this+0x70
	AsciiString m_gameSpyLocale;					// this+0x74
};

AsciiString GameSpyGameSlot::getLoginName() const
{
	return m_gameSpyLogin;
}

void GameSpyGameSlot::setLoginName(AsciiString name)
{
	m_gameSpyLogin = name;
}

void GameSpyGameSlot::setLocale(AsciiString name)
{
	m_gameSpyLocale = name;
}
