struct Rva006C9270GlobalData1782
{
	unsigned char m_pad[0x2c];
	int m_xResolution;
	int m_yResolution;
};

// Retail's global at 0x012ED5C8 is EA's `GlobalData *TheWritableGlobalData`,
// defined once in Common/GlobalData.cpp.  Rva006C9270GlobalData1782 above is
// this TU's view of the pointee, so the canonical global is forward declared
// and the cast at the use is the whole translation.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase(void);

	void set(const StringBase<T> &other);
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void);

	void format(AsciiString format, ...);
	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
};

namespace _STL
{
template <class T> struct less {};
template <class T> class allocator {};
template <class First, class Second> struct pair {};

template <class Key, class Value, class Compare = less<Key>,
	class Allocator = allocator<pair<const Key, Value> > >
class map
{
public:
	Value &operator[](const Key &key);

private:
	void *m_header;
	unsigned int m_size;
	unsigned int m_allocator;
};
}

typedef _STL::map<AsciiString, AsciiString, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, AsciiString> > >
	PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences(void);
	virtual bool load(AsciiString filename);
	virtual bool write(void);

private:
	AsciiString m_filename;
};

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences(void);
	virtual ~OptionPreferences(void);
};

class ClientRoot4120
{
public:
	void bfmeCloseHV(void);
	void bfmeOpenHV(void);

	unsigned char m_pad[0xc6];
	unsigned char m_resolutionChangePending;
};

extern ClientRoot4120 *TheGameClient;

struct Rva005A63D0Mouse
{
	void bfmeSetHV(int flag);
};

// Retail's singleton at 0x012F4C5C is EA's Mouse *TheMouse; (defined once in
// GameClient/Input/Mouse.cpp).  This TU keeps its own view of the layout and
// casts at the use so the reference links to the one global.
class Mouse;
extern Mouse *TheMouse;

void ClientRoot4120::bfmeCloseHV(void)
{
	m_resolutionChangePending = 0;

	OptionPreferences optionPreferences;
	AsciiString value;
	value.format("%d %d",
		((Rva006C9270GlobalData1782 *)TheWritableGlobalData)->m_xResolution,
		((Rva006C9270GlobalData1782 *)TheWritableGlobalData)->m_yResolution);
	optionPreferences[AsciiString("Resolution")] = value;
	optionPreferences.write();
}

class BfmeOwnerHV
{
public:
	void bfmeEndHV(int reason);

	unsigned char m_bfmeHeadHV[0x25e];
	unsigned char m_bfmeFlagHV;
	unsigned char m_bfmeGapHV[5];
	int m_bfmeStateHV;
};

void BfmeOwnerHV::bfmeEndHV(int reason)
{
	if (m_bfmeStateHV == 8 && reason == 3)
	{
		if (m_bfmeFlagHV)
			TheGameClient->bfmeCloseHV();
		else
			TheGameClient->bfmeOpenHV();

		((Rva005A63D0Mouse *)TheMouse)->bfmeSetHV(0);
		m_bfmeStateHV = 0;
	}
}
