// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva00367990
{
	unsigned char m_pad[8];
	unsigned m_8;
	unsigned m_C;

public:
	unsigned pick() const;
};

unsigned Rva00367990::pick() const
{
	unsigned cap = m_C;
	if (cap > 0)
	{
		unsigned v = m_8;
		if (v < cap)
			return v;
		return cap;
	}
	return m_8;
}
