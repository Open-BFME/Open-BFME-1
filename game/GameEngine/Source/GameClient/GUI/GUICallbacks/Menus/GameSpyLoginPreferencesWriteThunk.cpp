// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// WOLLoginMenuShutdown names the GameSpyLoginPreferences::write dispatch after
// the constructor has established a 0x38-byte object.  Retail keeps the
// inherited UserPreferences filename as a UTF-16 StringBase at +0x10 and
// opens it with _wfopen; the three derived map layouts are +0x14 password,
// +0x20 nickname, and +0x2c date.  These ABI shims stay local to the body.

#define _STLP_NO_EXCEPTIONS 1

#include <list>
#include <map>

typedef bool Bool;
typedef unsigned short WideChar;

template <class T> class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

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
    void concat(const T *text, int length);

    Header *m_data;
};

class AsciiString
{
public:
    AsciiString(void) : m_data(0) {}
    AsciiString(const char *text);

    AsciiString(const AsciiString &other)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&other);
    }

    ~AsciiString();

    const char *str(void) const
    {
        return m_data ? (const char *)m_data + 8 : "";
    }

    bool isEmpty(void) const
    {
        return !m_data || m_data->length == 0;
    }

    int getLength(void) const
    {
        return m_data ? m_data->length : 0;
    }

    void concat(const AsciiString &other)
    {
        ((StringBase<char> *)this)->concat(other.str(), other.getLength());
    }

    void concat(char character)
    {
        ((StringBase<char> *)this)->concat(&character, 1);
    }

private:
    StringBase<char>::Header *m_data;
};

struct UnicodeStringDataHeader
{
    unsigned char m_unreconstructed_00[4];
    unsigned short m_length;
    unsigned char m_unreconstructed_06[2];
};

class UnicodeString
{
public:
    bool isEmpty(void) const
    {
        return !m_data || m_data->m_length == 0;
    }

    const WideChar *str(void) const
    {
        return m_data ? (const WideChar *)((const unsigned char *)m_data + 8) : L"";
    }

private:
    UnicodeStringDataHeader *m_data;
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
typedef PreferenceMap PassMap;
typedef std::map<AsciiString, AsciiStringList> NickMap;
typedef PreferenceMap DateMap;

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
    virtual Bool write(void);

private:
    PassMap m_emailPasswordMap;
    NickMap m_emailNickMap;
    DateMap m_emailDateMap;
};

AsciiString obfuscate(AsciiString input);
AsciiString AsciiStringToQuotedPrintable(AsciiString input);

// ?write@GameSpyLoginPreferences@@UAE_NXZ
Bool GameSpyLoginPreferences::write(void)
{
    register GameSpyLoginPreferences *self = this;

    if (self->m_filename.isEmpty())
        return false;

    FILE *fp = _wfopen((const WideChar *)self->m_filename.str(), L"w");
    if (fp)
    {
        fprintf(fp, "lastEmail = %s\n", ((*this)["lastEmail"].str()));
        fprintf(fp, "lastName = %s\n", ((*this)["lastName"].str()));
        fprintf(fp, "useProfiles = %s\n", ((*this)["useProfiles"].str()));

        PassMap::iterator passIt = self->m_emailPasswordMap.begin();
        while (passIt != self->m_emailPasswordMap.end())
        {
            AsciiString pass = obfuscate(passIt->second);
            AsciiString quoPass = AsciiStringToQuotedPrintable(pass);
            fprintf(fp, "pass_%s = %s\n", passIt->first.str(), quoPass.str());
            ++passIt;
        }

        DateMap::iterator dateIt = self->m_emailDateMap.begin();
        while (dateIt != self->m_emailDateMap.end())
        {
            AsciiString date = AsciiStringToQuotedPrintable(dateIt->second);
            fprintf(fp, "date_%s = %s\n", dateIt->first.str(), date.str());
            ++dateIt;
        }

        NickMap::iterator nickIt = self->m_emailNickMap.begin();
        while (nickIt != self->m_emailNickMap.end())
        {
            AsciiString nicks;
            AsciiStringList::iterator listIt = nickIt->second.begin();
            while (listIt != nickIt->second.end())
            {
                nicks.concat(*listIt);
                nicks.concat(',');
                ++listIt;
            }
            fprintf(fp, "nick_%s = %s\n", nickIt->first.str(), nicks.str());
            ++nickIt;
        }

        fclose(fp);
        return true;
    }

    return false;
}
