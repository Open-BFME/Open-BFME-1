class BfmeSubBIC
{
public:
	int bfmeAskBIC();
};

int __stdcall bfmeGoBIC(BfmeSubBIC *sub)
{
	if (sub == 0)
		return -1;
	return sub->bfmeAskBIC();
}
