// Retail 0x00367A30 reads an integer at offset 0x04. No caller proves its owner.

struct Rva00367A30FieldGetter
{
    int getField04() const;
};

int Rva00367A30FieldGetter::getField04() const
{
    return *(const int *)((const char *)this + 4);
}
