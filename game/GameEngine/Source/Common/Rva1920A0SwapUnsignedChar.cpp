void rva_1920a0_swap_unsigned_char(unsigned char *left, unsigned char *right)
{
    unsigned char temporary = *left;
    *left = *right;
    *right = temporary;
}
