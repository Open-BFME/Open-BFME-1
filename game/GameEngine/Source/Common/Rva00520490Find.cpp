// cl: /O2 /Ob0

class Rva00520490
{
	char pad[0x14];
	int m_vals[8];

public:
	int find(int v);
};

int Rva00520490::find(int v)
{
	for (int i = 0; i < 8; i++)
	{
		if (v == m_vals[i])
			return i;
	}
	return -1;
}
