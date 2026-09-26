// Retail at 0x001F83B0 clears the byte at this+0x48 and returns.
// The owning type and field semantics were not recovered.
struct Rva001F83B0Holder
{
	char m_padding[0x48];
	unsigned char m_flag;

	void clearFlag();
};

void Rva001F83B0Holder::clearFlag()
{
	m_flag = 0;
}
