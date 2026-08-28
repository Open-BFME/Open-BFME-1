class BfmeSubBUC
{
public:
	void bfmeDoBUC(void *one, void *two, void *three, void *four);
};

void bfmeGoBUC(BfmeSubBUC *sub, void *one, void *two, void *three, void *four)
{
	if (sub != 0)
		sub->bfmeDoBUC(one, two, three, four);
}
