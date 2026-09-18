// cl: /DNDEBUG /MD /EHsc
// Real-C++ reconstruction of GameState::realMapPathToPortableMapPath from
// the donor implementation in GameState.cpp.  The local ABI view keeps the
// shared GameState and StringBase headers untouched.

#include <string.h>

static int stringLength(const char *text)
{
    return text ? (int)strlen(text) : 0;
}

class AsciiString;

template <typename T>
class StringBase
{
    friend class AsciiString;

public:
    bool startsWithNoCase(const StringBase<T> &source) const;
    bool startsWithNoCase(const T *text, int length) const;
    void set(const StringBase<T> &source);
    void set(const T *text, int length);
    void concat(const T *text, int length);
    void concat(const StringBase<T> &source);
    void toLower();

    void concat(const T *text)
    {
        concat(text, text ? stringLength(text) : 0);
    }

    void set(const T *text)
    {
        set(text, text ? stringLength(text) : 0);
    }

    bool startsWithNoCase(const T *text) const
    {
        return startsWithNoCase(text, text ? stringLength(text) : 0);
    }

private:
    StringBase(const StringBase<T> &source);
    StringBase(const T *text);

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

class AsciiString
{
public:
    AsciiString() : m_text(0) {}

    AsciiString(const AsciiString &source)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&source);
    }

    AsciiString(const char *text)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(text);
    }

    ~AsciiString();

    AsciiString &operator=(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
        return *this;
    }

    AsciiString &operator=(const char *text);

    const char *str() const
    {
        return m_text ? m_text + 8 : "";
    }

    int getLength() const
    {
        return m_text ? *(const unsigned short *)(m_text + 4) : 0;
    }

    bool startsWithNoCase(const char *text, int length) const
    {
        return ((const StringBase<char> *)this)->startsWithNoCase(text, length);
    }

    bool startsWithNoCase(const char *text) const
    {
        return ((const StringBase<char> *)this)->startsWithNoCase(text);
    }

    __forceinline bool startsWithNoCase(const AsciiString &source) const
    {
        int length = source.m_text
            ? *(const unsigned short *)(source.m_text + 4) : 0;
        const char *text = source.m_text ? source.m_text + 8 : "";
        return ((const StringBase<char> *)this)->startsWithNoCase(text, length);
    }

    void concat(const char *text)
    {
        ((StringBase<char> *)this)->concat(text);
    }

    void concat(const AsciiString &source)
    {
        const int length = source.m_text
            ? *(const unsigned short *)(source.m_text + 4) : 0;
        const char *text = source.m_text ? source.m_text + 8 : "";
        ((StringBase<char> *)this)->concat(text, length);
    }

    void toLower()
    {
        ((StringBase<char> *)this)->toLower();
    }

private:
    char *m_text;
};

class MapCache
{
public:
    AsciiString getMapDir() const;
    AsciiString getUserMapDir() const;
};

extern MapCache *TheMapCache;

class GameState
{
public:
    AsciiString getSaveDirectory() const;
    AsciiString getMapLeafName(const AsciiString &path) const;
    AsciiString realMapPathToPortableMapPath(const AsciiString &in) const;
};

const char *PORTABLE_SAVE = "Save\\";
const char *PORTABLE_MAPS = "Maps\\";
const char *PORTABLE_USER_MAPS = "UserData\\Maps\\";

static const char *findLastBackslashInRangeInclusive(const char *start,
                                                       const char *end)
{
    while (end >= start)
    {
        if (*end == '\\')
            return end;
        --end;
    }
    return 0;
}

__declspec(noinline) static AsciiString getMapLeafAndDirName(const AsciiString &in)
{
    const char *start = in.str();
    const char *end = in.str() + in.getLength() - 1;
    const char *leafSeparator = findLastBackslashInRangeInclusive(start, end);
    if (leafSeparator)
    {
        const char *directorySeparator =
            findLastBackslashInRangeInclusive(start, leafSeparator - 1);
        if (directorySeparator)
            return directorySeparator + 1;
        return in;
    }
    return in;
}

AsciiString GameState::realMapPathToPortableMapPath(const AsciiString &in) const
{
    const StringBase<char> *input = (const StringBase<char> *)&in;
    const int zero = 0;
    if (((const AsciiString *)input)->getLength() == zero)
        return *(const AsciiString *)input;
    AsciiString prefix;
    if (((const AsciiString *)input)->startsWithNoCase(getSaveDirectory()))
    {
        ((StringBase<char> *)&prefix)->set(PORTABLE_SAVE);
        prefix.concat(getMapLeafName(*(const AsciiString *)input));
    }
    else if (((const AsciiString *)input)->startsWithNoCase(TheMapCache->getMapDir()))
    {
        prefix = PORTABLE_MAPS;
        ((StringBase<char> *)&prefix)->concat(
            *(const StringBase<char> *)&getMapLeafAndDirName(*(const AsciiString *)input));
    }
    else if (input->startsWithNoCase(
        *(const StringBase<char> *)&TheMapCache->getUserMapDir()))
    {
        prefix = PORTABLE_USER_MAPS;
        ((StringBase<char> *)&prefix)->concat(
            *(const StringBase<char> *)&getMapLeafAndDirName(*(const AsciiString *)input));
    }
    else
    {
        prefix = *(const AsciiString *)input;
    }
    prefix.toLower();
    return prefix;
}
