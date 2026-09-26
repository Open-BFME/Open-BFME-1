// cl: /O2 /Ob0

class HoldRva002C5DA0
{
public:
	char m_lead[0x64];
	int m_value;
};

class Rva002C5DA0
{
public:
	int get() const;
};

int Rva002C5DA0::get() const
{
	const HoldRva002C5DA0 *holder =
		*(const HoldRva002C5DA0 *const *)((const char *)this - 0x33C);
	return holder->m_value;
}
