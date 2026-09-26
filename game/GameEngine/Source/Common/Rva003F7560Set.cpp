// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003F7560
{
	char m_pad[0xC];
	unsigned m_lead : 22;
	unsigned m_field : 2;

public:
	void set(unsigned value);
};

void Rva003F7560::set(unsigned value)
{
	m_field = value;
}
