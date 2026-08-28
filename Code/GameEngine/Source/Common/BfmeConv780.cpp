class BfmeThingDTK
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual bool bfmeAskDTK();
	void bfmeGoDTK();
	void bfmeGoDTL();
	void bfmeTailDTK();
	void bfmeTailDTL();
};

void BfmeThingDTK::bfmeGoDTK()
{
	if (bfmeAskDTK())
		bfmeTailDTK();
}

void BfmeThingDTK::bfmeGoDTL()
{
	if (bfmeAskDTK())
		bfmeTailDTL();
}
