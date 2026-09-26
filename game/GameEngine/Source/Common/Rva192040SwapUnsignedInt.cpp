void rva_192040_swap_unsigned_int(unsigned int *left, unsigned int *right)
{
    unsigned int temporary = *left;
    *left = *right;
    *right = temporary;
}
