#ifndef MELEEPROBE_CHAT_JSON_H
#define MELEEPROBE_CHAT_JSON_H

enum { PROBE_CHAT_CODE_UNITS = 512 };
struct ProbeChatText {
    char text[PROBE_CHAT_CODE_UNITS * 6 + 1];
    unsigned codeUnits, truncated;
};

static void escape_chat_text(const unsigned short *text, ProbeChatText &out) {
    static const char hex[] = "0123456789abcdef";
    unsigned n = 0, used = 0;
    for (; text && n < PROBE_CHAT_CODE_UNITS && text[n]; ++n) {
        unsigned ch = text[n];
        if (ch == '"' || ch == '\\') {
            out.text[used++] = '\\';
            out.text[used++] = (char)ch;
        } else if (ch >= 32 && ch < 127) {
            out.text[used++] = (char)ch;
        } else {
            out.text[used++] = '\\';
            out.text[used++] = 'u';
            out.text[used++] = hex[(ch >> 12) & 15];
            out.text[used++] = hex[(ch >> 8) & 15];
            out.text[used++] = hex[(ch >> 4) & 15];
            out.text[used++] = hex[ch & 15];
        }
    }
    out.text[used] = 0;
    out.codeUnits = n;
    out.truncated = (unsigned)(text && text[n] != 0);
}

#endif
