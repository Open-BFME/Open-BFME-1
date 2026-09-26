// cl: /O2 /Ob0

class Obj001DCD90
{
public:
	char pad[0x344];
	unsigned char m_344;
};

int __stdcall rva001dcd90(Obj001DCD90 *p)
{
	return p->m_344 & 1;
}
