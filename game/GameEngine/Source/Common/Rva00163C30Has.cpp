// cl: /O2 /Ob0

struct Rva00163C30Inner
{
	char pad[0xC8];
	int m_C8;
};

struct Rva00163C30Node
{
	char pad[4];
	Rva00163C30Inner *m_04;
	char pad2[4];
	Rva00163C30Node *m_0C;
	char pad3[9];
	char m_19;
};

class Rva00163C30
{
	char pad[0x14];
	Rva00163C30Node *m_14;

public:
	bool has();
};

bool Rva00163C30::has()
{
	for (Rva00163C30Node *p = m_14; p; p = p->m_0C)
	{
		if (p->m_04->m_C8 & 0x4000)
		{
			if (!p->m_19)
				return true;
		}
	}
	return false;
}
