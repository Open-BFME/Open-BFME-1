void rva_13dc00_value_fill(unsigned int *output, unsigned int count, const unsigned int *value)
{
    unsigned int *current = output;
    while (count > 0) {
        *current = *value;
        ++current;
        --count;
    }
}
