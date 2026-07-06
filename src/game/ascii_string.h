#pragma once

#include "string_base.h"

class UnicodeString;

class AsciiString {
public:
    AsciiString();
    AsciiString(char c);
    AsciiString(const AsciiString &that);
    AsciiString(const char *str);
    AsciiString(const char *str, int len);
    AsciiString(const AsciiString &that, int start, int len);
    AsciiString(const UnicodeString &that);
    ~AsciiString();
    AsciiString &operator=(const AsciiString &that);
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

    friend AsciiString operator+(AsciiString left, const char *right);
    friend AsciiString operator+(AsciiString left, const AsciiString &right);
    friend AsciiString operator+(AsciiString left, char right);

private:
    char *m_text;
};
