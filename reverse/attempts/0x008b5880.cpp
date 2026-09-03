// ??0Rva008B5880@@QAE@PAURva008B5880Arg@@@Z
// partial score=0.81 date=2026-09-02
// cl: /O2 /DNDEBUG /MD

extern "C" void *bfmeVft008B5880[];

struct Rva008B5880Inner
{
	char m_pad[4];
	void *m_04;
};

struct Rva008B5880Mid
{
	char m_pad[0x0c];
	Rva008B5880Inner *m_0c;
};

struct Rva008B5880Arg
{
	char m_pad[0x50];
	Rva008B5880Mid *m_50;

	__forceinline void *pick()
	{
		return m_50->m_0c->m_04;
	}
};

class Rva899F00Base
{
public:
	Rva899F00Base(const char *id, int kind);
};

class Rva008B5880 : public Rva899F00Base
{
public:
	Rva008B5880(Rva008B5880Arg *arg);

	void *m_vfptr;
	char m_pad04[0x1c];
	void *m_20;
	int m_24;
	int m_28;
};

Rva008B5880::Rva008B5880(Rva008B5880Arg *arg) :
	Rva899F00Base(reinterpret_cast<const char *>(0x15), 8)
{
	int z = 0;
	m_24 = z;
	m_vfptr = bfmeVft008B5880;
	void *v = arg->pick();
	m_28 = z;
	m_20 = v;
}
