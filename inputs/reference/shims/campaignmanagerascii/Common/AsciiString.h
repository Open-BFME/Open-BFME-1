#pragma once
// CampaignManager.cpp retail is built against the WWLib StringBase-based
// AsciiString (8-byte header, inline length-compare, out-of-line toLower/dtor
// resolving to StringBase<char>), not the ZH reference 4-byte header. This is
// the Code/Libraries/.../WWLib ascii_string.h content plus the reference
// tree's static AsciiString::TheEmptyString (retail symbol
// ?TheEmptyString@AsciiString@@2V1@A), which the WWLib class does not declare.

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class UnicodeString;

class AsciiString {
public:
    static AsciiString TheEmptyString;
    AsciiString() { m_text = 0; }
    AsciiString(char c);
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
    }
    AsciiString(const char *str)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(str);
    }
    AsciiString(const char *str, int len);
    AsciiString(const AsciiString &that, int start, int len);
    AsciiString(const UnicodeString &that);
    ~AsciiString();
    AsciiString &operator=(const AsciiString &that)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
        return *this;
    }
    AsciiString &operator=(char c);
    AsciiString &operator=(const char *str);
    AsciiString &operator=(const UnicodeString &that);
    AsciiString &operator+=(const AsciiString &that);
    AsciiString &operator+=(char c);
    AsciiString &operator+=(const char *str);
    AsciiString &operator+=(const UnicodeString &that);
    void __cdecl format(AsciiString fmt, ...);
    void translate(const UnicodeString &that);
    const char *str() const { return ((const StringBase<char>*)this)->str(); }
    int getLength() const { return ((const StringBase<char>*)this)->getLength(); }
    char getCharAt(int i) const { return ((const StringBase<char>*)this)->getCharAt(i); }
    bool isEmpty() const { return ((const StringBase<char>*)this)->isEmpty(); }
    bool isNotEmpty() const { return ((const StringBase<char>*)this)->isNotEmpty(); }
    bool isNone() const { return ((const StringBase<char>*)this)->isNone(); }
    bool isNotNone() const { return ((const StringBase<char>*)this)->isNotNone(); }
    const char *reverseFind(char c) const { return ((const StringBase<char>*)this)->reverseFind(c); }
    bool nextToken(AsciiString *tok, const char *delims=0) { return ((StringBase<char>*)this)->nextToken((StringBase<char>*)tok, delims); }
    void clear() { ((StringBase<char>*)this)->clear(); }
    void set(const char *s) { ((StringBase<char>*)this)->set(s); }
    void set(const AsciiString &s) { ((StringBase<char>*)this)->set(*(const StringBase<char>*)&s); }
    void concat(const char *s) { ((StringBase<char>*)this)->concat(s); }
    void concat(char c) { ((StringBase<char>*)this)->concat(c); }
    void concat(const AsciiString &s) { ((StringBase<char>*)this)->concat(*(const StringBase<char>*)&s); }
    void toLower() { ((StringBase<char>*)this)->toLower(); }
    void toUpper() { ((StringBase<char>*)this)->toUpper(); }
    void trim() { ((StringBase<char>*)this)->trim(); }
    void removeLastChar() { ((StringBase<char>*)this)->removeLastChar(); }
    const char *find(char c) const { return ((const StringBase<char>*)this)->find(c); }
    bool startsWith(const char *p) const { return ((const StringBase<char>*)this)->startsWith(p); }
    bool startsWithNoCase(const char *p) const { return ((const StringBase<char>*)this)->startsWithNoCase(p); }
    bool endsWith(const char *p) const { return ((const StringBase<char>*)this)->endsWith(p); }
    bool endsWithNoCase(const char *p) const { return ((const StringBase<char>*)this)->endsWithNoCase(p); }
    int compare(const char *p) const { return ((const StringBase<char>*)this)->compare(p); }
    int compareNoCase(const char *p) const { return ((const StringBase<char>*)this)->compareNoCase(p); }
    int compare(const AsciiString &s) const
    {
        const StringBase<char> *self = (const StringBase<char> *)this;
        const StringBase<char> *that = (const StringBase<char> *)&s;
        int thatLen = that->m_data ? that->m_data->length : 0;
        const char *thatData = that->m_data ? &that->m_data->data[0] : (const char *)"";
        int thisLen = self->m_data ? self->m_data->length : 0;
        const char *thisData = self->m_data ? &self->m_data->data[0] : (const char *)"";
        int n = thisLen < thatLen ? thisLen : thatLen;
        int c = memcmp(thisData, thatData, n);
        if (c != 0)
            return c;
        return thisLen - thatLen;
    }
    int compareNoCase(const AsciiString &s) const { return ((const StringBase<char>*)this)->compareNoCase(*(const StringBase<char>*)&s); }

    friend AsciiString operator+(AsciiString left, const char *right);
    friend AsciiString operator+(AsciiString left, const AsciiString &right);
    friend AsciiString operator+(AsciiString left, char right);

private:
    char *m_text;
};

inline bool operator==(const AsciiString &a, const AsciiString &b) { return *(const StringBase<char>*)&a == *(const StringBase<char>*)&b; }
inline bool operator!=(const AsciiString &a, const AsciiString &b) { return *(const StringBase<char>*)&a != *(const StringBase<char>*)&b; }
inline bool operator<(const AsciiString &a, const AsciiString &b) { return *(const StringBase<char>*)&a < *(const StringBase<char>*)&b; }
