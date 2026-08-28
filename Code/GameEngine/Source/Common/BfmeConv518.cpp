class BfmeThingBRD
{
public:
	void bfmeDoBRD(void *one, void *two, void *three);
	BfmeThingBRD *bfmeGoBRD(void *one, void *two, void *three);
};

BfmeThingBRD *BfmeThingBRD::bfmeGoBRD(void *one, void *two, void *three)
{
	bfmeDoBRD(one, two, three);
	return this;
}
