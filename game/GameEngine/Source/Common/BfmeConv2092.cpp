extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class ModelConditionFlags
{
public:
	unsigned int m_bfmeBitsXT[3];
};

class BfmeSinkXT
{
public:
	virtual void bfmeV0() = 0;
	virtual void bfmeV1() = 0;
	virtual void bfmeV2() = 0;
	virtual void bfmeV3() = 0;
	virtual void bfmeV4() = 0;
	virtual void bfmeV5() = 0;
	virtual void bfmeV6() = 0;
	virtual void bfmeV7() = 0;
	virtual void bfmeV8() = 0;
	virtual void bfmeV9() = 0;
	virtual void bfmeV10() = 0;
	virtual void bfmeV11() = 0;
	virtual void bfmeV12() = 0;
	virtual void bfmeV13() = 0;
	virtual void bfmeV14() = 0;
	virtual void bfmeV15() = 0;
	virtual void bfmeV16() = 0;
	virtual void bfmeV17() = 0;
	virtual void bfmeV18() = 0;
	virtual void bfmeV19() = 0;
	virtual void bfmeV20() = 0;
	virtual void bfmeV21() = 0;
	virtual void bfmeV22() = 0;
	virtual void bfmeV23() = 0;
	virtual void bfmeV24() = 0;
	virtual void bfmeV25() = 0;
	virtual void bfmeV26() = 0;
	virtual void bfmeV27() = 0;
	virtual void bfmeV28() = 0;
	virtual void bfmeV29() = 0;
	virtual void bfmeV30() = 0;
	virtual void bfmeV31() = 0;
	virtual void bfmeV32() = 0;
	virtual void bfmeV33() = 0;
	virtual void bfmeV34() = 0;
	virtual void bfmeV35() = 0;
	virtual void bfmeV36() = 0;
	virtual void bfmeV37() = 0;
	virtual void bfmeV38() = 0;
	virtual void bfmeV39() = 0;
	virtual void bfmeV40() = 0;
	virtual void bfmeV41() = 0;
	virtual void bfmeV42() = 0;
	virtual void bfmeV43() = 0;
	virtual void bfmeV44() = 0;
	virtual void bfmeV45() = 0;
	virtual void bfmeV46() = 0;
	virtual void bfmeV47() = 0;
	virtual void bfmeV48() = 0;
	virtual void bfmeV49() = 0;
	virtual void bfmeV50() = 0;
	virtual void bfmeV51() = 0;
	virtual void bfmeV52() = 0;
	virtual void bfmeV53() = 0;
	virtual void bfmeV54() = 0;
	virtual void bfmeV55() = 0;
	virtual void bfmeV56() = 0;
	virtual void bfmeV57() = 0;
	virtual void bfmeV58() = 0;
	virtual void bfmeV59() = 0;
	virtual void bfmeV60() = 0;
	virtual void bfmeV61() = 0;
	virtual void bfmeV62() = 0;
	virtual void bfmeV63() = 0;
	virtual void bfmeV64() = 0;
	virtual void bfmeV65() = 0;
	virtual void bfmeV66() = 0;
	virtual void bfmeV67() = 0;
	virtual void bfmeV68() = 0;
	virtual void bfmeV69() = 0;
	virtual void bfmeV70() = 0;
	virtual void bfmeV71() = 0;
	virtual void bfmeV72() = 0;
	virtual void bfmeV73() = 0;
	virtual void bfmeV74() = 0;
	virtual void bfmeV75() = 0;
	virtual void bfmeV76() = 0;
	virtual void bfmeV77() = 0;
	virtual void bfmeV78() = 0;
	virtual void bfmeV79() = 0;
	virtual void bfmeV80() = 0;
	virtual void bfmeV81() = 0;
	virtual void bfmeV82() = 0;
	virtual void bfmeV83() = 0;
	virtual void bfmeV84() = 0;
	virtual void bfmeV85() = 0;
	virtual void bfmeV86() = 0;
	virtual void bfmeV87() = 0;
	virtual void bfmeV88() = 0;
	virtual void bfmeV89() = 0;
	virtual void bfmeV90() = 0;
	virtual void bfmeV91() = 0;
	virtual void bfmeV92() = 0;
	virtual void bfmeV93() = 0;
	virtual void bfmeV94() = 0;
	virtual void bfmeV95() = 0;
	virtual void bfmeV96() = 0;
	virtual void bfmeV97() = 0;
	virtual void bfmeV98() = 0;
	virtual void bfmeV99() = 0;
	virtual void bfmeV100() = 0;
	virtual void bfmeV101() = 0;
	virtual void bfmeV102() = 0;
	virtual void bfmeV103() = 0;
	virtual void bfmeV104() = 0;
	virtual void bfmeV105() = 0;
	virtual void bfmeV106() = 0;
	virtual void bfmeV107() = 0;
	virtual void bfmeV108() = 0;
	virtual void bfmeV109() = 0;
	virtual void bfmeV110() = 0;
	virtual void bfmeV111() = 0;
	virtual void bfmeV112() = 0;
	virtual void bfmeV113() = 0;
	virtual void bfmeV114() = 0;
	virtual void bfmeV115() = 0;
	virtual void bfmeV116() = 0;
	virtual void bfmeV117() = 0;
	virtual void bfmeV118() = 0;
	virtual void bfmeV119() = 0;
	virtual void bfmeV120() = 0;
	virtual void bfmeV121() = 0;
	virtual void bfmeV122() = 0;
	virtual void bfmeV123() = 0;
	virtual void bfmeV124() = 0;
	virtual void bfmeV125() = 0;
	virtual void bfmeV126() = 0;
	virtual void bfmeNoteXT(int code) = 0;
};

class Object
{
public:
	void applyRva1C7370(const ModelConditionFlags &flags, bool on);
	void clearCondition(int code);

	unsigned char m_bfmeHeadXT[0x204];
	BfmeSinkXT *m_bfme204XT;
};

class BfmeCfgXT
{
public:
	unsigned char m_bfmeHeadXT[8];
	void *m_bfme08XT;
};

class BfmeHostXT
{
public:
	void bfmeRunXT();
	void bfmeApplyXT(Object *obj, int flag);

	unsigned char m_bfmeHeadXT[4];
	BfmeCfgXT *m_bfme04XT;
	Object *m_bfme08XT;
	unsigned char m_bfmeMidXT[0x14];
	void *m_bfme20XT;
};

void BfmeHostXT::bfmeRunXT()
{
	Object *obj = m_bfme08XT;

	m_bfme20XT = m_bfme04XT->m_bfme08XT;

	ModelConditionFlags flags;

	memset(flags.m_bfmeBitsXT, 0, 12);
	flags.m_bfmeBitsXT[1] |= 0x200000;

	obj->applyRva1C7370(flags, true);
	obj->clearCondition(0x16);

	BfmeSinkXT *sink = obj->m_bfme204XT;

	if (sink)
		sink->bfmeNoteXT(8);

	bfmeApplyXT(m_bfme08XT, 1);
}
