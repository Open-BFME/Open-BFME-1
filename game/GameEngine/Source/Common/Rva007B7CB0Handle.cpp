// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva007B7CB0Target
{
	int m_pad;
	int m_refs;
};

class Rva007B7CB0Handle
{
public:
	Rva007B7CB0Target *addRef();

	char m_pad[0x2c];
	Rva007B7CB0Target *m_target;
};

Rva007B7CB0Target *Rva007B7CB0Handle::addRef()
{
	++m_target->m_refs;
	return m_target;
}
