// Retail RVA 0x000C9020 returns the address 0x28 bytes after this.
// The carved boundary proves the offset and pointer return, but it does not
// prove the owning class or the member type.

class Rva000C9020AddressField
{
public:
	char *get() const;
};

char *Rva000C9020AddressField::get() const
{
	return (char *)this + 0x28;
}
