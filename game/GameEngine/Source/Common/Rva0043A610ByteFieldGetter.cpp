// cl: /O2 /Ob0
//
// The carved body at 0x0043A610 returns the byte at this+0x10. The available
// evidence proves the offset and width but does not prove a semantic owner.

typedef unsigned char UnsignedByte;

class Rva0043A610ByteField
{
	unsigned char m_unmodelled_000[0x10];
	UnsignedByte m_unmodelled_010;

public:
	UnsignedByte get() const;
};

UnsignedByte Rva0043A610ByteField::get() const
{
	return m_unmodelled_010;
}
