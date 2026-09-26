// The carved body at 0x000AFB10 returns the first dword from its receiver.

class Rva000AFB10Owner
{
public:
	unsigned int get() const;

	unsigned int m_value;
};

unsigned int Rva000AFB10Owner::get() const
{
	return m_value;
}
