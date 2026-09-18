class Rva0011A170PointerOffset
{
public:
	void *get() const;
};

void *Rva0011A170PointerOffset::get() const
{
	return reinterpret_cast<char *>(const_cast<Rva0011A170PointerOffset *>(this)) - 0x10;
}
