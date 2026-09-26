// cl: /O2 /Ob0

class Rva00520460
{
	char pad[4];
	int m_04;
	char pad2[0xC];
	int m_vals[8];

public:
	bool has();
};

bool Rva00520460::has()
{
	if (!m_04)
		return false;
	for (int i = 0; i < 8; i++)
	{
		if (m_vals[i] == 0)
			return false;
	}
	return true;
}
