// cl: /DNDEBUG /MD /EHsc
class Rva008AB7E0BitSetter
{
	char m_padding[0x60];
	unsigned m_bits;
public:
	void set(int enabled);
};

// ?set@Rva008AB7E0BitSetter@@QAEXH@Z
void Rva008AB7E0BitSetter::set(int enabled)
{
	unsigned bit = enabled != 0;
	bit <<= 16;
	m_bits = m_bits ^ ((m_bits ^ bit) & 0x10000);
}
