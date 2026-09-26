// cl: /DNDEBUG /MD /EHsc
class Rva008C44F0BitSetter
{
	char m_padding[0x1c];
	unsigned m_unused : 9;
	unsigned m_bit : 1;
public:
	void set(int enabled);
};

// ?set@Rva008C44F0BitSetter@@QAEXH@Z
void Rva008C44F0BitSetter::set(int enabled)
{
	m_bit = enabled != 0;
}

class Rva008C4510MaskTest
{
	char m_padding[0xa];
	short m_bits;
public:
	int test(int bit) const;
};

// ?test@Rva008C4510MaskTest@@QBEHH@Z
int Rva008C4510MaskTest::test(int bit) const
{
	return m_bits & (1 << bit);
}
