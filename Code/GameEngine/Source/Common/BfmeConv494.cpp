int __stdcall bfmeDoBNA(void *what);

class BfmeThingBNA
{
public:
	int bfmeGoBNA();
	unsigned char m_bfmeHead[0x18];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap[0x25];
	bool m_bfmeBusy;
};

int BfmeThingBNA::bfmeGoBNA()
{
	if (m_bfmeBusy)
		return -2;
	void *what = m_bfmeWhat;
	m_bfmeBusy = true;
	return bfmeDoBNA(what);
}
