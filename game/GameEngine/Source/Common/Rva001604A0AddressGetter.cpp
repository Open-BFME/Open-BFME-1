// Retail 0x001604A0 returns this plus 0x0C.
// No caller or identity table proves a semantic owner, so the name keeps the address.

class Rva001604A0AddressField
{
public:
	void *get() const;

private:
	char m_padding[0x0C];
};

void *Rva001604A0AddressField::get() const
{
	return (char *)this + 0x0C;
}
