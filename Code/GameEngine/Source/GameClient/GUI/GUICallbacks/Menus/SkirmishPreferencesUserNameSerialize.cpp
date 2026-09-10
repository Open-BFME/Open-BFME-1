// ?Rva0009FC90@Gen0009FC90Owner@@QAEXXZ
// ?Rva0009FC90@Gen0009FC90Owner@@QAEXXZ
// BFME UserNames-list serializer.  The write helper at 0x0009FEB0 and the
// insertion helper at 0x0009FDF0 both reach this body through the named
// incremental-link thunk.  The constructor vtable 0x010806B0 fixes the
// UserPreferences/list layout used here.

#define _STLP_NO_EXCEPTIONS 1

typedef bool Bool;
typedef unsigned short WideChar;

template <class T> struct StringInlineData
{
	unsigned short m_refCount;
	unsigned short m_reserved;
	unsigned short m_length;
	unsigned short m_pad;
	T m_text[1];
};

class AsciiString;
class UnicodeString;

template <class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	StringBase(void) : m_data(0) {}
	void concat(const T *text, int length);

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void set(const StringBase<T> &other);
	void releaseBuffer(void);

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(void) : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString() {}

	int getLength(void) const
	{
		StringInlineData<WideChar> *data =
			m_data;
		return data ? data->m_length : 0;
	}

	const WideChar *str(void) const
	{
		StringInlineData<WideChar> *data =
			m_data;
		return data ? data->m_text : (const WideChar *)0x0107388C;
	}

	void concat(const WideChar *text, int length)
	{
		StringBase<WideChar>::concat(text, length);
	}
};

AsciiString UnicodeStringToQuotedPrintable(UnicodeString original);

__declspec(dllimport) unsigned __cdecl bfmeLenVGI(const WideChar *text);

struct PreferenceNode
{
	unsigned char m_pad[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	AsciiString &operator[](const AsciiString &key);

private:
	PreferenceNode *m_end;
	unsigned char m_unreconstructed[8];
};

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
	virtual Bool load(AsciiString filename);
	virtual Bool write(void);

private:
	AsciiString m_filename;
};

struct UserNameNode
{
	UserNameNode *m_next;
	UserNameNode *m_prev;
	UnicodeString m_value;
};

struct UserNameList
{
	UserNameNode *m_end;
};

class Gen0009FC90Owner : public UserPreferences
{
public:
	void Rva0009FC90(void);

private:
	UserNameList m_userNames;
};

void Gen0009FC90Owner::Rva0009FC90(void)
{
	UserNameNode *it = m_userNames.m_end->m_next;
	UnicodeString names;

	while (it != m_userNames.m_end)
	{
		names.concat(it->m_value.str(), it->m_value.getLength());

		const WideChar *comma = (const WideChar *)0x010806D8;
		names.concat(comma, bfmeLenVGI(comma));
		it = it->m_next;
	}

	(*this)["UserNames"] = UnicodeStringToQuotedPrintable(names);
}
