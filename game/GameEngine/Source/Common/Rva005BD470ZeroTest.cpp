// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva005BD470Obj
{
	unsigned char m_pad[0x1C];
	unsigned char m_1C;
};

int rva005BD470(const Rva005BD470Obj *p)
{
	return p->m_1C == 0;
}

class Rva005BD4D0
{
	unsigned char m_pad[0x0C];
	unsigned m_C;

public:
	unsigned char isTwo() const;
};

unsigned char Rva005BD4D0::isTwo() const
{
	return m_C == 2;
}

