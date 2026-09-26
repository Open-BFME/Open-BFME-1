// Open-BFME5 conversions.

struct BfmeVec1254
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeR1254
{
public:
	virtual void bfmeV1254_00();
	virtual void bfmeV1254_01();
	virtual void bfmeV1254_02();
	virtual void bfmeV1254_03();
	virtual void bfmeV1254_04();
	virtual void bfmeV1254_05();
	virtual void bfmeV1254_06();
	virtual void bfmeV1254_07();
	virtual void bfmeV1254_08();
	virtual void bfmeV1254_09();
	virtual void bfmeV1254_10();
	virtual void bfmeV1254_11();
	virtual void bfmeV1254_12();
	virtual void bfmeV1254_13();
	virtual void bfmeV1254_14();
	virtual void bfmeV1254_15();
	virtual void bfmeV1254_16();
	virtual void bfmeV1254_17();
	virtual void bfmeV1254_18();
	virtual void bfmeV1254_19();
	virtual void bfmeV1254_20();
	virtual void bfmeV1254_21();
	virtual void bfmeV1254_22();
	virtual void bfmeV1254_23();
	virtual void bfmeV1254_24();
	virtual void bfmeV1254_25();
	virtual void bfmeV1254_26();
	virtual void bfmeV1254_27();
	virtual void bfmeV1254_28();
	virtual void bfmeV1254_29();
	virtual void bfmeV1254_30();
	virtual void bfmeV1254_31();
	virtual void bfmeV1254_32();
	virtual void bfmeV1254_33();
	virtual void bfmeV1254_34();
	virtual void bfmeV1254_35();
	virtual void bfmeV1254_36();
	virtual void bfmeV1254_37();
	virtual void bfmeV1254_38();
	virtual void bfmeV1254_39();
	virtual void bfmeV1254_40();
	virtual void bfmeV1254_41();
	virtual void bfmeV1254_42();
	virtual void bfmeV1254_43();
	virtual void bfmeV1254_44();
	virtual void bfmeV1254_45();
	virtual void bfmeV1254_46();
	virtual void bfmeV1254_47();
	virtual void bfmeV1254_48();
	virtual void bfmeV1254_49();
	virtual void bfmeV1254_50();
	virtual void bfmeV1254_51();
	virtual void bfmeV1254_52();
	virtual void bfmeV1254_53();
	virtual void bfmeV1254_54();
	virtual void bfmeV1254_55();
	virtual void bfmeV1254_56();
	virtual void bfmeV1254_57();
	virtual void bfmeV1254_58();
	virtual void bfmeV1254_59();
	virtual void bfmeV1254_60();
	virtual void bfmeV1254_61();
	virtual void bfmeV1254_62();
	virtual void bfmeV1254_63();
	virtual void bfmeV1254_64();
	virtual void bfmeV1254_65();
	virtual void bfmeV1254_66();
	virtual void bfmeV1254_67();
	virtual void bfmeV1254_68();
	virtual void bfmeV1254_69();
	virtual void bfmeV1254_70();
	virtual void bfmeV1254_71();
	virtual void bfmeV1254_72();
	virtual void bfmeV1254_73();
	virtual void bfmeV1254_74();
	virtual void bfmeV1254_75();
	virtual void bfmeV1254_76();
	virtual void bfmeV1254_77();
	virtual void bfmeV1254_78();
	virtual void bfmeV1254_79();
	virtual void bfmeV1254_80();
	virtual void bfmeV1254_81();
	virtual void bfmeV1254_82();
	virtual void bfmeV1254_83();
	virtual void bfmeV1254_84();
	virtual void bfmeV1254_85();
	virtual void bfmeV1254_86();
	virtual void bfmeV1254_87();
	virtual void bfmeV1254_88();
	virtual void bfmeV1254_89();
	virtual void bfmeV1254_90();
	virtual void bfmeV1254_91();
	virtual void bfmeV1254_92();
	virtual void bfmeV1254_93();
	virtual void bfmeMark1254(int a, BfmeVec1254 *b, unsigned int c);
};

extern BfmeR1254 *g_bfme1254;
extern const float g_bfmeK1254;

class BfmeQ1254
{
public:
	char m_bfmePad00[0x1c4];
	unsigned int m_bfme1c4;
};

class BfmeS1254
{
public:
	BfmeQ1254 *bfmeGet1254();
};

class BfmeP1254
{
public:
	char m_bfmePad00[0x38];
	BfmeVec1254 m_bfme38;
};

class BfmeA1254
{
public:
	void bfmeDraw1254(BfmeS1254 *a, int b);
	char m_bfmePad00[8];
	BfmeP1254 *m_bfme08;
};

void BfmeA1254::bfmeDraw1254(BfmeS1254 *a, int b)
{
	BfmeVec1254 v;
	BfmeVec1254 *q;
	unsigned int c;

	q = &m_bfme08->m_bfme38;
	v.m_bfme00 = q->m_bfme00;
	v.m_bfme04 = q->m_bfme04;
	v.m_bfme08 = *(volatile float *)&q->m_bfme08 + g_bfmeK1254;
	c = a->bfmeGet1254()->m_bfme1c4 | 0xe6000000;
	g_bfme1254->bfmeMark1254(b, &v, c);
}
