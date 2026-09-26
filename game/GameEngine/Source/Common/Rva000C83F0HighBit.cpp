// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived high-bit reader at 0x000C83F0.

struct Rva000C83F0Record
{
	unsigned char m_prefix[0xc8];
	unsigned char m_flags;
};

unsigned int rva000C83F0HighBit(const Rva000C83F0Record *record)
{
	return record->m_flags >> 7;
}
