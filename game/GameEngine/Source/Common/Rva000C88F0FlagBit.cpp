// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived flag-bit reader at 0x000C88F0.

struct Rva000C88F0Object
{
	unsigned char m_prefix[0x344];
	unsigned char m_flags;

	unsigned int flagBitThree() const;
};

unsigned int Rva000C88F0Object::flagBitThree() const
{
	return (m_flags >> 3) & 1;
}
