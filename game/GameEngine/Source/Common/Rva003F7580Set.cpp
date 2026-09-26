// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003F7580
{
	char m_pad[0xC];
	unsigned m_lead : 6;
	unsigned m_field : 6;

public:
	void set(unsigned value);
};

void Rva003F7580::set(unsigned value)
{
	m_field = value;
}
