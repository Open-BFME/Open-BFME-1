// cl: /O2 /Ob0

class Rva00945720PairSetter
{
	unsigned char m_prefix[0x24];
	unsigned m_first;
	unsigned m_second;
public:
	void set(unsigned first, unsigned second);
};
void Rva00945720PairSetter::set(unsigned first, unsigned second)
{
	m_first = first;
	m_second = second;
}
