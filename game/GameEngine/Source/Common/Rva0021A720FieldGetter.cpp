// Retail 0x0021A720 reads an integer at offset 0x04. No caller proves its owner.

struct Rva0021A720FieldGetter
{
    int getField04() const;
};

int Rva0021A720FieldGetter::getField04() const
{
    return *(const int *)((const char *)this + 4);
}
