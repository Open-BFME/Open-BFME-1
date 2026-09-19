// The carved body at 0x005BFF90 returns the first dword from its receiver.

class Rva005BFF90Owner
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

unsigned int Rva005BFF90Owner::get() const
{
	return m_value;
}
