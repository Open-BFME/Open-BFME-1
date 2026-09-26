extern "C" void Rva14A980CopyIfNotNull(int *destination, const int *source)
{
    if (destination != 0) {
        *destination = *source;
    }
}
