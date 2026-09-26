// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x0009FDF0 is the SkirmishPreferences UserNames-list insertion
// helper.  The class identity is established by the constructor's vtable
// 0x010806B0, its list member at this+0x14, and the helper's immediate call
// through ILT 0x0002CB10 to the UserNames serializer at 0x0009FC90.  The
// public method name is unresolved, so this body remains address-derived.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;
typedef unsigned short WideChar;

class AsciiString;
class UnicodeString;

template <class T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	StringBase(void) : m_data(0) {}

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void set(const StringBase<T> &other);
	void releaseBuffer(void);

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(void) : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString() {}
};

struct PreferenceNode
{
	unsigned char m_pad[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const throw();

private:
	PreferenceNode *m_end;
	unsigned char m_unreconstructed[8];
};

class BfmeThingBRA
{
public:
	virtual void layoutAnchor(void);
	void bfmeOneBRA(void);
};

class Gen0009FDF0Owner : public BfmeThingBRA, public PreferenceMap
{
public:
	void Rva0009FDF0(UnicodeString value);

private:
	AsciiString m_filename;
	_STL::list<UnicodeString> m_userNames;
};

// ?Rva0009FDF0@Gen0009FDF0Owner@@QAEXVUnicodeString@@@Z
void Gen0009FDF0Owner::Rva0009FDF0(UnicodeString value)
{
	m_userNames.push_back(value);
	bfmeOneBRA();
}
