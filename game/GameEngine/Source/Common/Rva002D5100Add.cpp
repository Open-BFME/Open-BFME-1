// cl: /O2 /Ob0

struct Rva002D5100Obj
{
	char m_lead[0x1C];
	float m_1c;
};

struct Rva002D5100Holder
{
	char m_lead[0x210];
	Rva002D5100Obj *m_obj;
};

struct Rva002D5100Other
{
	char m_lead[0x70];
	float m_70;
};

class Rva002D5100
{
public:
	void add();
};

void Rva002D5100::add()
{
	Rva002D5100Obj *obj = (*(Rva002D5100Holder **)((char *)this - 8))->m_obj;
	if (obj)
	{
		Rva002D5100Other *o = *(Rva002D5100Other **)((char *)this - 0x0C);
		obj->m_1c += o->m_70;
	}
}
