// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva0014FEB0
{
	void *m_00;
	unsigned char m_04;
	unsigned m_08;
	unsigned m_0c;

public:
	Rva0014FEB0 *init(void *value);
};

Rva0014FEB0 *Rva0014FEB0::init(void *value)
{
	m_00 = value;
	m_04 = 0;
	m_08 = 0;
	m_0c = 0;
	return this;
}
