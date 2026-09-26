// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva000E9270Mask
{
public:
	void mask();

private:
	char m_pad[0x14];
	int m_bits;
};

void Rva000E9270Mask::mask()
{
	m_bits &= 0x001FFFFF;
}
