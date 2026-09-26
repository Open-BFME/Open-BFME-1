// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva0022B500Inner
{
	unsigned char m_pad[0x238];
	unsigned char m_238;
};

struct Rva0022B500Sub
{
	Rva0022B500Inner *m_holder;
};

class Rva0022B500
{
public:
	unsigned char test() const;
};

unsigned char Rva0022B500::test() const
{
	return ((const Rva0022B500Sub *)((const char *)this - 0x1C))->m_holder->m_238 != 0;
}
