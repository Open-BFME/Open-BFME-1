void j_00002b8f();

class BfmeThingBNG
{
public:
	void bfmeGoBNG(void *what);
	unsigned char m_bfmeHead[0xb4];
	void *m_bfmeGot;
};

void BfmeThingBNG::bfmeGoBNG(void *what)
{
	m_bfmeGot = reinterpret_cast<void *(__cdecl *)(void *, void *)>(j_00002b8f)(what, what);
}
