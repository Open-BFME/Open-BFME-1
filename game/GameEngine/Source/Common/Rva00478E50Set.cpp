// cl: /O2 /Ob0

class Rva00478E50
{
	char m_lead[0x1E4];
	void *m_ptr;

public:
	int apply(void *p);
};

int Rva00478E50::apply(void *p)
{
	if (p)
		m_ptr = p;
	return 0;
}
