// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

typedef bool Bool;

template <typename T>
class StringBase
{
    template <typename U>
    friend bool operator==(const StringBase<U> &, const StringBase<U> &);

    friend class AsciiString;
    friend class UnicodeString;

public:
    __forceinline int compare(const StringBase<T> &) const;

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
    void set(const StringBase<T> &source);
    void releaseBuffer();

protected:
    Header *m_data;
};

template <typename T>
__forceinline int StringBase<T>::compare(const StringBase<T> &right) const
{
    const int rightLength = right.m_data ? right.m_data->length : 0;
    const T *rightData = right.m_data ? &right.m_data->data[0] : (const T *)0x0107388B;
    const int leftLength = m_data ? m_data->length : 0;
    const T *leftData = m_data ? &m_data->data[0] : (const T *)0x0107388B;
    const int length = leftLength < rightLength ? leftLength : rightLength;
    int result = memcmp(leftData, rightData, length);
    if (result != 0)
        return result;
    return leftLength - rightLength;
}

template <typename T>
__forceinline bool operator==(const StringBase<T> &left,
                              const StringBase<T> &right)
{
    return left.compare(right) == 0;
}

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const AsciiString &source) : StringBase<char>(source) {}
    ~AsciiString() { releaseBuffer(); }

    const char *str() const
    {
        return m_data ? &m_data->data[0] : (const char *)0x0107388B;
    }

    AsciiString &operator=(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(
            *(const StringBase<char> *)&source);
        return *this;
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

__forceinline Bool operator==(const AsciiString &left, const AsciiString &right)
{
    return *(const StringBase<char> *)&left ==
           *(const StringBase<char> *)&right;
}

class LadderPref
{
public:
    UnicodeString name;
    AsciiString address;
    unsigned short port;
    long lastPlayDate;

    __forceinline bool operator==(const LadderPref &other)
    {
        return address == other.address && port == other.port;
    }
};

typedef std::map<long, LadderPref> LadderPrefMap;

class UserPreferenceMap : public std::map<AsciiString, AsciiString>
{
};

class UserPreferences : public UserPreferenceMap
{
public:
    virtual Bool write(void);

private:
    UnicodeString m_filename;
};

class Rva000AE7C0LadderPreferences : public UserPreferences
{
public:
    void addRecentLadder(LadderPref ladder);

private:
    LadderPrefMap m_ladders;
};

// ?addRecentLadder@LadderPreferences@@QAEXVLadderPref@@@Z
void Rva000AE7C0LadderPreferences::addRecentLadder(LadderPref ladder)
{
    for (LadderPrefMap::iterator it = m_ladders.begin();
         it != m_ladders.end(); ++it)
    {
        if (it->second == ladder)
        {
            m_ladders.erase(it);
            break;
        }
    }

    m_ladders[ladder.lastPlayDate] = ladder;
}
