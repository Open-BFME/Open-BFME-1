// ?nextToken@?$StringBase@G@@QAE_NPAV1@PBG@Z
// partial score=0.59 date=2026-09-07
// Banked real-C++ attempt for StringBase<wchar_t>::nextToken,
// RVA 0x008889B0, retail size 197 bytes.
// The header layout and all five retail call routes are proven; the remaining
// mismatch is MSVC's callee-saved register allocation in the prologue and
// dependent arithmetic/call setup.
static unsigned short *skipSepsW(unsigned short *, const unsigned short *);
static unsigned short *skipNonSepsW(unsigned short *, const unsigned short *);

bool StringBase<wchar_t>::nextToken(StringBase<wchar_t> *out,
                                    const wchar_t *delimiters)
{
    if (isEmpty() || out == this)
        return false;

    static const wchar_t kDefault[] = L" \n\r\t";
    if (delimiters == 0)
        delimiters = kDefault;

    wchar_t *start = skipSepsW(peek(), delimiters);
    wchar_t *end = skipNonSepsW(start, delimiters);
    if (end > start)
    {
        int len = (int)(end - start);
        wchar_t *tmp = out->getBufferForRead(len);
        memcpy(tmp, start, len * 2);
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
