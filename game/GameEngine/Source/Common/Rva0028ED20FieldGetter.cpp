// Retail 0x0028ED20 reads an integer at offset 0x4; no owner identity is proven.
struct Rva0028ED20FieldGetter
{
	int getField04() const;
};

int Rva0028ED20FieldGetter::getField04() const
{
	return *(const int *)((const char *)this + 4);
}
