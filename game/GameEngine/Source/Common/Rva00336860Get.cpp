// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00336860Obj
{
	char m_pad[0xB8C];
	int m_value;
};

Rva00336860Obj *g_rva00336860;

int rva00336860Get()
{
	return g_rva00336860->m_value;
}
