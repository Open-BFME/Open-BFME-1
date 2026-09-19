// Retail 0x00086440 reads an integer at offset 0x04. No caller proves its owner.

struct Rva00086440FieldGetter
{
	int getField04() const;
};

int Rva00086440FieldGetter::getField04() const
{
	return *(const int *)((const char *)this + 4);
}
