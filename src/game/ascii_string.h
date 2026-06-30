#pragma once

class AsciiString {
public:
    AsciiString();
    AsciiString(char c);
    AsciiString(const char *str, int len);
    AsciiString &operator=(const AsciiString &that);
    AsciiString &operator=(const char *str);
    AsciiString &operator+=(const AsciiString &that);

private:
    char *m_text;
};
