// cl: /O2 /Ob0

class Rva0069EBD0
{
	int *m_00;
	int *m_04;
	int *m_08;

public:
	unsigned rem(int **p);
};

unsigned Rva0069EBD0::rem(int **p)
{
	int *q = *p;
	if (q)
		q = (int *)q[2];
	unsigned n = (unsigned)(m_08 - m_04);
	return (unsigned)q % n;
}
