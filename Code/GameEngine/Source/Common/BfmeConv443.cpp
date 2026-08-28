class BfmeSubBDB
{
public:
	void bfmeDoBDB(void *what, int flag);
};

void bfmeGoBDB(void *one, BfmeSubBDB *two)
{
	two->bfmeDoBDB(one, 0);
}
