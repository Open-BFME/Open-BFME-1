// ?load30@Rva000C3D70@@QAEHXZ
// Retail 0x000C3D70 loads the dword at this+0x30 and returns it.
// The adjacent boundaries do not prove a semantic class or method name.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva000C3D70
{
public:
	int load30();

private:
	char m_padding[0x30];
	int m_value30;
};

int Rva000C3D70::load30()
{
	return m_value30;
}
