class Rva86380PointerPlus16
{
public:
    unsigned char *get_value();

private:
    unsigned char *value;
};

// ?d_00086380@@YAXXZ
unsigned char *Rva86380PointerPlus16::get_value()
{
    return value + 16;
}
