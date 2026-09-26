// cl: /O2 /Ob0

struct Rva000EF320Inner
{
	char m_lead[0x14];
	int m_value;
};

class Rva000EF320
{
	char m_lead[0xF0];
	Rva000EF320Inner *m_inner;

public:
	bool get();
};

bool Rva000EF320::get()
{
	return m_inner->m_value != 0;
}
