// cl: /O2 /Ob0

struct Rva000EE7D0Inner
{
	char m_lead[0x14];
	int m_value;
};

class Rva000EE7D0
{
	char m_lead[0xEC];
	Rva000EE7D0Inner *m_inner;

public:
	bool get();
};

bool Rva000EE7D0::get()
{
	return m_inner->m_value != 0;
}
