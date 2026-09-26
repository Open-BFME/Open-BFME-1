// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00412010Inner
{
	bool ready();
};

class Rva00412010
{
	char m_pad[0xFC];
	Rva00412010Inner *m_inner;

public:
	int test() const;
};

int Rva00412010::test() const
{
	Rva00412010Inner *inner = m_inner;
	if (inner && inner->ready())
		return 1;
	return 0;
}
