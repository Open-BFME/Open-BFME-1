// Retail 0x001B1F30 reads an integer at offset 0x4; no owner identity is proven.
struct Rva001B1F30FieldGetter
{
	int getField04() const;
};

int Rva001B1F30FieldGetter::getField04() const
{
	return *(const int *)((const char *)this + 4);
}
