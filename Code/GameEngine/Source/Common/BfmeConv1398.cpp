// Open-BFME5 conversions.

extern "C" void *memcpy(void *d, const void *s, unsigned n);
#pragma intrinsic(memcpy)

class BfmeBufVKD
{
public:
	int bfmeReadVKD(void *dst, int n);
	char m_bfmePad[0x14];
	char *m_bfme14;
	int m_bfme18;
	int m_bfme1c;
};

int BfmeBufVKD::bfmeReadVKD(void *dst, int n)
{
	char *base = m_bfme14;
	if (!base)
		return -1;
	int avail = m_bfme1c - m_bfme18;
	int cnt = n;
	if (cnt > avail)
		cnt = avail;
	if (cnt > 0)
	{
		if (dst)
			memcpy(dst, base + m_bfme18, cnt);
	}
	m_bfme18 += cnt;
	return cnt;
}
