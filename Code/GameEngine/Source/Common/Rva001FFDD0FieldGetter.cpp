// Retail 0x001FFDD0 reads an integer at offset 0x04.
// Nearby GiantBirdSlowDeathBehavior methods do not prove this body's owner or field type.

struct Rva001FFDD0FieldGetter
{
	int getField04() const;
};

int Rva001FFDD0FieldGetter::getField04() const
{
	return *(const int *)((const char *)this + 4);
}
