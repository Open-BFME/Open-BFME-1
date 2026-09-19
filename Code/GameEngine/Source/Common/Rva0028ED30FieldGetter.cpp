// Retail 0x0028ED30 reads an integer at offset 0x0c.
// No caller or type table proves a semantic owner, so the address stays in the names.

struct Rva0028ED30FieldGetter
{
	int getField0C() const;
};

int Rva0028ED30FieldGetter::getField0C() const
{
	return *(const int *)((const char *)this + 0x0c);
}
