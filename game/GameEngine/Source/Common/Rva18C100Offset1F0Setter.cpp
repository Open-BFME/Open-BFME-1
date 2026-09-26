struct Rva18C100Offset1F0Setter
{
    unsigned char unused[0x1F0];
    unsigned int value;

    unsigned int set_value(unsigned int new_value);
};

unsigned int Rva18C100Offset1F0Setter::set_value(unsigned int new_value)
{
    value = new_value;
    return new_value;
}
