// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000C9D40Pointee
{
public:
	char m_leading[0xBD];
	unsigned char m_field;
};

class Rva000C9D40
{
	void *m_0;
	Rva000C9D40Pointee *m_pointee;

public:
	int get();
};

int Rva000C9D40::get()
{
	if (m_pointee)
	{
		return m_pointee->m_field;
	}
	return 0;
}
