// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva0022D180Inner
{
	char m_pad[0x1F8];
	char m_value;
};

class Rva0022D180Obj
{
public:
	char get(int unused);

	int m_pad;
	Rva0022D180Inner *m_inner;
};

char Rva0022D180Obj::get(int unused)
{
	return m_inner->m_value;
}
