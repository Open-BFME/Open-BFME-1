// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

char *Rva008455F0WriteUnsignedDigits64(char *end, unsigned __int64 value, unsigned int flags)
{
    while (value != 0) {
        unsigned int digit = (unsigned int)(value % 10);
        *--end = (char)(digit + '0');
        value /= 10;
    }
    if (flags & 0x800)
        *--end = '+';
    return end;
}
