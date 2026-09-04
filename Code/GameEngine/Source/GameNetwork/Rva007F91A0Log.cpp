// cl: /O2 /Ob0
// Converted from Code/gen_asm/d_007f2a50.asm (?d_007f91a0@@YAXXZ).
// Rva007EB810Get()->log(0, "conn err %d\n", err) then [this+0x6A4] vslot 2 (0, 0).

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void log(int level, const char *format, ...);
	virtual void fail(const char *expr, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get();

struct Rva007F91A0Sink
{
	virtual void v0();
	virtual void v1();
	virtual void slot2(int a, int b);
};

class Rva007F91A0Host
{
public:
	void apply(int err);

	char m_pad[0x6A4];
	Rva007F91A0Sink *m_sink;
};

void Rva007F91A0Host::apply(int err)
{
	Rva007EB810Get()->log(0, "conn err %d\n", err);
	m_sink->slot2(0, 0);
}
