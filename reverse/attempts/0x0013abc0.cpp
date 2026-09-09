// ?bfmeEqualsXZ@BfmeTblXZ@@QAEDPAV1@@Z
// partial score=0.90 date=2026-09-09
extern "C" int (__cdecl *_bfmeCmpXZ)(void *a, void *b);

class BfmeTblXZ
{
public:
	char bfmeEqualsXZ(BfmeTblXZ *o);

	unsigned char m_bfmeHeadXZ[4];
	void **m_bfme04XZ;
	int m_bfme08XZ;
};

char BfmeTblXZ::bfmeEqualsXZ(BfmeTblXZ *o)
{
	int n = m_bfme08XZ;

	if (n == o->m_bfme08XZ)
	{
		int i = 0;

		if (n > 0)
		{
			int (__cdecl *cmp)(void *, void *) = _bfmeCmpXZ;

			do
			{
				if (cmp(m_bfme04XZ[i], o->m_bfme04XZ[i]) != 0)
					return 0;

				i++;
			}
			while (i < m_bfme08XZ);
		}

		return 1;
	}

	return 0;
}
