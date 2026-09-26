struct Rva18C0F0Offset1F0Getter
{
    unsigned char unused[0x1F0];
    unsigned int value;

    unsigned int get_value();
};

unsigned int Rva18C0F0Offset1F0Getter::get_value()
{
    return value;
}
