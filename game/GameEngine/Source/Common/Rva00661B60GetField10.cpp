// Retail 0x00661B60 returns the four-byte field at this plus 0x10.
// Its only incoming edge is the address-qualified ILT thunk at 0x00004A48,
// so this reconstruction deliberately makes no owning-class identity claim.

class Rva00661B60Object
{
public:
	int getField10() const;

private:
	char m_padding00[0x10];
	int m_field10;
};

int Rva00661B60Object::getField10() const
{
	return m_field10;
}
