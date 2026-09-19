// The carved body at 0x000A31C0 returns the first dword from its receiver.

class Rva000A31C0Owner
{
public:
	unsigned int get() const;

	unsigned int m_value;
};

unsigned int Rva000A31C0Owner::get() const
{
	return m_value;
}
