// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva001A3020Flag
{
public:
	void ensure();

private:
	char m_pad[0x18];
	char m_flag;
};

void Rva001A3020Flag::ensure()
{
	if (!m_flag)
		m_flag = 1;
}
