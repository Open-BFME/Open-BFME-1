// cl: /O2 /Ob0

struct Rva0028ED50Inner
{
	char m_lead[0x0C];
	int m_value;
};

class Rva0028ED50
{
	char m_pad[4];
	Rva0028ED50Inner *m_inner;

public:
	bool get();
};

bool Rva0028ED50::get()
{
	return m_inner->m_value != 0;
}
