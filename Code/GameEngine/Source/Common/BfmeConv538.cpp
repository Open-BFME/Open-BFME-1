class BfmeSubBVC
{
public:
	void bfmeDoBVC(void *one, void *two, void *three, void *four);
};

class BfmeThingBVC
{
public:
	void *bfmeGoBVC(void *one, void *two, void *three, void *four);
	unsigned char m_bfmeHead[4];
	BfmeSubBVC *m_bfmeSub;
};

void *BfmeThingBVC::bfmeGoBVC(void *one, void *two, void *three, void *four)
{
	m_bfmeSub->bfmeDoBVC(one, two, three, four);
	return one;
}
