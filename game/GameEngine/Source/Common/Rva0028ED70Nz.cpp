// cl: /O2 /Ob0

struct Rva0028ED70Inner
{
	char m_lead[0x4C];
	int m_value;
};

class Rva0028ED70
{
	char m_lead[4];
	Rva0028ED70Inner *m_inner;

public:
	bool get();
};

bool Rva0028ED70::get()
{
	return m_inner->m_value != -1;
}
