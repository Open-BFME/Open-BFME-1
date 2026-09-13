// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The retail body at 0x00082970 is reached by WOLLoginMenuInit immediately
// after operator new(0x38).  It is the GameSpyLoginPreferences constructor:
// UserPreferences occupies +0x00..+0x13, the three STLport maps occupy
// +0x14, +0x20, and +0x2c, and the constructor finishes by loading the default
// GameSpyLogin.ini through the derived virtual load slot.  This ABI slice is
// deliberately local; the original naked recovery TU was retired only after
// this constructor name and body were byte-verified.  Its exact bytes remain
// recoverable through the tombstone recorded for the former false getEmails row.

#include <map>
#include <list>

typedef bool Bool;

template <class T> class StringBase
{
friend class AsciiString;

private:
	StringBase(const T *text);
	~StringBase();
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

typedef std::list<AsciiString> AsciiStringList;
typedef std::map<AsciiString, AsciiString> PassMap;
typedef std::map<AsciiString, AsciiStringList> NickMap;
typedef std::map<AsciiString, AsciiString> DateMap;

class UserPreferences
{
public:
	UserPreferences();
	virtual ~UserPreferences();
	virtual Bool load(AsciiString filename);
	virtual Bool write(void);

private:
	unsigned char m_unreconstructed_04[0x10];
};

class GameSpyLoginPreferences : public UserPreferences
{
public:
	GameSpyLoginPreferences();
	virtual ~GameSpyLoginPreferences();
	virtual Bool load(AsciiString filename);
	virtual Bool write(void);

private:
	PassMap m_emailPasswordMap;
	NickMap m_emailNickMap;
	DateMap m_emailDateMap;
};

// ??0GameSpyLoginPreferences@@QAE@XZ
GameSpyLoginPreferences::GameSpyLoginPreferences(void)
{
	load("GameSpyLogin.ini");
}
