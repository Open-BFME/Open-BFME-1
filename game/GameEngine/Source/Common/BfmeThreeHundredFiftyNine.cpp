extern "C" unsigned char bfmeVftVB[];

void __stdcall bfmeFreeVB(void *what);

class BfmeThingVB
{
public:
	void bfmeDtorVB(void *what);
	void *bfmeKillVB(int flags);
	void *m_bfmeVft;
	void *m_bfmeWhat;
};

void *BfmeThingVB::bfmeKillVB(int flags)
{
	m_bfmeVft = bfmeVftVB;
	bfmeDtorVB(m_bfmeWhat);
	if ((flags & 1) != 0)
		bfmeFreeVB(this);
	return this;
}
