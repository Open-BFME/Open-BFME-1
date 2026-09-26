struct BfmeTripleZP
{
	void *m_bfmeAZP;
	void *m_bfmeBZP;
	void *m_bfmeCZP;
};

class BfmeLocalZP
{
public:
	BfmeLocalZP();

	void *m_bfmeAZP;
	void *m_bfmeBZP;
	void *m_bfmeCZP;
	void *m_bfmeDZP;
	unsigned char m_bfmeTailZP[4];
};

int __cdecl rva000cbd40(void *first, void *second);

class BfmeTail926C
{
public:
	void bfmeCall926E(void *routine, void *state);

	void *bfmeMakeZP(BfmeTripleZP *source);
};

void *BfmeTail926C::bfmeMakeZP(BfmeTripleZP *source)
{
	BfmeLocalZP local;

	local.m_bfmeAZP = source->m_bfmeAZP;
	local.m_bfmeBZP = source->m_bfmeBZP;
	local.m_bfmeCZP = source->m_bfmeCZP;

	bfmeCall926E((void *)rva000cbd40, &local);

	return local.m_bfmeDZP;
}
