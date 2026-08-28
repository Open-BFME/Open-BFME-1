class BfmeThingBCD
{
public:
	void bfmeStepBCD();
	void bfmeTailBCD();
	void bfmeGoBCD();
};

void BfmeThingBCD::bfmeGoBCD()
{
	bfmeStepBCD();
	bfmeTailBCD();
}
