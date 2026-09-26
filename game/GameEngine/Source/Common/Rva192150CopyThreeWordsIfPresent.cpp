void rva_192150_copy_three_words_if_present(unsigned int *destination, unsigned int *source)
{
    if (destination != 0) {
        destination[0] = source[0];
        destination[1] = source[1];
        destination[2] = source[2];
    }
}
