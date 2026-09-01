#pragma once
// The UnicodeString half of the StringBase drift, spelled so it composes with
// reference/shims/campaignmanagerascii.
//
// Retail's UnicodeString is a StringBase<wchar_t> wrapper -- the copy
// constructor at 0x00888400 is ??0?$StringBase@G@@AAE@ABV0@@Z -- not the ZH
// reference class with its own 4-byte header. What that buys is the call-site
// shape: a by-value UnicodeString temporary (TheMouse->setMouseText,
// setCursorTooltip, every GameText fetch passed by value) compiles to retail's
// `mov [esp+N],esp` / `mov ecx,esp` order only when the constructor's body is
// visible and itself makes a call. A declared-only constructor leaves the
// temporary opaque and MSVC emits the two instructions the other way round.
//
// reference/shims/languagefilter solves the same problem but declares its own
// minimal StringBase, so it cannot be combined with the AsciiString shim in one
// TU -- the two definitions of the template collide. This one includes the real
// string_base.h instead, which is the header campaignmanagerascii already pulls
// in, so a file that needs both string classes can take both shims.

#include "string_base.h"

class AsciiString;

class UnicodeString {
public:
    static UnicodeString TheEmptyString;

    UnicodeString() { m_text = 0; }
    UnicodeString(const UnicodeString &that)
    {
        ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(*(const StringBase<wchar_t> *)&that);
    }
    explicit UnicodeString(const wchar_t *str)
    {
        ((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(str);
    }
    ~UnicodeString();

    UnicodeString &operator=(const UnicodeString &that)
    {
        ((StringBase<wchar_t> *)this)->set(*(const StringBase<wchar_t> *)&that);
        return *this;
    }
    UnicodeString &operator=(const wchar_t *str)
    {
        ((StringBase<wchar_t> *)this)->set(str);
        return *this;
    }

    int getLength() const { return ((const StringBase<wchar_t>*)this)->getLength(); }
    bool isEmpty() const { return ((const StringBase<wchar_t>*)this)->isEmpty(); }
    bool isNotEmpty() const { return ((const StringBase<wchar_t>*)this)->isNotEmpty(); }
    void clear() { ((StringBase<wchar_t>*)this)->clear(); }
    wchar_t getCharAt(int index) const { return ((const StringBase<wchar_t>*)this)->getCharAt(index); }
    const wchar_t *str() const { return ((const StringBase<wchar_t>*)this)->str(); }
    wchar_t *getBufferForRead(int len) { return ((StringBase<wchar_t>*)this)->getBufferForRead(len); }

    void set(const UnicodeString &that) { ((StringBase<wchar_t>*)this)->set(*(const StringBase<wchar_t>*)&that); }
    void set(const wchar_t *str) { ((StringBase<wchar_t>*)this)->set(str); }
    void translate(const AsciiString &that);
    void concat(const UnicodeString &that)
    {
        const int length = that.m_text
            ? *reinterpret_cast<const unsigned short *>(
                reinterpret_cast<const char *>( that.m_text ) + 4 ) : 0;
        const wchar_t *text = that.m_text
            ? reinterpret_cast<const wchar_t *>(
                reinterpret_cast<const char *>( that.m_text ) + 8 ) : L"";
        ((StringBase<wchar_t>*)this)->concat( text, length );
    }
    void concat(const wchar_t *str) { ((StringBase<wchar_t>*)this)->concat(str); }
    void concat(const wchar_t c) { ((StringBase<wchar_t>*)this)->concat(c); }
    void trim() { ((StringBase<wchar_t>*)this)->trim(); }
    void removeLastChar() { ((StringBase<wchar_t>*)this)->removeLastChar(); }
    void toLower() { ((StringBase<wchar_t>*)this)->toLower(); }

    void __cdecl format(UnicodeString fmt, ...);
    void __cdecl format(const wchar_t *fmt, ...);
    void format_va(const UnicodeString &fmt, char *args);
    void format_va(const wchar_t *fmt, char *args);

    int compare(const UnicodeString &that) const { return ((const StringBase<wchar_t>*)this)->compare(*(const StringBase<wchar_t>*)&that); }
    int compare(const wchar_t *str) const { return ((const StringBase<wchar_t>*)this)->compare(str); }
    int compareNoCase(const UnicodeString &that) const { return ((const StringBase<wchar_t>*)this)->compareNoCase(*(const StringBase<wchar_t>*)&that); }
    int compareNoCase(const wchar_t *str) const { return ((const StringBase<wchar_t>*)this)->compareNoCase(str); }

    bool nextToken(UnicodeString *token, UnicodeString delimiters = UnicodeString::TheEmptyString)
    {
        return ((StringBase<wchar_t>*)this)->nextToken((StringBase<wchar_t>*)token,
                                                       ((const StringBase<wchar_t>*)&delimiters)->str());
    }

    void debugIgnoreLeaks() { ((StringBase<wchar_t>*)this)->debugIgnoreLeaks(); }
    void validate() const { }

private:
    wchar_t *m_text;
};

inline bool operator==(const UnicodeString &a, const UnicodeString &b) { return *(const StringBase<wchar_t>*)&a == *(const StringBase<wchar_t>*)&b; }
inline bool operator!=(const UnicodeString &a, const UnicodeString &b) { return *(const StringBase<wchar_t>*)&a != *(const StringBase<wchar_t>*)&b; }
inline bool operator<(const UnicodeString &a, const UnicodeString &b) { return *(const StringBase<wchar_t>*)&a < *(const StringBase<wchar_t>*)&b; }
