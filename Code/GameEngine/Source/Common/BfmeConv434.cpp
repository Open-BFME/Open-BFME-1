void *bfmeLookBBB(void *what);

class BfmeThingBBB
{
public:
	void *bfmeGetBBB();
	void *m_bfmeSub;
};

void *BfmeThingBBB::bfmeGetBBB()
{
	void *sub = m_bfmeSub;
	return (char *)bfmeLookBBB(sub) + 0x10;
}
