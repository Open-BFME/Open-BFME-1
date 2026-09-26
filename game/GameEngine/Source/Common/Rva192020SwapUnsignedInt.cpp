void rva_192020_swap_unsigned_int(unsigned int *left, unsigned int *right)
{
    unsigned int temporary = *left;
    *left = *right;
    *right = temporary;
}
