// cl: /O2 /Ob0

struct Rva001073B0Blk
{
	int a;
	int b;
	int c;
	int d;
};

class Rva001073B0
{
	char pad[0x1454];
	Rva001073B0Blk m_1454;
	char m_1464;

public:
	void set(const Rva001073B0Blk *v);
};

void Rva001073B0::set(const Rva001073B0Blk *v)
{
	m_1454 = *v;
	m_1464 = 1;
}
