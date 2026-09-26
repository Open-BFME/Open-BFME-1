// cl: /O2 /Ob0

class HoldRva002C60B0
{
public:
	char m_lead[0x7C];
	int m_value;
};

class Rva002C60B0
{
public:
	int get() const;
};

int Rva002C60B0::get() const
{
	const HoldRva002C60B0 *holder =
		*(const HoldRva002C60B0 *const *)((const char *)this - 0x33C);
	return holder->m_value;
}
