// cl: /O2 /Ob0

class HoldRva002B3080
{
public:
	char m_lead[0x7C];
	unsigned char m_value;
};

class Rva002B3080
{
public:
	unsigned char get() const;
};

unsigned char Rva002B3080::get() const
{
	const HoldRva002B3080 *holder =
		*(const HoldRva002B3080 *const *)((const char *)this - 0x33C);
	return holder->m_value;
}
