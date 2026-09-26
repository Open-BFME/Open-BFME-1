// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00249DF0Inner
{
	unsigned char m_pad[0x238];
	unsigned char m_238;
};

struct Rva00249DF0Sub
{
	Rva00249DF0Inner *m_holder;
};

class Rva00249DF0
{
public:
	unsigned char test() const;
};

unsigned char Rva00249DF0::test() const
{
	return ((const Rva00249DF0Sub *)((const char *)this - 0x1C))->m_holder->m_238 != 0;
}
