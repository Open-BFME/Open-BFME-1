void bfmeDoBKA(void *what, int flag);

class BfmeThingBKA
{
public:
	void bfmeGoBKA(void *what);
	unsigned char m_bfmeHead[0x1730];
	void *m_bfmeSaved;
};

void BfmeThingBKA::bfmeGoBKA(void *what)
{
	m_bfmeSaved = what;
	bfmeDoBKA(what, 1);
}
