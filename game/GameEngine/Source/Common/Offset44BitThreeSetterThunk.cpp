struct Offset44BitThreeSetterThunk
{
    unsigned char padding[0x44];
    unsigned int flags;

    void set_bit_three();
};

// ?d_00087460@@YAXXZ
void Offset44BitThreeSetterThunk::set_bit_three()
{
    flags |= 8;
}
