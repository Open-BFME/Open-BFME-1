// cl: /O2 /Ob0

struct Rva000C7CD0Obj
{
	char pad[0xD8];
	unsigned m_D8;
	char pad2[0x3D8];
	int m_4B4;
};

class Rva000C7CD0
{
	char pad[4];
	int m_04;
	int m_08;

public:
	unsigned char ok(Rva000C7CD0Obj *o, int);
};

unsigned char Rva000C7CD0::ok(Rva000C7CD0Obj *o, int)
{
	int a = o->m_4B4;
	if (!a)
		return 1;
	if (o->m_D8 & 0x400000)
		return 1;
	return (m_08 + a) <= m_04;
}
