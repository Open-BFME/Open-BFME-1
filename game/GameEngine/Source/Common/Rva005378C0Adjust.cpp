// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva005378C0
{
	unsigned char m_pad[4];
	int *m_4;

public:
	void adjust(int amount);
};

void Rva005378C0::adjust(int amount)
{
	int *value = m_4;
	value[0] += amount;
	value[1] -= amount;
}
