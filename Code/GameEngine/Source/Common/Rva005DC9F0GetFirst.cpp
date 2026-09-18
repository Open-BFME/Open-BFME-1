// Retail RVA 0x005DC9F0 returns the receiver's first dword.
// The carved body has no named caller, so the address-derived owner keeps its identity open.

class Rva005DC9F0
{
public:
	unsigned int getFirst();

private:
	unsigned int m_first;
};

unsigned int Rva005DC9F0::getFirst()
{
	return m_first;
}
