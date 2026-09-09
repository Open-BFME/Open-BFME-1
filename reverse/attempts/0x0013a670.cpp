// ?bfmeFindXZ@BfmeTblXZ@@QAEHPAPAX@Z
// partial score=0.95 date=2026-09-09
extern "C" int (__cdecl *_bfmeCmpXZ)(void *a, void *b);

class BfmeTblXZ
{
public:
	int bfmeFindXZ(void **key);

	unsigned char m_bfmeHeadXZ[4];
	void **m_bfme04XZ;
	int m_bfme08XZ;
	unsigned char m_bfme0CXZ;
};

int BfmeTblXZ::bfmeFindXZ(void **key)
{
	if (m_bfme0CXZ == 0)
		return 0;

	int i = 0;

	if (m_bfme08XZ > 0)
	{
		int (__cdecl *cmp)(void *, void *) = _bfmeCmpXZ;
		void **k = key;

		do
		{
			if (cmp(m_bfme04XZ[i], *k) == 0)
				return i;

			i++;
		}
		while (i < m_bfme08XZ);
	}

	return -1;
}
