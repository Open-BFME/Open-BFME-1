// cl: /DNDEBUG /MD /EHsc /O2 /Ob0
//
// Open-BFME: retail 0x0020A900 size 116. Near-twin of the already-landed
// SpawnBehavior::maySpawnSelfTaskAI (Code/.../SpawnBehavior.cpp, marked
// present-unmatched there) with different field offsets: this build's
// Object/SpawnBehavior headers do not carry BFME's true layout, so this
// is a fresh twin using address-derived offsets read straight from the
// retail bytes, matching docs/matching.md's near-twin recipe rather than
// editing the shared header.

extern float g_bfmeZeroCY; // retail 0x01075350 (0.0f)
extern float g_bfmeUint32Scale; // retail 0x01075358 (2^32 conversion fixup)

class Rva0020A900Ai
{
public:
	virtual void bfmeAiSlot0020A900_0();
	virtual void bfmeAiSlot0020A900_1();
	virtual void bfmeAiSlot0020A900_2();
	virtual void bfmeAiSlot0020A900_3();
	virtual void bfmeAiSlot0020A900_4();
	virtual void bfmeAiSlot0020A900_5();
	virtual void bfmeAiSlot0020A900_6();
	virtual void bfmeAiSlot0020A900_7();
	virtual void bfmeAiSlot0020A900_8();
	virtual void bfmeAiSlot0020A900_9();
	virtual void bfmeAiSlot0020A900_10();
	virtual void bfmeAiSlot0020A900_11();
	virtual void bfmeAiSlot0020A900_12();
	virtual void bfmeAiSlot0020A900_13();
	virtual void bfmeAiSlot0020A900_14();
	virtual void bfmeAiSlot0020A900_15();
	virtual void bfmeAiSlot0020A900_16();
	virtual void bfmeAiSlot0020A900_17();
	virtual void bfmeAiSlot0020A900_18();
	virtual void bfmeAiSlot0020A900_19();
	virtual void bfmeAiSlot0020A900_20();
	virtual void bfmeAiSlot0020A900_21();
	virtual void bfmeAiSlot0020A900_22();
	virtual void bfmeAiSlot0020A900_23();
	virtual void bfmeAiSlot0020A900_24();
	virtual void bfmeAiSlot0020A900_25();
	virtual void bfmeAiSlot0020A900_26();
	virtual void bfmeAiSlot0020A900_27();
	virtual void bfmeAiSlot0020A900_28();
	virtual void bfmeAiSlot0020A900_29();
	virtual void bfmeAiSlot0020A900_30();
	virtual void bfmeAiSlot0020A900_31();
	virtual void bfmeAiSlot0020A900_32();
	virtual void bfmeAiSlot0020A900_33();
	virtual void bfmeAiSlot0020A900_34();
	virtual void bfmeAiSlot0020A900_35();
	virtual void bfmeAiSlot0020A900_36();
	virtual void bfmeAiSlot0020A900_37();
	virtual void bfmeAiSlot0020A900_38();
	virtual void bfmeAiSlot0020A900_39();
	virtual void bfmeAiSlot0020A900_40();
	virtual void bfmeAiSlot0020A900_41();
	virtual void bfmeAiSlot0020A900_42();
	virtual void bfmeAiSlot0020A900_43();
	virtual void bfmeAiSlot0020A900_44();
	virtual void bfmeAiSlot0020A900_45();
	virtual void bfmeAiSlot0020A900_46();
	virtual void bfmeAiSlot0020A900_47();
	virtual void bfmeAiSlot0020A900_48();
	virtual void bfmeAiSlot0020A900_49();
	virtual void bfmeAiSlot0020A900_50();
	virtual void bfmeAiSlot0020A900_51();
	virtual void bfmeAiSlot0020A900_52();
	virtual void bfmeAiSlot0020A900_53();
	virtual void bfmeAiSlot0020A900_54();
	virtual void bfmeAiSlot0020A900_55();
	virtual void bfmeAiSlot0020A900_56();
	virtual void bfmeAiSlot0020A900_57();
	virtual void bfmeAiSlot0020A900_58();
	virtual void bfmeAiSlot0020A900_59();
	virtual void bfmeAiSlot0020A900_60();
	virtual void bfmeAiSlot0020A900_61();
	virtual void bfmeAiSlot0020A900_62();
	virtual void bfmeAiSlot0020A900_63();
	virtual void bfmeAiSlot0020A900_64();
	virtual void bfmeAiSlot0020A900_65();
	virtual void bfmeAiSlot0020A900_66();
	virtual void bfmeAiSlot0020A900_67();
	virtual void bfmeAiSlot0020A900_68();
	virtual void bfmeAiSlot0020A900_69();
	virtual void bfmeAiSlot0020A900_70();
	virtual void bfmeAiSlot0020A900_71();
	virtual void bfmeAiSlot0020A900_72();
	virtual void bfmeAiSlot0020A900_73();
	virtual void bfmeAiSlot0020A900_74();
	virtual void bfmeAiSlot0020A900_75();
	virtual void bfmeAiSlot0020A900_76();
	virtual void bfmeAiSlot0020A900_77();
	virtual void bfmeAiSlot0020A900_78();
	virtual void bfmeAiSlot0020A900_79();
	virtual void bfmeAiSlot0020A900_80();
	virtual void bfmeAiSlot0020A900_81();
	virtual void bfmeAiSlot0020A900_82();
	virtual void bfmeAiSlot0020A900_83();
	virtual void bfmeAiSlot0020A900_84();
	virtual void bfmeAiSlot0020A900_85();
	virtual void bfmeAiSlot0020A900_86();
	virtual void bfmeAiSlot0020A900_87();
	virtual void bfmeAiSlot0020A900_88();
	virtual void bfmeAiSlot0020A900_89();
	virtual void bfmeAiSlot0020A900_90();
	virtual void bfmeAiSlot0020A900_91();
	virtual void bfmeAiSlot0020A900_92();
	virtual void bfmeAiSlot0020A900_93();
	virtual void bfmeAiSlot0020A900_94();
	virtual void bfmeAiSlot0020A900_95();
	virtual void bfmeAiSlot0020A900_96();
	virtual void bfmeAiSlot0020A900_97();
	virtual void bfmeAiSlot0020A900_98();
	virtual void bfmeAiSlot0020A900_99();
	virtual void bfmeAiSlot0020A900_100();
	virtual void bfmeAiSlot0020A900_101();
	virtual void bfmeAiSlot0020A900_102();
	virtual void bfmeAiSlot0020A900_103();
	virtual void bfmeAiSlot0020A900_104();
	virtual void bfmeAiSlot0020A900_105();
	virtual void bfmeAiSlot0020A900_106();
	virtual void bfmeAiSlot0020A900_107();
	virtual void bfmeAiSlot0020A900_108();
	virtual void bfmeAiSlot0020A900_109();
	virtual void bfmeAiSlot0020A900_110();
	virtual void bfmeAiSlot0020A900_111();
	virtual void bfmeAiSlot0020A900_112();
	virtual void bfmeAiSlot0020A900_113();
	virtual void bfmeAiSlot0020A900_114();
	virtual void bfmeAiSlot0020A900_115();
	virtual void bfmeAiSlot0020A900_116();
	virtual void bfmeAiSlot0020A900_117();
	virtual void bfmeAiSlot0020A900_118();
	virtual void bfmeAiSlot0020A900_119();
	virtual void bfmeAiSlot0020A900_120();
	virtual void bfmeAiSlot0020A900_121();
	virtual void bfmeAiSlot0020A900_122();
	virtual void bfmeAiSlot0020A900_123();
	virtual void bfmeAiSlot0020A900_124();
	virtual void bfmeAiSlot0020A900_125();
	virtual void bfmeAiSlot0020A900_126();
	virtual void bfmeAiSlot0020A900_127();
	virtual int bfmeGetCmdSource0020A900();
};

class Rva0020A900Object
{
public:
	unsigned char m_pad0[0x204];
	Rva0020A900Ai *m_ai; // +0x204
};

class Rva0020A900Host
{
public:
	unsigned char m_pad0[0x30];
	int m_spawnCount; // +0x30
	unsigned int m_selfTaskingSpawnCount; // +0x34

	bool maySpawnSelfTaskAI(float maxSelfTaskersRatio);
};

bool Rva0020A900Host::maySpawnSelfTaskAI(float maxSelfTaskersRatio)
{
	if (m_spawnCount == 0)
		return false;
	if (maxSelfTaskersRatio == g_bfmeZeroCY)
		return false;

	Rva0020A900Object *obj = *(Rva0020A900Object **)((char *)this - 0x18);
	if (!obj)
		return false;
	Rva0020A900Ai *ai = obj->m_ai;
	if (!ai)
		return false;

	int lastAttackCommandSource = ai->bfmeGetCmdSource0020A900();
	if (lastAttackCommandSource != 2)
		return false;

	float curSelfTaskersRatio = (float)m_selfTaskingSpawnCount / (float)m_spawnCount;

	return curSelfTaskersRatio < maxSelfTaskersRatio;
}

