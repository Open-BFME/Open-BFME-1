// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// The constructor stores vtable 0x01136AF8 after calling Rva00899F00Base's
// constructor at 0x00899F00.  The address-derived type name reflects that
// the retail binary does not expose a trusted public class name.

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

	int *m_vfptr;
	char m_pad04[0x1c];
	void *m_20;
	void *m_24;
	void *m_28;
};

Rva008B5880::Rva008B5880(Rva008B5880Arg *arg) :
	Rva899F00Base(reinterpret_cast<const char *>(0x15), 8)
{
	Rva008B5880Arg *p = arg;
	m_24 = reinterpret_cast<void *>(0);
	m_vfptr = reinterpret_cast<int *>(bfmeVft008B5880);
	int z = 0;
	void *v = p->m_50->m_0c->m_04;
	m_20 = v;
	m_28 = reinterpret_cast<void *>(z);
}
