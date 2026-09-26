// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva001EAF50
{
	unsigned char m_pad[0x2E];
	unsigned char m_2E[1];

public:
	void toggle(int index);
};

void Rva001EAF50::toggle(int index)
{
	m_2E[index] = !m_2E[index];
}
