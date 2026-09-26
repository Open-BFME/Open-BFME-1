// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

char *Rva00845640WriteUnsignedDigits(char *end, unsigned int value, unsigned int flags)
{
    while (value != 0) {
        unsigned int digit = value % 10;
        *--end = (char)(digit + '0');
        value /= 10;
    }
    if (flags & 0x800)
        *--end = '+';
    return end;
}
