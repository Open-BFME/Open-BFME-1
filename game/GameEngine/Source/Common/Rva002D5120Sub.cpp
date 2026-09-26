// cl: /O2 /Ob0

struct Rva002D5120Obj
{
	char m_lead[0x1C];
	float m_1c;
};

struct Rva002D5120Holder
{
	char m_lead[0x210];
	Rva002D5120Obj *m_obj;
};

struct Rva002D5120Other
{
	char m_lead[0x70];
	float m_70;
};

class Rva002D5120
{
public:
	void sub();
};

void Rva002D5120::sub()
{
	Rva002D5120Obj *obj = (*(Rva002D5120Holder **)((char *)this - 8))->m_obj;
	if (obj)
	{
		Rva002D5120Other *o = *(Rva002D5120Other **)((char *)this - 0x0C);
		obj->m_1c -= o->m_70;
	}
}
