class BfmeThingCBF
{
public:
	void *bfmeGoCBF(unsigned int flags);
	void *m_bfmePtr;
};

void bfmeDtorCBF(void *what);
void bfmeFreeCBF(void *what);

void *BfmeThingCBF::bfmeGoCBF(unsigned int flags)
{
	bfmeDtorCBF(m_bfmePtr);
	if (flags & 1)
		bfmeFreeCBF(this);
	return this;
}
