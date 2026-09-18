// Retail RVA 0x001E0D10 returns the address 0x40 bytes after this.
// The carved body does not prove its owning class or member type.

class Rva001E0D10AddressField
{
public:
	char *get() const;
};

char *Rva001E0D10AddressField::get() const
{
	return (char *)this + 0x40;
}
