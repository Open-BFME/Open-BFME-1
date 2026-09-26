// cl: /O2 /Ob0

struct Rva0016C4E0Inner
{
	char m_lead[0x4C];
	int m_value;
};

class Rva0016C4E0
{
	char m_lead[0x60];
	Rva0016C4E0Inner *m_inner;

public:
	bool get();
};

bool Rva0016C4E0::get()
{
	return m_inner->m_value > 0;
}
