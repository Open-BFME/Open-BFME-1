// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003679B0
{
	unsigned char m_pad[0x30];
	unsigned m_30[1];

public:
	void set(int index, unsigned value);
};

void Rva003679B0::set(int index, unsigned value)
{
	m_30[index] = value;
}
