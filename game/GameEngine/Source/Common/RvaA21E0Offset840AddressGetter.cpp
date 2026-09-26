struct RvaA21E0Offset840AddressGetter
{
    unsigned char unused[840];
    unsigned char storage;

    unsigned char *get_value();
};

// ?d_000a21e0@@YAXXZ
unsigned char *RvaA21E0Offset840AddressGetter::get_value()
{
    return &storage;
}
