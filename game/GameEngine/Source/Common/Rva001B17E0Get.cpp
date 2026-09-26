// cl: /O2 /Ob0

class Rva001B17E0
{
	char pad[0x14];
	char *m_14;

public:
	void *get(int i);
};

void *Rva001B17E0::get(int i)
{
	return m_14 + i * 0x88;
}
