void *bfmeMakeBOA(void *what);

class BfmeThingBOA
{
public:
	void bfmeGoBOA(void **out, void *spare);
	void *m_bfmeWhat;
};

void BfmeThingBOA::bfmeGoBOA(void **out, void *spare)
{
	void *old = m_bfmeWhat;
	m_bfmeWhat = bfmeMakeBOA(old);
	*out = old;
}
