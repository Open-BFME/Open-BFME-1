// cl: /O2 /DNDEBUG /MD /EHsc
//
// Retail 0x0009F560 is the SkirmishPreferences profile-removal helper.  The
// owner is established by vtable 0x010806B0, the UserNames list at this+0x14,
// and the named Skirmish screen path that passes the current username through
// this object.  The public method name is unresolved, so keep the method
// address-derived while preserving the proven class and ABI.

typedef bool Bool;
typedef unsigned short WideChar;

class UnicodeString;
class AsciiString;

template <class T> class StringBase
{
	friend class UnicodeString;
	friend class AsciiString;

public:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);
	void releaseBuffer(void);
	void concat(const T *text, int length);

	private:
	~StringBase();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	__forceinline AsciiString(void) { *(void **)this = 0; }
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	void translate(const UnicodeString &text);
	void concat(const char *text, int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString(void) {}
};

class Rva0009F090WideListData
{
public:
	void remove(const UnicodeString &value);

private:
	void *m_head;
};

class SkirmishPreferences
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual Bool slot14(AsciiString filename) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1c(void) = 0;

	void Rva0009F560(UnicodeString value);

private:
	unsigned char m_unmodelled_04[0x10];
	Rva0009F090WideListData m_userNames;
};

// ?Rva0009F560@SkirmishPreferences@@QAEXVUnicodeString@@@Z
void SkirmishPreferences::Rva0009F560(UnicodeString value)
{
	m_userNames.remove(value);

	AsciiString filename;
	filename.translate(value);
	filename.concat((const char *)0x0108066c, 0x11);
	slot14(filename);
}
