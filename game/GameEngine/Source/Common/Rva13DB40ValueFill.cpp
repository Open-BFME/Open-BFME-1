void rva_13db40_value_fill(unsigned int *output, unsigned int count, const unsigned int *value)
{
    unsigned int *current = output;
    while (count > 0) {
        *current = *value;
        ++current;
        --count;
    }
}
