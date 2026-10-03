// Native AsciiString methods live apart from the unrelated Unicode naked lifts.
#include "unicode_string.h"
#include "ascii_string.h"
#include "string_base.h"

extern "C" unsigned int __cdecl strlen(const char *str);

// Keep out-of-line copy and C-string ctor COMDATs for retail callers.
#pragma auto_inline(off)
AsciiString bfme_force_ascii_string_copy_ctor_emission(const AsciiString &that)
{
    return AsciiString(that);
}

AsciiString bfme_force_ascii_string_cstr_ctor_emission(const char *str)
{
    return AsciiString(str);
}

void bfme_force_ascii_string_assign_emission(AsciiString &dst, const AsciiString &src)
{
    dst = src;
}
#pragma auto_inline(on)

AsciiString::AsciiString(char c) : StringBase<char>(c) {}

AsciiString::AsciiString(const AsciiString &that, int start, int len) : StringBase<char>(that, start, len) {}

inline AsciiString::AsciiString(const char *str, int len) : StringBase<char>(str, len) {}

// ??1AsciiString (0x0005EE90) is the implicit destructor; the unwind actions
// of the by-value operators below emit its COMDAT.

AsciiString &AsciiString::operator=(char c)
{
    char ch = c;
    ((StringBase<char> *)this)->set(&ch, 1);
    return *this;
}

AsciiString &AsciiString::operator=(const char *str)
{
    ((StringBase<char> *)this)->set(str, str ? strlen(str) : 0);
    return *this;
}

AsciiString &AsciiString::operator+=(const AsciiString &that)
{
    const StringBase<char> *s = (const StringBase<char> *)&that;
    ((StringBase<char> *)this)->concat(s->m_data ? &s->m_data->data[0] : (const char *)"",
                                       s->m_data ? s->m_data->length : 0);
    return *this;
}

AsciiString &AsciiString::operator+=(char c)
{
    char ch = c;
    ((StringBase<char> *)this)->concat(&ch, 1);
    return *this;
}

AsciiString &AsciiString::operator+=(const char *str)
{
    ((StringBase<char> *)this)->concat(str, str ? strlen(str) : 0);
    return *this;
}

AsciiString operator+(AsciiString left, const char *right)
{
    left += right;
    return left;
}

AsciiString operator+(AsciiString left, const AsciiString &right)
{
    left += right;
    return left;
}

AsciiString operator+(AsciiString left, char right)
{
    left += right;
    return left;
}

AsciiString &AsciiString::operator=(const UnicodeString &that)
{
    const StringBase<wchar_t> *w = (const StringBase<wchar_t> *)&that;
    format(AsciiString("%ls"), w->m_data ? &w->m_data->data[0] : (const wchar_t *)L"");
    return *this;
}

void __cdecl AsciiString::format(AsciiString fmt, ...)
{
    const StringBase<char> *f = (const StringBase<char> *)&fmt;
    ((StringBase<char> *)this)->format_va(f->m_data ? &f->m_data->data[0] : (const char *)"",
                                          (char *)(&fmt + 1));
}

void AsciiString::translate(const UnicodeString &that)
{
    const StringBase<wchar_t> *w = (const StringBase<wchar_t> *)&that;
    format(AsciiString("%ls"), w->m_data ? &w->m_data->data[0] : (const wchar_t *)L"");
}
