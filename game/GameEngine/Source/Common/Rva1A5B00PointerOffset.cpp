struct Rva1A5B00PointerOffset
{
    int unused;
    void *value;

    void *get() const;
};

void *Rva1A5B00PointerOffset::get() const
{
    return value;
}
