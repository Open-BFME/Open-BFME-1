struct RvaA2180Offset144Getter
{
    unsigned char unused[144];
    unsigned int value;

    unsigned int get_value();
};

unsigned int RvaA2180Offset144Getter::get_value()
{
    return value;
}
