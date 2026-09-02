// cl: /O2
// 0x007F4980: ariesudp.cpp slot store. Index must be 0 or 1; otherwise
// Get()->fail("false", ariesudp.cpp, 76).

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get();

class Rva007F4980
{
public:
	void set(void *p, int i);

private:
	char m_pad[8];
	void *m_slot[2];
};

void Rva007F4980::set(void *p, int i)
{
	if (i < 0 || i >= 2)
		Rva007EB810Get()->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\ariesudp.cpp",
			76);
	else
		m_slot[i] = p;
}
