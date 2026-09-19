// The carved body at 0x0029BCB0 returns the dword at receiver offset 0x30.

class Rva0029BCB0Field30
{
public:
	int get() const;

private:
	int m_pad[ 0xC ];
	int m_field30;
};

int Rva0029BCB0Field30::get() const
{
	return m_field30;
}
