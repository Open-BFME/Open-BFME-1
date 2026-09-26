// cl: /O2 /Ob0

class Obj001DCD70
{
public:
	char pad[0x344];
	unsigned char m_344;
};

int __stdcall rva001dcd70(Obj001DCD70 *p)
{
	unsigned char v = p->m_344;
	v = ~v;
	return v & 1;
}
