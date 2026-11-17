// Existing BFME1 INI field descriptor; see identity_evidence/20261117-fieldparse-header.md.
#ifndef BFME_COMMON_FIELD_PARSE_H
#define BFME_COMMON_FIELD_PARSE_H

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
    const char *token;
    INIFieldParseProc parse;
    const void *userData;
    int offset;

    inline void set(const char *t, INIFieldParseProc p, const void *u, int o)
    {
        token = t;
        parse = p;
        userData = u;
        offset = o;
    }
};

#endif
