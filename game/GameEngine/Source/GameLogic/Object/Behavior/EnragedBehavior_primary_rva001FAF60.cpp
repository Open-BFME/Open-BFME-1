// cl: /DNDEBUG /MD /EHsc
// Retail body [0x001FAF60, 0x001FAFC6), 102 bytes.
//
// Object::1C1EA0 reaches this arm through ILT 0x0001F960 after finding the
// module keyed by the verified "EnragedBehavior" literal.  The matched
// EnragedBehavior constructor establishes the same module layout used here:
// Object at +0x08 and the module state word at +0x20.  The neighbouring exact
// 0x001FAEE0 body uses that layout and the same condition/sink/wake ABI.
//
// The method name is deliberately RVA-scoped.  No public spelling or virtual
// slot meaning is asserted by this source.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class ModelConditionFlags
{
public:
	unsigned int m_bfmeBitsXT[3];
};

class BfmeSinkXT
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void slot73() = 0;
	virtual void slot74() = 0;
	virtual void slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void slot78() = 0;
	virtual void slot79() = 0;
	virtual void slot80() = 0;
	virtual void slot81() = 0;
	virtual void slot82() = 0;
	virtual void slot83() = 0;
	virtual void slot84() = 0;
	virtual void slot85() = 0;
	virtual void slot86() = 0;
	virtual void slot87() = 0;
	virtual void slot88() = 0;
	virtual void slot89() = 0;
	virtual void slot90() = 0;
	virtual void slot91() = 0;
	virtual void slot92() = 0;
	virtual void slot93() = 0;
	virtual void slot94() = 0;
	virtual void slot95() = 0;
	virtual void slot96() = 0;
	virtual void slot97() = 0;
	virtual void slot98() = 0;
	virtual void slot99() = 0;
	virtual void slot100() = 0;
	virtual void slot101() = 0;
	virtual void slot102() = 0;
	virtual void slot103() = 0;
	virtual void slot104() = 0;
	virtual void slot105() = 0;
	virtual void slot106() = 0;
	virtual void slot107() = 0;
	virtual void slot108() = 0;
	virtual void slot109() = 0;
	virtual void slot110() = 0;
	virtual void slot111() = 0;
	virtual void slot112() = 0;
	virtual void slot113() = 0;
	virtual void slot114() = 0;
	virtual void slot115() = 0;
	virtual void slot116() = 0;
	virtual void slot117() = 0;
	virtual void slot118() = 0;
	virtual void slot119() = 0;
	virtual void slot120() = 0;
	virtual void slot121() = 0;
	virtual void slot122() = 0;
	virtual void slot123() = 0;
	virtual void slot124() = 0;
	virtual void slot125() = 0;
	virtual void slot126() = 0;
	virtual void slot127(int) = 0;
};

class Object
{
public:
	void applyRva1C7370(const ModelConditionFlags &flags, bool on);

	unsigned char m_bfmeHeadXT[0x204];
	BfmeSinkXT *m_bfme204XT;
};

// Existing caller-proven ABI view for the Object arm at ILT 0x000122AB.
// Its public spelling is not asserted here.
class BfmeObjE10
{
public:
	void actionB(int value);
};

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();

protected:
	void *m_moduleData;
	Object *m_object;
};

class EnragedBehaviorIface1 { public: virtual void slot(); };
class EnragedBehaviorIface2 { public: virtual void slot(); };

class UpdateModule : public PB_DeepBase, public EnragedBehaviorIface1,
	public EnragedBehaviorIface2
{
public:

	void setWakeFrame(Object *object, unsigned int whenToWakeUp);

protected:
	Object *getObject() const { return m_object; }

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class EnragedBehavior : public UpdateModule
{
public:
	void rva001FAF60();

private:
	volatile unsigned int m_f20;
};

// ?rva001FAF60@EnragedBehavior@@QAEXXZ
void EnragedBehavior::rva001FAF60()
{
	Object *object = getObject();
	m_f20 = 0;
	ModelConditionFlags flags;

	memset(flags.m_bfmeBitsXT, 0, 12);
	flags.m_bfmeBitsXT[1] |= 0x200000;

	object->applyRva1C7370(flags, false);
	((BfmeObjE10 *)object)->actionB(0x16);

	BfmeSinkXT *sink = object->m_bfme204XT;
	if (sink)
		sink->slot127(0);

	setWakeFrame(getObject(), 0x3fffffff);
}
