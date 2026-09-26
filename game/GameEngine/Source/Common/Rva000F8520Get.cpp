// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva000F8520Obj
{
	char m_pad[0xB60];
	int m_value;
};

Rva000F8520Obj *g_rva000F8520;

int rva000F8520Get()
{
	return g_rva000F8520->m_value;
}
