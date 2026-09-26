// cl: /O2 /Ob0

struct Rva0021C780Obj
{
	char m_pad[0x94];
	unsigned m_flags;
};

class Rva0021C780
{
public:
	int bit3() const;
};

int Rva0021C780::bit3() const
{
	Rva0021C780Obj *o = *(Rva0021C780Obj **)((char *)this - 0x18);
	return (int)((o->m_flags >> 3) & 1);
}
