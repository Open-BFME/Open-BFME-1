class BfmeSubBGB
{
public:
	void bfmeDoBGB(int one, int two);
};

int bfmeGoBGB(BfmeSubBGB *sub)
{
	if (sub != 0)
		sub->bfmeDoBGB(8, 0);
	return 0;
}
