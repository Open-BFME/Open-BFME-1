// cl: /O2 /Ob0

class Obj0075B520
{
public:
	char pad[0x110];
	unsigned char m_110;
};

int rva0075b520(Obj0075B520 *p, int alt)
{
	if (p && (p->m_110 & 0x20))
		return 2;
	return alt;
}
