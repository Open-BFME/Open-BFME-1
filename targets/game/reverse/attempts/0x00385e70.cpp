// ?bfmeQueryGJ@@YGHHH@Z
// partial score=0.75 date=2026-09-08
class NetworkInterface
{
public:
	virtual void bfmeVtGJ00();
	virtual void bfmeVtGJ01();
	virtual void bfmeVtGJ02();
	virtual void bfmeVtGJ03();
	virtual void bfmeVtGJ04();
	virtual void bfmeVtGJ05();
	virtual void bfmeVtGJ06();
	virtual void bfmeVtGJ07();
	virtual void bfmeVtGJ08();
	virtual void bfmeVtGJ09();
	virtual void bfmeVtGJ10();
	virtual void bfmeVtGJ11();
	virtual void bfmeVtGJ12();
	virtual void bfmeVtGJ13();
	virtual void bfmeVtGJ14();
	virtual void bfmeVtGJ15();
	virtual void bfmeVtGJ16();
	virtual void bfmeVtGJ17();
	virtual void bfmeVtGJ18();
	virtual void bfmeVtGJ19();
	virtual void bfmeVtGJ20();
	virtual void bfmeVtGJ21();
	virtual void bfmeVtGJ22();
	virtual void bfmeVtGJ23();
	virtual void bfmeVtGJ24();
	virtual void bfmeVtGJ25();
	virtual void bfmeVtGJ26();
	virtual void bfmeVtGJ27();
	virtual void bfmeVtGJ28();
	virtual void bfmeVtGJ29();
	virtual void bfmeVtGJ30();
	virtual void bfmeVtGJ31();
	virtual void bfmeVtGJ32();
	virtual void bfmeVtGJ33();
	virtual void bfmeVtGJ34();
	virtual void bfmeVtGJ35();
	virtual void bfmeVtGJ36();
	virtual void bfmeVtGJ37();
	virtual void bfmeVtGJ38();
	virtual void bfmeVtGJ39();
	virtual void bfmeVtGJ40();
	virtual void bfmeVtGJ41();
	virtual void bfmeVtGJ42();
	virtual void bfmeVtGJ43();
	virtual char bfmeIsFrozenGJ();
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadGJ[0x3c];
	unsigned int m_bfmeStateGJ;
	unsigned char m_bfmeMidGJ[0xcc];
	int m_bfmeModeGJ;
};

extern NetworkInterface *TheNetwork;
extern Rva00367E30Logic *TheBfmeGameLogic;

int __stdcall bfmeQueryGJ(int a, int b)
{
	int mode = TheBfmeGameLogic->m_bfmeModeGJ;

	if (mode == 1 || mode == 5)
	{
		if (TheNetwork == 0 || TheNetwork->bfmeIsFrozenGJ())
			return 3;
	}

	if (TheBfmeGameLogic->m_bfmeStateGJ < 6)
		return 1;

	return 3;
}
