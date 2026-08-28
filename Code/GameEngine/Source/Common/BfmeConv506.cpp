class BfmeSubBPB
{
public:
	void bfmeDoBPB(void *one, void *two, void *three);
};

void bfmeGoBPB(BfmeSubBPB *sub, void *one, void *two, void *three)
{
	if (sub != 0)
		sub->bfmeDoBPB(one, two, three);
}
