extern "C" __declspec(dllimport) unsigned int __stdcall bfmeTickDZC();

struct BfmeThingDZC
{
	bool bfmeGoDZC();
	unsigned char m_bfmeHead[0x12110];
	unsigned int m_bfmeT;
};

bool BfmeThingDZC::bfmeGoDZC()
{
	if (!m_bfmeT)
		return false;
	return bfmeTickDZC() - m_bfmeT > 10000;
}

class BfmeUiDZD
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
	virtual void bfmeV22();
	virtual void bfmeV23();
	virtual void bfmeV24();
	virtual void bfmeV25();
	virtual void bfmeV26();
	virtual void bfmeV27();
	virtual void bfmeV28();
	virtual void bfmeV29();
	virtual void bfmeV30();
	virtual void bfmeV31();
	virtual void bfmeV32();
	virtual void bfmeV33();
	virtual void bfmeV34();
	virtual void bfmeV35();
	virtual void bfmeV36();
	virtual void bfmeV37();
	virtual void bfmeV38();
	virtual void bfmeV39();
	virtual void bfmeV40();
	virtual void bfmeV41();
	virtual void bfmeV42();
	virtual bool bfmeAskDZD();
};

extern BfmeUiDZD *g_bfmeUiDZD;

struct BfmeThingDZD
{
	void bfmeGoDZD(void *unused);
	void bfmeDoDZD();
	unsigned char m_bfmeHead[0x1c0];
	unsigned int m_bfmeT;
};

void BfmeThingDZD::bfmeGoDZD(void *unused)
{
	if (g_bfmeUiDZD->bfmeAskDZD())
	{
		bfmeDoDZD();
		m_bfmeT = bfmeTickDZC();
	}
}
