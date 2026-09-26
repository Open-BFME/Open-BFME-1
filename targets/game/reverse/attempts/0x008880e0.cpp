// ?nextToken@?$StringBase@D@@QAE_NPAV1@PBD@Z
// partial score=0.26 date=2026-09-07
// Banked real-C++ attempt for StringBase<char>::nextToken,
// RVA 0x008880E0, retail size 186 bytes.
// StringBase layout, separator-helper ABI, and all five retail call routes
// are proven; the remaining mismatch is MSVC's entry register/save choice
// and the resulting out/end/length allocation.
static char *skipSeps(char *, const char *);
static char *skipNonSeps(char *, const char *);

bool StringBase<char>::nextToken(StringBase<char> *out,
                                 const char *delimiters)
{
    if (isEmpty() || out == this)
        return false;

    static const char kDefault[] = " \n\r\t";
    if (delimiters == 0)
        delimiters = kDefault;

    char *start = skipSeps(peek(), delimiters);
    char *end = skipNonSeps(start, delimiters);
    if (end > start)
    {
        int len = (int)(end - start);
        char *tmp = out->getBufferForRead(len);
        memcpy(tmp, start, len);
        tmp[len] = 0;

        int remaining = getLength();
        remaining -= (int)(end - peek());
        set(end, remaining);
        return true;
    }

    clear();
    out->clear();
    return false;
}
