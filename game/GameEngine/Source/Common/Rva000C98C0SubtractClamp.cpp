// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000C98C0
{
	char m_pad[0x278];
	int m_value;

public:
	void subtract(int amount);
};

void Rva000C98C0::subtract(int amount)
{
	m_value -= amount;
	if (m_value < 0)
		m_value = 0;
}
