// Retail 0x0028D470 returns the first dword of an opaque object.

struct Rva0028D470FirstValue
{
	int get() const;
};

int Rva0028D470FirstValue::get() const
{
	return *(const int *)this;
}
