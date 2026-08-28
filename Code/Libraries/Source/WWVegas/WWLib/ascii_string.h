#pragma once

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class UnicodeString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString {
public:
    // Retail inlines the default ctor (the entry ctor at 0x009A1390 zeroes
    // m_text with a single store rather than calling out); ascii_string.cpp
    // still emits the out-of-line COMDAT at 0x00062030 for its 10 callers.
    AsciiString() { m_text = 0; }
    AsciiString(char c);
    // Inline for the same reason as the default ctor, and provably so: retail
    // call sites that copy an AsciiString emit `call StringBase<char>::StringBase`
    // directly rather than a call to this ctor, which only happens if the
    // delegation is visible. It also changes how MSVC schedules the unwind-esp
    // record for by-value AsciiString arguments (retail records esp before
    // loading it into ecx), which is what several callers depend on to match.
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
    }
    // Inline for the same reason, and by the same evidence: retail's
    // INI::loadSubsystemFiles (0x000BB310) builds its AsciiString temp with a
    // direct `call StringBase<char>::StringBase(const char *)`.
    AsciiString(const char *str)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(str);
    }
    AsciiString(const char *str, int len);
    AsciiString(const AsciiString &that, int start, int len);
    AsciiString(const UnicodeString &that);
    ~AsciiString();
    // Same story again: SubsystemInterfaceList::initSubsystem (0x009A20B0)
    // inlines setName and lands a direct `call StringBase<char>::set`.
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
    // BFME's AsciiString exposes StringBase<char>'s methods (they mangle
    // @StringBase@D and are matched in string_base.cpp). Delegate so a caller
    // inlines a `call StringBase<char>::method` to the matched implementation.
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
    // Real body rather than a delegation: retail inlines this comparison at every
    // call site (there is no out-of-line call to 0x0005FEB0 anywhere in the image),
    // and SubsystemLegend::findEntry (0x009A11A0) only matches with the repe cmpsb
    // in line. StringBase<char>::compare keeps its own out-of-line COMDAT.
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
