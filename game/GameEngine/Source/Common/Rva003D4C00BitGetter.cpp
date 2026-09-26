// cl: /O2 /Ob0

class Rva003D4C00BitGetter
{
public:
	int get() const;

	char m_padding[0x0c];
	unsigned int m_flags;
};

int Rva003D4C00BitGetter::get() const
{
	return (m_flags >> 19) & 1;
}
