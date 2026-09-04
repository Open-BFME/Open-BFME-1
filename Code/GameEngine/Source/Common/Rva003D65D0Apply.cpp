// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva003D65D0Flags
{
    char m_pad00[0x0C];
    unsigned m_flags;
};

extern void j_0002f3f6(void);
typedef bool (__cdecl *Rva003D65D0Helper)(unsigned slot);

class Rva003D65D0
{
public:
    int apply(void *unused0, Rva003D65D0Flags *source, int a, int b);

private:
    char m_pad00[0x4];
    float *m_at04;
	volatile unsigned m_at08;
};

int Rva003D65D0::apply(void *unused0, Rva003D65D0Flags *source,
    int a, int b)
{
    (void)unused0;
    unsigned flags = source->m_flags;
    unsigned low = flags & 7;
    if (low == 5 || low == 2 || low == 4)
        return 1;
    if ((unsigned char)(flags >> 21) & 1)
        return 1;
    if (m_at08 == 1)
    {
        unsigned slot = (flags >> 6) & 0x3F;
		if (((Rva003D65D0Helper)j_0002f3f6)(slot))
            return 1;
    }
    int sa = a * 10;
    float *dst = m_at04;
    unsigned slot = (flags >> 6) & 0x3F;
    m_at08 = slot;
    dst[0] = (float)sa;
	dst = m_at04;
	dst[1] = (float)((b << 3) + (b << 1));
    return 0;
}
