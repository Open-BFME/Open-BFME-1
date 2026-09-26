// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// WOLLoginMenuInit allocates the 0x38-byte preference object and invokes its
// constructor; that constructor initializes the base/maps and calls this
// virtual load.  The retail body first delegates to UserPreferences::load,
// then walks the inherited preference map and imports pass_, date_, and nick_
// entries into the password, nickname, and date maps at +0x14, +0x20, and
// +0x2c respectively.  The standalone ABI below keeps the BFME base layout
// and the STLport map/list members local to this body.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <map>
#include <string.h>

typedef bool Bool;

template <class T> class StringBase
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
    StringBase(const StringBase<T> &other);
    ~StringBase();

public:
    bool startsWith(const T *text, int length) const;
    void set(const StringBase<T> &other);
    void set(const T *text, int length);
    bool nextToken(StringBase<T> *out, const T *delimiters);

private:
    Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(void) : StringBase<char>() {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString(void) {}

    AsciiString &operator=(const AsciiString &other)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
        return *this;
    }

    AsciiString &operator=(const char *text)
    {
        ((StringBase<char> *)this)->set(text, text ? strlen(text) : 0);
        return *this;
    }

    const char *str(void) const
    {
        return m_data ? (const char *)m_data + 8 : "";
    }

    bool nextToken(AsciiString *out, const char *delimiters)
    {
        return ((StringBase<char> *)this)->nextToken(
            (StringBase<char> *)out, delimiters);
    }
};

class GameSpyLoginAsciiStringLess
{
public:
    bool operator()(const AsciiString &lhs, const AsciiString &rhs) const;
};

namespace _STL
{
    template <>
    struct less<AsciiString> : public GameSpyLoginAsciiStringLess
    {
    };
}

typedef std::list<AsciiString> AsciiStringList;
typedef std::map<AsciiString, AsciiString> PreferenceMap;

class PassMap
{
public:
    AsciiString &operator[](const AsciiString &key);

private:
    unsigned char m_state[0x0c];
};

typedef PassMap DateMap;

class NickMap
{
public:
    AsciiStringList &operator[](const AsciiString &key);

private:
    unsigned char m_state[0x0c];
};

class UserPreferences : public PreferenceMap
{
public:
    virtual ~UserPreferences();
    virtual Bool load(AsciiString filename);
    virtual Bool write(void);

protected:
    AsciiString m_filename;
};

class GameSpyLoginPreferences : public UserPreferences
{
public:
    virtual Bool load(AsciiString filename);

private:
    PassMap m_emailPasswordMap;
    NickMap m_emailNickMap;
    DateMap m_emailDateMap;
};

AsciiString QuotedPrintableToAsciiString(AsciiString original);
AsciiString obfuscate(AsciiString input);

// ?load@GameSpyLoginPreferences@@UAE_NVAsciiString@@@Z
Bool GameSpyLoginPreferences::load(AsciiString fname)
{
    if (!UserPreferences::load(fname))
        return false;

    UserPreferences::iterator upIt = begin();
    while (upIt != end())
    {
        AsciiString key = upIt->first;
        if (((const StringBase<char> *)&key)->startsWith("pass_", 5))
        {
            AsciiString email, pass;
            email = key.str() + 5;
            pass = upIt->second;

            AsciiString quoPass = QuotedPrintableToAsciiString(pass);
            pass = obfuscate(quoPass);

            m_emailPasswordMap[email] = pass;
        }
        if (((const StringBase<char> *)&key)->startsWith("date_", 5))
        {
            AsciiString email, date;
            email = key.str() + 5;
            date = upIt->second;

            date = QuotedPrintableToAsciiString(date);

            m_emailDateMap[email] = date;
        }
        else if (((const StringBase<char> *)&key)->startsWith("nick_", 5))
        {
            AsciiString email, nick, nicks;
            email = key.str() + 5;
            nicks = upIt->second;
            while (nicks.nextToken(&nick, ","))
            {
                m_emailNickMap[email].push_back(nick);
            }
        }
        ++upIt;
    }

    return true;
}
