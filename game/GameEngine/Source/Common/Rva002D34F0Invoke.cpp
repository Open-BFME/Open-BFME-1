// cl: /O2 /Ob0
//
// 11-byte adjust-ecx tail jmp: ecx = *(this-0x1C) + 0x14; jmp ILT 0x0002644F.

class Gen0002644F
{
public:
	void handle();
};

struct Rva002D34F0Holder
{
	char m_lead[0x14];
	Gen0002644F m_sub;
};

class Rva002D34F0
{
public:
	void invoke();
};

void Rva002D34F0::invoke()
{
	Rva002D34F0Holder *holder = *(Rva002D34F0Holder **)((char *)this - 0x1C);
	holder->m_sub.handle();
}
