// cl: /O2 /Ob0

struct Rva002C7DE0Blk
{
	int a;
	int b;
	int c;
};

class Rva002C7DE0
{
	char pad[0xC0];
	Rva002C7DE0Blk m_C0;
	unsigned char m_CC;

public:
	unsigned char get(Rva002C7DE0Blk *out);
};

unsigned char Rva002C7DE0::get(Rva002C7DE0Blk *out)
{
	*out = m_C0;
	return m_CC;
}
