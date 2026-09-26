// Retail at 0x004893C0 stores one into the byte at this+0x55 and returns.
// The owning type and flag semantics were not recovered.
struct Rva004893C0ByteSetter
{
	char m_padding[0x55];
	unsigned char m_flag;

	void set();
};

void Rva004893C0ByteSetter::set()
{
	m_flag = 1;
}
