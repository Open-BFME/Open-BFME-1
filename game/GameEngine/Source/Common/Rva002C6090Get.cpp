// cl: /O2 /Ob0

class HoldRva002C6090
{
public:
	char m_lead[0x74];
	unsigned char m_value;
};

class Rva002C6090
{
public:
	unsigned char get() const;
};

unsigned char Rva002C6090::get() const
{
	const HoldRva002C6090 *holder =
		*(const HoldRva002C6090 *const *)((const char *)this - 0x33C);
	return holder->m_value;
}
