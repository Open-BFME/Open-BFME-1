// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Gen000107D5
{
public:
	void handle(int a);
};

class Rva000C9770
{
	char m_pad[0x220];
	Gen000107D5 *m_inner;

public:
	void wrap(int a);
};

void Rva000C9770::wrap(int a)
{
	if (m_inner)
		m_inner->handle(a);
}
