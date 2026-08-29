// Open-BFME5 conversions: a begin / forward / end wrapper family.

class Bfme5Host
{
public:
	virtual void bfmeVM0();
	virtual void bfmeVM1();
	virtual void bfmeVM2();
	virtual void bfmeVM3();
	virtual void bfmeVM4();
	virtual void bfmeVM5();
	virtual void bfmeVM6();
	virtual void bfmeVM7();
	virtual void bfmeVM8();
	virtual void bfmeVM9();
	virtual void bfmeVM10();
	virtual void bfmeVM11();
	virtual void bfmeVM12();
	virtual void bfmeVM13();
	virtual void bfmeVM14();
	virtual void bfmeVM15();
	virtual void bfmeVM16();
	virtual void bfmeVM17();
	virtual void bfmeVM18();
	virtual void bfmeVM19();
	virtual void bfmeVM20();
	virtual void bfmeVM21();
	virtual void bfmeVM22();
	virtual void bfmeVM23();
	virtual void bfmeVM24();
	virtual void bfmeVM25();
	virtual void bfmeVM26();
	virtual void bfmeVM27();
	virtual void bfmeVM28();
	virtual void bfmeVM29();
	virtual void bfmeVM30();
	virtual void bfmeVM31();
	virtual void bfmeVM32();
	virtual void bfmeVM33();
	virtual void bfmeVM34();
	virtual void bfmeVM35();
	virtual void bfmeVM36();
	virtual void bfmeVM37();
	virtual void bfmeVM38();
	virtual void bfmeVM39();
	virtual void bfmeVM40();
	virtual void bfmeVM41();
	virtual void bfmeVM42();
	virtual void bfmeVM43();
	virtual void bfmeBegin();
	virtual void bfmeWorkA(int a, int b, int c, int d, int e, int f, int g);
	virtual void bfmeVM46();
	virtual void bfmeVM47();
	virtual void bfmeWorkB(int a, int b, int c, int d, int e);
	virtual void bfmeWorkC(int a, int b, int c, int d, int e);
	virtual void bfmeVM50();
	virtual void bfmeVM51();
	virtual void bfmeWorkD(int a, int b, int c, int d, int e, int f, int g);
	virtual void bfmeWorkE(int a, int b, int c, int d, int e, int f, int g);
	virtual void bfmeVM54();
	virtual void bfmeEnd();

	void bfmeRunB(int a, int b, int c, int d, int e);
	void bfmeRunC(int a, int b, int c, int d, int e);
	void bfmeRunA(int a, int b, int c, int d, int e, int f, int g);
	void bfmeRunD(int a, int b, int c, int d, int e, int f, int g);
	void bfmeRunE(int a, int b, int c, int d, int e, int f, int g);
};

void Bfme5Host::bfmeRunB(int a, int b, int c, int d, int e)
{
	bfmeBegin();
	bfmeWorkB(a, b, c, d, e);
	bfmeEnd();
}

void Bfme5Host::bfmeRunC(int a, int b, int c, int d, int e)
{
	bfmeBegin();
	bfmeWorkC(a, b, c, d, e);
	bfmeEnd();
}

void Bfme5Host::bfmeRunA(int a, int b, int c, int d, int e, int f, int g)
{
	bfmeBegin();
	bfmeWorkA(a, b, c, d, e, f, g);
	bfmeEnd();
}

void Bfme5Host::bfmeRunD(int a, int b, int c, int d, int e, int f, int g)
{
	bfmeBegin();
	bfmeWorkD(a, b, c, d, e, f, g);
	bfmeEnd();
}

void Bfme5Host::bfmeRunE(int a, int b, int c, int d, int e, int f, int g)
{
	bfmeBegin();
	bfmeWorkE(a, b, c, d, e, f, g);
	bfmeEnd();
}
