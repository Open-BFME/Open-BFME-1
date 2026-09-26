// cl: /O2 /Ob0

struct Rva0028EE70Obj
{
	char pad[0x74];
	int m_74;
};

class Rva0028EE70
{
	char pad[0x24];
	char m_24[1];
	char pad2[0xB];
	int m_30[1];
	char pad3[0x24];
	int m_58[1];

public:
	void set(int i, Rva0028EE70Obj *p);
};

void Rva0028EE70::set(int i, Rva0028EE70Obj *p)
{
	int v;
	m_24[i] = 1;
	m_30[i] = 0;
	if (p)
		v = p->m_74;
	else
		v = 0;
	m_58[i] = v;
}
