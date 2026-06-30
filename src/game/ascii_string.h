#pragma once

class AsciiString {
public:
    AsciiString();
    AsciiString(char c);
    AsciiString &operator=(const AsciiString &that);
    AsciiString &operator=(const char *str);
    AsciiString &operator+=(const AsciiString &that);

private:
    char *m_text;
};
