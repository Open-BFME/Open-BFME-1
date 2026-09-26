// cl: /O2 /Ob0

class Slot002997E0
{
public:
	char pad[0x20];
	int m_20;
};

class Rva002997E0
{
	char pad[0x58];
	Slot002997E0 *m_arr[1];

public:
	void set(int i, int v);
};

void Rva002997E0::set(int i, int v)
{
	m_arr[i]->m_20 = v;
}
