// cl: /O2 /Ob0

class Rva007F70F0
{
	char pad[0x38];
	char *m_base;
	int m_count;

public:
	void *get(int i);
};

void *Rva007F70F0::get(int i)
{
	if (i >= m_count)
		return 0;
	return m_base + i * 0x1C;
}
