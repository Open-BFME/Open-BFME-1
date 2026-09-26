struct Rva87430Bit4Getter
{
    unsigned char unused[0x44];
    unsigned int flags;

    unsigned int get_value();
};

// ?d_00087430@@YAXXZ
unsigned int Rva87430Bit4Getter::get_value()
{
    return (flags >> 4) & 1;
}
