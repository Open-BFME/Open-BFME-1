// Retail 0x006C0880 returns the float at offset 0x14.

struct Rva006C0880FloatGetter
{
	float get() const;
};

float Rva006C0880FloatGetter::get() const
{
	return *(const float *)((const char *)this + 0x14);
}
