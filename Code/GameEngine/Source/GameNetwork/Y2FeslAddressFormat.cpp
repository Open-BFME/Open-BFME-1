// cl: /O2
// 0x007E8760: FESL address.cpp dotted-quad format. Buffer shorter than
// 17 bytes is the "false" assert at line 49.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();
extern "C" int __cdecl sprintf(char *buf, const char *fmt, ...);

class Rva007E8760Addr
{
public:
	void format(char *buf, unsigned size);

private:
	char m_pad[8];
	unsigned m_addr;
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
