// Open-BFME5 conversions.

struct BfmeVec1256
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeR1256
{
public:
	virtual void bfmeV1256_00();
	virtual void bfmeV1256_01();
	virtual void bfmeV1256_02();
	virtual void bfmeV1256_03();
	virtual void bfmeV1256_04();
	virtual void bfmeV1256_05();
	virtual void bfmeV1256_06();
	virtual void bfmeV1256_07();
	virtual void bfmeV1256_08();
	virtual void bfmeV1256_09();
	virtual void bfmeV1256_10();
	virtual void bfmeV1256_11();
	virtual void bfmeV1256_12();
	virtual void bfmeV1256_13();
	virtual void bfmeV1256_14();
	virtual void bfmeV1256_15();
	virtual void bfmeV1256_16();
	virtual void bfmeV1256_17();
	virtual void bfmeV1256_18();
	virtual void bfmeV1256_19();
	virtual void bfmeV1256_20();
	virtual void bfmeV1256_21();
	virtual void bfmeV1256_22();
	virtual void bfmeV1256_23();
	virtual void bfmeV1256_24();
	virtual void bfmeV1256_25();
	virtual void bfmeV1256_26();
	virtual void bfmeV1256_27();
	virtual void bfmeV1256_28();
	virtual void bfmeV1256_29();
	virtual void bfmeV1256_30();
	virtual void bfmeV1256_31();
	virtual void bfmeV1256_32();
	virtual void bfmeV1256_33();
	virtual void bfmeV1256_34();
	virtual void bfmeV1256_35();
	virtual void bfmeV1256_36();
	virtual void bfmeV1256_37();
	virtual void bfmeV1256_38();
	virtual void bfmeV1256_39();
	virtual void bfmeV1256_40();
	virtual void bfmeV1256_41();
	virtual void bfmeV1256_42();
	virtual void bfmeV1256_43();
	virtual void bfmeV1256_44();
	virtual void bfmeV1256_45();
	virtual void bfmeV1256_46();
	virtual void bfmeV1256_47();
	virtual void bfmeV1256_48();
	virtual void bfmeV1256_49();
	virtual void bfmeV1256_50();
	virtual void bfmeV1256_51();
	virtual void bfmeV1256_52();
	virtual void bfmeV1256_53();
	virtual void bfmeV1256_54();
	virtual void bfmeV1256_55();
	virtual void bfmeV1256_56();
	virtual void bfmeV1256_57();
	virtual void bfmeV1256_58();
	virtual void bfmeV1256_59();
	virtual void bfmeV1256_60();
	virtual void bfmeV1256_61();
	virtual void bfmeV1256_62();
	virtual void bfmeV1256_63();
	virtual void bfmeV1256_64();
	virtual void bfmeV1256_65();
	virtual void bfmeV1256_66();
	virtual void bfmeV1256_67();
	virtual void bfmeV1256_68();
	virtual void bfmeV1256_69();
	virtual void bfmeV1256_70();
	virtual void bfmeV1256_71();
	virtual void bfmeV1256_72();
	virtual void bfmeV1256_73();
	virtual void bfmeV1256_74();
	virtual void bfmeV1256_75();
	virtual void bfmeV1256_76();
	virtual void bfmeV1256_77();
	virtual void bfmeV1256_78();
	virtual void bfmeV1256_79();
	virtual void bfmeV1256_80();
	virtual void bfmeV1256_81();
	virtual void bfmeV1256_82();
	virtual void bfmeV1256_83();
	virtual void bfmeV1256_84();
	virtual void bfmeV1256_85();
	virtual void bfmeV1256_86();
	virtual void bfmeV1256_87();
	virtual void bfmeV1256_88();
	virtual void bfmeV1256_89();
	virtual void bfmeV1256_90();
	virtual void bfmeV1256_91();
	virtual void bfmeV1256_92();
	virtual void bfmeV1256_93();
	virtual void bfmeMark1256(int a, BfmeVec1256 *b, unsigned int c);
};

extern BfmeR1256 *g_bfme1256;
extern const float g_bfmeK1256;

class BfmeQ1256
{
public:
	char m_bfmePad00[0x1c4];
	unsigned int m_bfme1c4;
};

class BfmeS1256
{
public:
	BfmeQ1256 *bfmeGet1256();
};

class BfmeP1256
{
public:
	char m_bfmePad00[0x38];
	BfmeVec1256 m_bfme38;
};

class BfmeA1256
{
public:
	void bfmeDraw1256(BfmeS1256 *a, int b);
	char m_bfmePad00[8];
	BfmeP1256 *m_bfme08;
};

void BfmeA1256::bfmeDraw1256(BfmeS1256 *a, int b)
{
	BfmeVec1256 v;
	BfmeVec1256 *q;
	unsigned int c;

	q = &m_bfme08->m_bfme38;
	v.m_bfme00 = q->m_bfme00;
	v.m_bfme04 = q->m_bfme04;
	v.m_bfme08 = *(volatile float *)&q->m_bfme08 + g_bfmeK1256;
	c = a->bfmeGet1256()->m_bfme1c4 | 0xe6000000;
	g_bfme1256->bfmeMark1256(b, &v, c);
}
