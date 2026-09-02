// cl: /O2
// 0x007E8760 / 0x007E86D0: FESL address.cpp dotted-quad format and parse.
// Format asserts if the destination is shorter than 17 bytes (line 49).
// Parse packs %d.%d.%d.%d into this+8 and stores the second argument at +0xC.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();
extern "C" int __cdecl sprintf(char *buf, const char *fmt, ...);
extern "C" int __cdecl sscanf(const char *buf, const char *fmt, ...);

class Rva007E8760Addr
{
public:
	void format(char *buf, unsigned size);
	void parse(const char *str, int extra);

private:
	char m_pad[8];
	unsigned m_addr;
	int m_extra;
};

void Rva007E8760Addr::format(char *buf, unsigned size)
{
	if (size < 17)
		Rva007EB810Get()->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\address.cpp",
			49);
	unsigned v = m_addr;
	sprintf(buf, "%hu.%hu.%hu.%hu",
		(unsigned char)(v >> 24),
		(unsigned char)(v >> 16),
		(unsigned char)(v >> 8),
		(unsigned char)v);
}

void Rva007E8760Addr::parse(const char *str, int extra)
{
	int a, b, c, d;
	sscanf(str, "%d.%d.%d.%d", &a, &b, &c, &d);
	unsigned v = (unsigned)a;
	v = (v << 8) + (unsigned)b;
	v = (v << 8) + (unsigned)c;
	v = (v << 8) + (unsigned)d;
	m_addr = v;
	m_extra = extra;
}
