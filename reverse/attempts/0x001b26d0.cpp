// ?apply@BfmeSub210_4B0@@QAEXMH@Z
// partial score=0.86 date=2026-09-10
typedef int Int;
typedef float Real;
typedef bool Bool;

class BfmeMgrF07
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void* vfn26(void *key);
};
extern BfmeMgrF07 *g_mgr12F076C;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

private:
	void *m_vtable;
	Overridable *m_nextOverride;

	friend class Thing;
};

class ThingTemplate : public Overridable
{
public:
	Bool isTrainable() const
	{
		return m_isTrainable;
	}

private:
	unsigned char m_unreconstructed_008[0x487 - 0x008];
	Bool m_isTrainable;

	friend class Thing;
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const;

protected:
	virtual ~Thing();

private:
	const ThingTemplate *m_template;
};

inline const ThingTemplate *Thing::getTemplate() const
{
	const ThingTemplate *thingTemplate = m_template;
	if (thingTemplate == 0)
		return 0;
	if (thingTemplate->m_nextOverride)
		thingTemplate = static_cast<const ThingTemplate *>(
			thingTemplate->m_nextOverride->getFinalOverride());
	return thingTemplate;
}

class BfmeSub210_4B0;

class Object : public Thing
{
public:
	unsigned char m_unreconstructed[0x210 - 0x008];
	BfmeSub210_4B0 *m_sub210;
};

class GameLogic
{
public:
	Object *findObjectByID(Int objectID);
};

extern GameLogic *TheBfmeGameLogic;

class ExperienceLevelSystem
{
public:
	Int unidentified_00380ee0(Object *object, Bool showFeedback);
};

extern ExperienceLevelSystem *TheExperienceLevelSystem;

class BfmeThingEFE
{
public:
	Real bfmeAt(Int baseCount);

private:
	void *m_vtable;
	void *m_owner;
	Real m_scalar;
	Int m_baseCount;
	void *m_values;

	friend class BfmeSub210_4B0;
};

#pragma comment(linker, "/alternatename:?unidentified_00380ee0@ExperienceLevelSystem@@QAEHPAVObject@@_N@Z=?j_00007dbf@@YAXXZ")

class BfmeSub210_4B0
{
public:
	void apply(Real val, Int flags);

private:
	Bool isTrainable() const;

	void *m_vtable;
	Object *m_parent;
	unsigned char m_unreconstructed_008[0x0c - 0x008];
	Real m_currentExperience;
	unsigned char m_unreconstructed_010[0x18 - 0x010];
	Int m_experienceSink;
	Real m_experienceScalar;
	Int m_unknown20;
	Bool m_unknown24;
	unsigned char m_padding25[3];
	Int m_scalarIndex;
	BfmeThingEFE *m_scalarTable;
};

struct BfmeObj4B0
{
	unsigned char pad[0x210];
	BfmeSub210_4B0 *m_sub210;
};

Bool BfmeSub210_4B0::isTrainable() const
{
	return m_parent->getTemplate()->isTrainable();
}

// ?apply@BfmeSub210_4B0@@QAEXMH@Z
// The existing ILT 0x000326F5 routes this named carrier to retail 0x001B26D0.
// Both named callers pass an Object+0x210 subobject and a float-widened value;
// the body follows the proven ExperienceLevelSystem/BfmeThingEFE update ABI.
void BfmeSub210_4B0::apply(Real value, Int flags)
{
	BfmeSub210_4B0 *tracker = this;
	if (tracker->m_experienceSink != 0)
	{
		GameLogic *gameLogic = TheBfmeGameLogic;
		do
		{
			Object *sink = gameLogic->findObjectByID(
				tracker->m_experienceSink);
			if (sink == 0)
				break;
			tracker = sink->m_sub210;
		}
		while (tracker->m_experienceSink != 0);
	}

	Object *parent = tracker->m_parent;
	const ThingTemplate *thingTemplate = parent->getTemplate();
	if (!thingTemplate->isTrainable())
		return;

	tracker->m_currentExperience = value;
	const Int level = TheExperienceLevelSystem->unidentified_00380ee0(
		parent, true);
	if ((Bool)flags && level != 0)
	{
		BfmeThingEFE *table = tracker->m_scalarTable;
		if (level != table->m_baseCount)
		{
			table->m_baseCount = level;
			table->m_scalar = table->bfmeAt(level);
		}
	}
}

void __stdcall bfmeApplyIntAsFloat4B0(void *key, int intArg)
{
	BfmeObj4B0 *obj = (BfmeObj4B0*)g_mgr12F076C->vfn26(key);
	if (obj && obj->m_sub210) {
		obj->m_sub210->apply((float)intArg, 1);
	}
}

void __cdecl bfmeStep1_250(void *arg);
void __cdecl bfmeStep2_250(void *arg);
extern "C" void __cdecl piPingCleanup(void *arg);
void __cdecl bfmeStep4_250(void *arg);

void __cdecl bfmeCallAll250(void *arg)
{
	bfmeStep1_250(arg);
	bfmeStep2_250(arg);
	piPingCleanup(arg);
	bfmeStep4_250(arg);
}

typedef void (__stdcall *ProcessValFn)(int val);
extern ProcessValFn g_processVal13596B8;

struct BfmeThingDA0
{
	unsigned char pad[0xb4c];
	int m_fieldB4C;
	int m_fieldB50;
	void step();
};

void BfmeThingDA0::step()
{
	if (m_fieldB50 <= 0 && m_fieldB4C != -1) {
		g_processVal13596B8(m_fieldB4C);
	}
	++m_fieldB50;
}

struct BfmeStr4BE
{
	char m_buf[1];
	void freeStr();
};

class BfmeFreeHelper
{
public:
	__declspec(dllimport) void doFree();
};

void BfmeStr4BE::freeStr()
{
	if (m_buf[0]) {
		((BfmeFreeHelper*)this)->doFree();
	}
}
