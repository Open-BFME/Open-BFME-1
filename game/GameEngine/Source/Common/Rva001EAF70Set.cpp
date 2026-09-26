// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva001EAF70
{
	unsigned char m_pad[0x2E];
	unsigned char m_2E[1];

public:
	void set(int index, unsigned char value);
};

void Rva001EAF70::set(int index, unsigned char value)
{
	m_2E[index] = value;
}
