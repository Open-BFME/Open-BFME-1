// Retail RVA 0x005DCA10 returns the first dword after clearing it.
// The adjacent carved getter and the body boundary prove the operation, but no owner identity.

class Rva005DCA10
{
public:
	unsigned int getAndClear();

private:
	unsigned int m_value;
};

unsigned int Rva005DCA10::getAndClear()
{
	unsigned int old = m_value;
	m_value = 0;
	return old;
}
