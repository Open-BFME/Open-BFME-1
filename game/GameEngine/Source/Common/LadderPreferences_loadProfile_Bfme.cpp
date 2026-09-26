// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include <stdlib.h>
#include <string.h>

typedef int Int;
typedef bool Bool;

template <typename T>
class StringBase
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

    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &source);
    StringBase(const T *source);
    void set(const StringBase<T> &source);
    void releaseBuffer();

protected:
    Header *m_data;

public:
    __forceinline const T *reverseFind(T c) const
    {
        const T *start = m_data ? &m_data->data[0] : (const T *)0x0107388B;
        const T *p = start + (m_data ? m_data->length : 0);
        while (p != start)
        {
            --p;
            if (*p == c)
                return p;
        }
        return 0;
    }

    void removeLastChar();
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &source) : StringBase<char>(source) {}
    AsciiString(const char *source) : StringBase<char>(source) {}
    ~AsciiString() { releaseBuffer(); }

    const char *str() const
    {
        return m_data ? &m_data->data[0] : (const char *)0x0107388B;
    }

    void __cdecl format(AsciiString format, ...);
    AsciiString &operator=(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(
            *(const StringBase<char> *)&source);
        return *this;
    }

    __forceinline const char *reverseFind(char c) const
    {
        const char *first = str();
        const char *p = first + (m_data ? m_data->length : 0);
        while (p != first)
        {
            --p;
            if (*p == c)
                return p;
        }
        return 0;
    }

    void removeLastChar()
    {
        ((StringBase<char> *)this)->removeLastChar();
    }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const UnicodeString &source)
        : StringBase<unsigned short>(source)
    {
    }
    ~UnicodeString() { releaseBuffer(); }

    UnicodeString &operator=(const UnicodeString &source)
    {
        ((StringBase<unsigned short> *)this)->set(
            *(const StringBase<unsigned short> *)&source);
        return *this;
    }
};

class LadderPref
{
public:
    UnicodeString name;
    AsciiString address;
    unsigned short port;
    long lastPlayDate;
};

typedef std::map<long, LadderPref> LadderPrefMap;

enum NameKeyType
{
    NAMEKEY_INVALID = 0
};

typedef std::map<NameKeyType, float> UserPreferenceClearMap;

class UserPreferenceMap : public std::map<AsciiString, AsciiString>
{
public:
    void clear(void)
    {
        ((UserPreferenceClearMap *)this)->clear();
    }
};

class UserPreferences : public UserPreferenceMap
{
public:
    virtual ~UserPreferences() {}
    virtual void unused00();
    virtual Bool load(AsciiString fname);
    virtual Bool write(void);

private:
    UnicodeString m_filename;
};

class LadderPreferences : public UserPreferences
{
public:
    Bool loadProfile(Int profileID);

private:
    LadderPrefMap m_ladders;
};

extern AsciiString QuotedPrintableToAsciiString(AsciiString original);
extern UnicodeString QuotedPrintableToUnicodeString(AsciiString original);

// ?loadProfile@LadderPreferences@@QAE_NH@Z
Bool LadderPreferences::loadProfile(Int profileID)
{
    clear();
    m_ladders.clear();
    AsciiString userPrefFilename;
    userPrefFilename.format("LoTRB4MEOnline\\Ladders%d.ini", profileID);
    Bool success = load(userPrefFilename);
    if (!success)
        return success;

    for (LadderPreferences::iterator it = begin(); it != end(); ++it)
    {
        LadderPref p;
        AsciiString ladName = it->first;
        AsciiString ladData = it->second;

        const char *ptr = ladName.reverseFind(':');
        if (!ptr)
            continue;

        p.port = atoi(ptr + 1);
        for (Int i = 0; i < strlen(ptr); ++i)
            ladName.removeLastChar();
        p.address = QuotedPrintableToAsciiString(ladName);

        ptr = ladData.reverseFind(':');
        if (!ptr)
            continue;

        p.lastPlayDate = atoi(ptr + 1);
        for (i = 0; i < strlen(ptr); ++i)
            ladData.removeLastChar();
        p.name = QuotedPrintableToUnicodeString(ladData);

        m_ladders[p.lastPlayDate] = p;
    }

    return true;
}
