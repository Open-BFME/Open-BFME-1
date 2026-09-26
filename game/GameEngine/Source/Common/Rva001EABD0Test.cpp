// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva001EABD0Inner
{
public:
	unsigned char m_pad[0x4F0];
	void *m_4F0;
};

class Rva001EABD0
{
	unsigned char m_pad[4];
	Rva001EABD0Inner *m_4;

public:
	bool test() const;
};

bool Rva001EABD0::test() const
{
	Rva001EABD0Inner *h = m_4;
	return h->m_4F0 == 0;
}
