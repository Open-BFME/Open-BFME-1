void __stdcall bfmeDoBLA(int what);

class BfmeThingBLA
{
public:
	void bfmeGoBLA(void *what, bool flag);
	unsigned char m_bfmeHead[0x18];
	void *m_bfmeWhat;
};

void BfmeThingBLA::bfmeGoBLA(void *what, bool flag)
{
	m_bfmeWhat = what;
	if (flag)
		bfmeDoBLA(1);
}
