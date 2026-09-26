// cl: /O2
// Retail 0x0006B070 returns the dword at this + 0x8.

class Rva0006B070Owner
{
public:
	int get();

private:
	char m_padding[8];
	int m_value;
};

int Rva0006B070Owner::get()
{
	return m_value;
}
