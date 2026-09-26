// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003F75A0
{
	char m_pad[0xC];
	unsigned m_lead : 12;
	unsigned m_field : 6;

public:
	void set(unsigned value);
};

void Rva003F75A0::set(unsigned value)
{
	m_field = value;
}
