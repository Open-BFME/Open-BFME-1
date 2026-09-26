// cl: /DNDEBUG /MD /EHsc
//
// GameSpyLoginPreferences::getDateForEmail.  The public caller in
// WOLLoginMenu.cpp supplies the email and three output strings; the retail
// object has the password map at +0x14, nick map at +0x20, and date map at
// +0x2c.  Keep the string and map views local to this split body so the
// standalone reconstruction does not alter the shared headers.

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase(void) : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}

	int getLength(void) const
	{
		return m_data ? m_data->length : 0;
	}

	char getCharAt(int index) const
	{
		return m_data ? m_data->data[index] : 0;
	}

	void format(AsciiString format, ...);

	static AsciiString TheEmptyString;
};

struct PassMapNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;
};

class PassMap
{
public:
	PassMapNode *find(const AsciiString &key);
	AsciiString &operator[](const AsciiString &key);
	PassMapNode *end(void) const { return m_header; }

private:
	PassMapNode *m_header;
	unsigned char m_unreconstructed_04[0x08];
};

typedef PassMap DateMap;

class UserPreferences
{
public:
	virtual ~UserPreferences();

private:
	unsigned char m_unreconstructed_04[0x10];
};

class GameSpyLoginPreferences : public UserPreferences
{
public:
	AsciiString getDateForEmail(AsciiString email, AsciiString &month,
		AsciiString &date, AsciiString &year);

private:
	PassMap m_emailPasswordMap;
	PassMap m_emailNickMap;
	DateMap m_emailDateMap;
};

// ?getDateForEmail@GameSpyLoginPreferences@@QAE?AVAsciiString@@V2@AAV2@11@Z
AsciiString GameSpyLoginPreferences::getDateForEmail(AsciiString email,
	AsciiString &month, AsciiString &date, AsciiString &year)
{
	if (m_emailDateMap.find(email) == m_emailDateMap.end())
		return AsciiString::TheEmptyString;

	AsciiString fullDate = m_emailDateMap[email];
	if (fullDate.getLength() != 8)
		return AsciiString::TheEmptyString;

	month.format("%c%c", fullDate.getCharAt(0), fullDate.getCharAt(1));
	date.format("%c%c", fullDate.getCharAt(2), fullDate.getCharAt(3));
	year.format("%c%c%c%c", fullDate.getCharAt(4), fullDate.getCharAt(5),
		fullDate.getCharAt(6), fullDate.getCharAt(7));
	return m_emailDateMap[email];
}
