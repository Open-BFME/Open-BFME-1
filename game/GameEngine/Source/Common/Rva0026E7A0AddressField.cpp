// The carved body at retail RVA 0x0026E7A0 returns the address 0x18 bytes
// after its object. The bytes prove the offset and pointer return, but they do
// not prove the owning class or the member type.

class Rva0026E7A0AddressField
{
public:
	char *get() const;
};

char *Rva0026E7A0AddressField::get() const
{
	return (char *)this + 0x18;
}
