// cl: /DNDEBUG /MD /EHsc
// Retail reports whether the two adjacent state words differ.

class Rva00699090
{
public:
	bool differs();

private:
	unsigned char m_padding[0x8C];
	unsigned int m_left;
	unsigned int m_right;
};

bool Rva00699090::differs()
{
	return m_left != m_right;
}
