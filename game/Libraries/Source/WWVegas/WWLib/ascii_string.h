#pragma once

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class UnicodeString;

// BFME's AsciiString is `class AsciiString : public StringBase<char>` and adds
// no data: the retail copy, C-string and default constructors are the
// StringBase<char> ones, and a constructor that runs code after the base is
// built protects the base subobject with an EH state (0x00889090).
// upstream (ZH, a standalone class): inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char> {
public:
    // Exported as ?TheEmptyString@AsciiString@@2V1@B (0x00F36E50).
    static const AsciiString TheEmptyString;

    // Retail inlines the default ctor (the entry ctor at 0x009A1390 zeroes
    // m_data with a single store rather than calling out); ascii_string.cpp
    // still emits the out-of-line COMDAT at 0x00062030 for its 10 callers.
    AsciiString() {}
    AsciiString(char c);
    // Inline, and provably so: retail call sites that copy an AsciiString emit
    // `call StringBase<char>::StringBase` directly rather than a call to this
    // ctor. It also changes how MSVC schedules the unwind-esp record for
    // by-value AsciiString arguments (retail records esp before loading it
    // into ecx), which is what several callers depend on to match.
    AsciiString(const AsciiString &that) : StringBase<char>(that) {}
    // Inline for the same reason, and by the same evidence: retail's
    // INI::loadSubsystemFiles (0x000BB310) builds its AsciiString temp with a
    // direct `call StringBase<char>::StringBase(const char *)`.
    AsciiString(const char *str) : StringBase<char>(str) {}
    AsciiString(const char *str, int len);
    AsciiString(const AsciiString &that, int start, int len);
    AsciiString(const UnicodeString &that);
    // Inline and empty: ??1AsciiString (0x0005EE90) is a bare `jmp 0x00887940`,
    // releaseBuffer through the inline base destructor, and scope exits call
    // 0x00887940 directly. An
    // out-of-line declaration also transposes the EH saved-esp store at
    // by-value call sites (docs/shape_levers.md row 2).
    ~AsciiString() {}
    // Same story again: SubsystemInterfaceList::initSubsystem (0x009A20B0)
    // inlines setName and lands a direct `call StringBase<char>::set`.
    AsciiString &operator=(const AsciiString &that)
    {
        StringBase<char>::set(that);
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
    // StringBase<char>'s methods mangle @StringBase@D and are matched in
    // StringBase.cpp. AsciiString's own overloads hide the base ones, so
    // forward each to the matched implementation.
    const char *str() const { return StringBase<char>::str(); }
    int getLength() const { return StringBase<char>::getLength(); }
    char getCharAt(int i) const { return StringBase<char>::getCharAt(i); }
    bool isEmpty() const { return StringBase<char>::isEmpty(); }
    bool isNotEmpty() const { return StringBase<char>::isNotEmpty(); }
    bool isNone() const { return StringBase<char>::isNone(); }
    bool isNotNone() const { return StringBase<char>::isNotNone(); }
    const char *reverseFind(char c) const { return StringBase<char>::reverseFind(c); }
    bool nextToken(AsciiString *tok, const char *delims=0) { return StringBase<char>::nextToken(tok, delims); }
    void clear() { StringBase<char>::clear(); }
    void set(const char *s) { StringBase<char>::set(s); }
    void set(const AsciiString &s) { StringBase<char>::set(s); }
    void concat(const char *s) { StringBase<char>::concat(s); }
    void concat(char c) { StringBase<char>::concat(c); }
    void concat(const AsciiString &s) { StringBase<char>::concat(s); }
    void toLower() { StringBase<char>::toLower(); }
    void toUpper() { StringBase<char>::toUpper(); }
    void trim() { StringBase<char>::trim(); }
    void removeLastChar() { StringBase<char>::removeLastChar(); }
    const char *find(char c) const { return StringBase<char>::find(c); }
    bool startsWith(const char *p) const { return StringBase<char>::startsWith(p); }
    bool startsWithNoCase(const char *p) const { return StringBase<char>::startsWithNoCase(p); }
    bool endsWith(const char *p) const { return StringBase<char>::endsWith(p); }
    bool endsWithNoCase(const char *p) const { return StringBase<char>::endsWithNoCase(p); }
    int compare(const char *p) const { return StringBase<char>::compare(p); }
    int compareNoCase(const char *p) const { return StringBase<char>::compareNoCase(p); }
    // Real body rather than a delegation: retail inlines this comparison at every
    // AsciiString call site, and SubsystemLegend::findEntry (0x009A11A0) only
    // matches with the repe cmpsb in line. StringBase<char>::compare keeps its own
    // out-of-line COMDAT (0x0005FEB0), which the StringBase operator< calls.
    int compare(const AsciiString &s) const
    {
        int thatLen = s.m_data ? s.m_data->length : 0;
        const char *thatData = s.m_data ? &s.m_data->data[0] : (const char *)"";
        int thisLen = m_data ? m_data->length : 0;
        const char *thisData = m_data ? &m_data->data[0] : (const char *)"";
        int n = thisLen < thatLen ? thisLen : thatLen;
        int c = memcmp(thisData, thatData, n);
        if (c != 0)
            return c;
        return thisLen - thatLen;
    }
    int compareNoCase(const AsciiString &s) const { return StringBase<char>::compareNoCase(s); }

    friend AsciiString operator+(AsciiString left, const char *right);
    friend AsciiString operator+(AsciiString left, const AsciiString &right);
    friend AsciiString operator+(AsciiString left, char right);
};

inline bool operator==(const AsciiString &a, const AsciiString &b) { return (const StringBase<char> &)a == (const StringBase<char> &)b; }
inline bool operator!=(const AsciiString &a, const AsciiString &b) { return (const StringBase<char> &)a != (const StringBase<char> &)b; }
inline bool operator<(const AsciiString &a, const AsciiString &b) { return (const StringBase<char> &)a < (const StringBase<char> &)b; }
