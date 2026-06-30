#pragma once

#include <wchar.h>

class UnicodeString {
public:
    UnicodeString();
    UnicodeString(wchar_t c);
    UnicodeString &operator=(const UnicodeString &that);

private:
    wchar_t *m_text;
};
