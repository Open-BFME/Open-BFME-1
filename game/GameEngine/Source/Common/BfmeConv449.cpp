class BfmeThingBED
{
public:
	virtual void bfmeSpareBED0();
	virtual void bfmeSpareBED1();
	virtual void bfmeSpareBED2();
	virtual void bfmeSpareBED3();
	virtual void bfmeSpareBED4();
	virtual void bfmeSpareBED5();
	virtual void bfmeSpareBED6();
	virtual void bfmeSpareBED7();
	virtual void bfmeSpareBED8();
	virtual void bfmeSpareBED9();
	virtual void bfmeSpareBEDA();
	virtual void bfmeSpareBEDB();
	virtual void bfmeSpareBEDC();
	virtual void bfmeSpareBEDD();
	virtual void bfmeSpareBEDE();
	virtual void bfmeSpareBEDF();
	virtual void bfmeSpareBEDG();
	virtual void bfmeSpareBEDH();
	virtual void bfmeSpareBEDI();
	virtual void bfmeSpareBEDJ();
	virtual void bfmeSpareBEDK();
	virtual void bfmeSpareBEDL();
	virtual void bfmeSpareBEDM();
	virtual void bfmeSpareBEDN();
	virtual void bfmeSpareBEDO();
	virtual void bfmeSpareBEDP();
	virtual void bfmeSpareBEDQ();
	virtual void bfmeSpareBEDR();
	virtual void bfmeSpareBEDS();
	virtual void bfmeSpareBEDT();
	virtual void bfmeSetBED(int what);
	void bfmeTailBED();
	void bfmeGoBED();
};

void BfmeThingBED::bfmeGoBED()
{
	bfmeSetBED(2);
	bfmeTailBED();
}
