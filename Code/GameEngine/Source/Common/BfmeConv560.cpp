class BfmeThingCAA
{
public:
	virtual void bfmeSpareCAA0();
	virtual void bfmeSpareCAA1();
	virtual void bfmeSpareCAA2();
	virtual void bfmeSpareCAA3();
	virtual void bfmeSpareCAA4();
	virtual void bfmeSpareCAA5();
	virtual void bfmeSpareCAA6();
	virtual void bfmeSpareCAA7();
	virtual void bfmeSpareCAA8();
	virtual void bfmeSpareCAA9();
	virtual void bfmeSpareCAA10();
	virtual void bfmeSpareCAA11();
	virtual void bfmeSpareCAA12();
	virtual void bfmeSpareCAA13();
	virtual void bfmeSpareCAA14();
	virtual void bfmeSpareCAA15();
	virtual void bfmeStepCAA16();
	virtual void bfmeStepCAA17();
	virtual void bfmeStepCAA18();
	virtual void bfmeStepCAA19();
	void bfmeTailCAA();
	void bfmeGoCAA();
};

void BfmeThingCAA::bfmeGoCAA()
{
	bfmeStepCAA16();
	bfmeStepCAA17();
	bfmeStepCAA18();
	bfmeStepCAA19();
	bfmeTailCAA();
}
