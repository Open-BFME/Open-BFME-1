// cl: /O2 /Ob0

class HoldRva002C8330
{
public:
	char m_lead[0x64];
	int m_value;
};

class Rva002C8330
{
public:
	int get() const;
};

int Rva002C8330::get() const
{
	const HoldRva002C8330 *holder =
		*(const HoldRva002C8330 *const *)((const char *)this - 0x340);
	return holder->m_value;
}
