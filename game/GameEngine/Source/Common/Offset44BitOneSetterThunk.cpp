struct Offset44BitOneSetterThunk
{
    unsigned char padding[0x44];
    unsigned int flags;

    void set_bit_one();
};

// ?d_00087440@@YAXXZ
void Offset44BitOneSetterThunk::set_bit_one()
{
    flags |= 2;
}
