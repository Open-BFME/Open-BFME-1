#pragma once

class AsciiString {
public:
    AsciiString();
    AsciiString(char c);
    AsciiString &operator=(const AsciiString &that);

private:
    char *m_text;
};
