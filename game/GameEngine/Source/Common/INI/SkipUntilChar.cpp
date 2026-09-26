// cl: /DNDEBUG /MD /EHsc
static const char *bfmeSkipUntil0035E800(const char *p, char delimiter)
{
    char c = *p;
    while (c && c != delimiter)
        c = *++p;
    return p;
}

const char *bfmeKeepSkipUntil0035E800(const char *p, char delimiter)
{
    return bfmeSkipUntil0035E800(p, delimiter);
}
