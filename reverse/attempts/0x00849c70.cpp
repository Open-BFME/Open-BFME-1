// ?ungetc00849C70@Rva00849C70Owner@@QAEHH@Z
// partial score=0.9 date=2026-09-03
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD

#include <stdio.h>

struct Rva00849C70StreamBuf
{
	unsigned char *m_ptr;	// +0
	int m_cnt;				// +4
	unsigned char *m_base;	// +8
};

class Rva00849C70Owner
{
public:
	int ungetc00849C70(int ch);

private:
	char m_pad0[4];
	Rva00849C70StreamBuf *m_buf;	// +4
	char m_pad8[0x54 - 8];
	FILE *m_file;					// +0x54
};

// ?ungetc00849C70@Rva00849C70Owner@@QAEHH@Z
int Rva00849C70Owner::ungetc00849C70(int ch)
{
	if (ch != -1)
	{
		int r = ungetc(ch, m_file);
		if (r == -1)
			r = -1;
		return r;
	}
	Rva00849C70StreamBuf *buf = m_buf;
	unsigned char *base = buf->m_base;
	if (base >= *(unsigned char **)buf)
		return -1;
	Rva00849C70StreamBuf *b = buf;
	unsigned char *ptr = *(unsigned char **)b;
	int cnt = b->m_cnt;
	--ptr;
	++cnt;
	b->m_cnt = cnt;
	*(unsigned char **)b = ptr;
	return 0;
}
