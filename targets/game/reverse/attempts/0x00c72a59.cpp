// ?Rva00C72A59@@YAIPBD@Z
// partial score=0.2916666667 date=2026-09-23
// cl: /O1
// Address identity only. Retail RVA 0x00C72A59, 24 bytes.
// Counts bytes up to the first NUL. No semantic/original-symbol claim.
// Boundary: preceding INT3 run; RET at 0x00C72A70; zero fill from 0x00C72A71.
unsigned int Rva00C72A59(const char *text)
{
    const char *end = text;
    char current = *end++;
    while (current) {
        current = *end++;
    }
    return (unsigned int)(end - text - 1);
}
