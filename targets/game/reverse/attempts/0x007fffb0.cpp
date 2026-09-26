// ?Rva007FFFB0NullStringSpan@@YAIPBD@Z
// partial score=0.85 date=2026-09-26
// Includes the NUL terminator for a present byte string; null stays empty.
unsigned int Rva007FFFB0NullStringSpan(const char *text)
{
    if (!text)
        return 0;
    const char *afterStart = text + 1;
    while (*text++)
    {
    }
    return (unsigned int)(text - afterStart) + 1;
}
