// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00410060Inner
{
	char m_pad[4];
	unsigned short m_w;
};

class Rva00410060
{
	char m_pad[4];
	Rva00410060Inner *m_ptr;

public:
	unsigned get() const;
};

unsigned Rva00410060::get() const
{
	if (m_ptr)
		return m_ptr->m_w;
	else
		return 0;
}
