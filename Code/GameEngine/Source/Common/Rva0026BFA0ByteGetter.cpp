// Retail RVA 0x0026BFA0 is a four-byte const thiscall getter.
// The carved boundary proves a byte read at this+0x2D, but no caller or
// identity table proves the owning class or field name.

class Rva0026BFA0ByteGetter
{
public:
	unsigned char getByte(void) const;

private:
	unsigned char m_padding[0x2D];
	unsigned char m_value;
};

unsigned char Rva0026BFA0ByteGetter::getByte(void) const
{
	return m_value;
}
