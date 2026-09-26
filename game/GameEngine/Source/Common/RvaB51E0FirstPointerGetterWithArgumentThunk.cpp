struct RvaB51E0FirstPointerGetterWithArgumentThunk
{
    void *value;

    void *get(int unused);
};

// ?d_000b51e0@@YAXXZ
void *RvaB51E0FirstPointerGetterWithArgumentThunk::get(int)
{
    return value;
}
