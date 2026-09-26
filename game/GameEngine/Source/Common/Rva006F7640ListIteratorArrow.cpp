struct Rva006F7640ListIteratorArrow
{
    unsigned char *pointer;

    unsigned char *payload() const;
};

unsigned char *Rva006F7640ListIteratorArrow::payload() const
{
    return pointer + 8;
}
