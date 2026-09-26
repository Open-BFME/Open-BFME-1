void rva_192000_swap_unsigned_short(unsigned short *left, unsigned short *right)
{
    unsigned short temporary = *left;
    *left = *right;
    *right = temporary;
}
