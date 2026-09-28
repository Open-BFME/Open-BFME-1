// ?finishSpecialPower@SpecialPowerModule@@QAEXI@Z
// partial score=0.98 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
// stlport
//
// BANKED, NOT BYTE-EXACT (opus-5.5 2026-09-28): 1073 compiled bytes = retail
// 1073, 23 differing non-relocation bytes, shape 0.997, 2 structural diffs.
// Identity: the pinned ILT ?finishSpecialPower@SpecialPowerModule@@QAEXI@Z
// (0x000251AD -> 0x00269C50) is what the matched doSpecialPower* callers call;
// the body is the BFME expansion of ZH SpecialPowerModule::triggerSpecialPower
// (aboutToDoSpecialPower, createViewObject, recharge, ...), and the
// Rva0026A190 -0x10 adjustor tail enters it from the interface.
// Remaining residue is pure register choice in three spots:
//  +0xc7   TheGameLogic loaded into ecx (retail) vs edx (ours);
//  +0x181  configure() args: retail value/player in edx, name in ecx and the
//          player push after the store load; ours swaps ecx/edx and pushes
//          player before loading the store;
//  +0x1ea  Coord3D copies: retail eax/edx, ours edx/eax.
// Tried without effect: inline getFrame(), a frame local, delta+frame order,
// Coord3D::set(), eh_levers+shape_search (21 trials), flag_sweep (90 variants).
// Levers that got here from the 0.13 bank: real filter classes (pinned global
// vtables) declared rj/relationship/alive/object in unwind order; ZH
// inline-recursive const+non-const friend_getFinalOverride; __real literals
// 5.0f and 0.0f (retail 0x01075344/0x01075350 are compiler float constants);
// ZH-style static FXList::doFXPos/doFXObj helpers; the reference store read
// per branch; hasValue as an if; the filter/result tail in its own block so
// the result takes the dead location parameter slot and the frame is 0x4c.
// Landing needs two pins (not added yet, evidence below):
//  ?aboutToDoSpecialPower@SpecialPowerModule@@IAEXPBUCoord3D@@@Z at ILT
//    0x00046C13 (body 0x00268CB0, ledger-misnamed as a module-data dtor): ZH
//    call order plus its TheScriptEngine notify with the controlling player's
//    index at +0x24;
//  an address-derived name for ILT 0x0001F505 -> dump 0x00269780 (thiscall,
//    one BfmeWideResult* argument, ret 4).

#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#include <vector>
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Player;
class Matrix3D;
class AsciiString;

enum DisabledType
{
	DISABLED_HELD = 3
};

enum KindOfType
{
	KINDOF_0x6C = 0x6c
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object)
		: m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_obj(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

class Rva00265150RJFilter : public PartitionFilter
{
public:
	Rva00265150RJFilter(void *subobject, void *extra, Bool match)
		: m_subobject(subobject), m_extra(extra), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	void *m_subobject;
	void *m_extra;
	Bool m_match;
};

struct BfmeWideResultItem
{
	Object *m_object;
	UnsignedInt m_distance;
};

struct BfmeWideResultPayload
{
	std::vector<BfmeWideResultItem> m_items;
	BfmeWideResultItem *m_cursor;
	Int m_refCount;
};

struct Rva009F3C70Result
{
	BfmeWideResultPayload *m_value;
	void append(Int, Int);
};

struct BfmeWideResult : public Rva009F3C70Result
{
	~BfmeWideResult()
	{
		BfmeWideResultPayload *&payload = m_value;
		--payload->m_refCount;
		if (payload->m_refCount == 0)
			delete payload;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int, Int, Int, Int, Int);
};

class PartitionManager : public BfmeWideForwardC
{
};

extern PartitionManager *ThePartitionManager;

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *getFinalOverride();
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled[0xd4 - 8];
	UnsignedInt m_fieldD4;
};

class SpecialPowerTemplate : public Overridable
{
public:
	const SpecialPowerTemplate *getFO() const
	{
		return (const SpecialPowerTemplate *)friend_getFinalOverride();
	}

	unsigned char m_unmodelled[0x20 - 8];
	Int m_field20;
};

class FXList
{
public:
	Bool isEmpty() const;
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx = 0,
		Real primarySpeed = 0.0f, const Coord3D *secondary = 0) const;
	void doFXObj(const Object *primary, const Object *secondary = 0) const;

	static void doFXPos(const FXList *fx, const Coord3D *primary)
	{
		if (fx && !fx->isEmpty())
			fx->doFXPos(primary);
	}
	static void doFXObj(const FXList *fx, const Object *primary)
	{
		if (fx && !fx->isEmpty())
			fx->doFXObj(primary);
	}
};

class Rva000C98C0
{
public:
	void subtract(Int);
};

class BfmeItemRY
{
public:
	void bfmeDoRY(void *, void *);
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class Rva001BFE20Interface : public BfmeVirtualSlots<60>
{
public:
	virtual void collectObjects(std::list<Object *> *out) = 0;
};

class Thing
{
public:
	virtual ~Thing();
	Bool isKindOf(KindOfType kind) const;

protected:
	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	void setDisabledUntil(DisabledType type, UnsignedInt frame);
	void *unidentified_001BFE20() const;
	ThingTemplate *getTemplate() const
	{
		ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = (ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}
	const Coord3D *getPosition() const
	{
		return (const Coord3D *)((const unsigned char *)this + 0x38);
	}

};

class GameLogic
{
public:
	unsigned char m_unmodelled[0x3c];
	UnsignedInt m_frame;
	UnsignedInt getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

class BfmeObjectReferenceStore
{
public:
	void clearObjectEntries();
	void configure(Int kind, const Int &key, const Object *owner,
		const AsciiString &name, Int value);
};

class BfmeModeGF;
extern BfmeModeGF *g_bfmeModeGF;
inline BfmeObjectReferenceStore *TheBfmeObjectReferenceStore()
{
	return (BfmeObjectReferenceStore *)g_bfmeModeGF;
}


struct SpecialPowerModuleData
{
	unsigned char m_unmodelled00[8];
	SpecialPowerTemplate *m_specialPowerTemplate;
	Bool m_updateModuleStartsAttack;
	unsigned char m_unmodelled0d[0x1d0 - 0x0d];
	unsigned char m_name1d0[4];
	Int m_range1d4;
	Bool m_field1d8;
	unsigned char m_pad1d9[3];
	Int m_key1dc;
	unsigned char m_pad1e0[4];
	Bool m_field1e4;
	unsigned char m_pad1e5[3];
	Int m_value1e8;
	Bool m_field1ec;
	Bool m_field1ed;
	Bool m_field1ee;
	unsigned char m_pad1ef[0x1f4 - 0x1ef];
	const FXList *m_fx;
	unsigned char m_pad1f8[4];
	Int m_frames1fc;
	Real m_scale200;
	unsigned char m_pad204[4];
	Bool m_field208;
	unsigned char m_pad209;
	Bool m_field20a;
	Bool m_field20b;
};

class BehaviorModuleBase
{
public:
	virtual ~BehaviorModuleBase();

protected:
	const SpecialPowerModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled0c[4];
};

class SpecialPowerModuleInterface : public BfmeVirtualSlots<16>
{
public:
	virtual void startPowerRecharge() = 0;
};

class SpecialPowerModule : public BehaviorModuleBase, public SpecialPowerModuleInterface
{
public:
	void finishSpecialPower(UnsignedInt arg);

protected:
	void aboutToDoSpecialPower(const Coord3D *location);
	void createViewObject(const Coord3D *location);
	void rva00269780(BfmeWideResult *result);

	Object *getObject() const { return m_object; }
	const SpecialPowerModuleData *getSpecialPowerModuleData() const { return m_moduleData; }
};

void SpecialPowerModule::finishSpecialPower(UnsignedInt arg)
{
	const Coord3D *location = (const Coord3D *)arg;
	aboutToDoSpecialPower(location);
	createViewObject(location);

	if (!getSpecialPowerModuleData()->m_updateModuleStartsAttack)
		startPowerRecharge();

	Player *player = getObject()->getControllingPlayer();
	if (player)
	{
		SpecialPowerTemplate *spTemplate = getSpecialPowerModuleData()->m_specialPowerTemplate;
		((Rva000C98C0 *)player)->subtract(spTemplate->getFO()->m_field20);
	}

	const SpecialPowerModuleData *data = getSpecialPowerModuleData();
	Int frames = data->m_frames1fc;
	if (frames != -1 && data->m_scale200 > 0.0f)
	{
		Int delta = (Int)(data->m_scale200 * 5.0f);
		((BfmeItemRY *)getObject())->bfmeDoRY((void *)frames, (void *)delta);
		if (data->m_field208)
			getObject()->setDisabledUntil(DISABLED_HELD, TheGameLogic->m_frame + delta);
	}

	const FXList *fx = data->m_fx;
	if (fx)
	{
		if (location)
			FXList::doFXPos(fx, location);
		else
			FXList::doFXObj(fx, getObject());
	}

	if (data->m_field1e4)
	{
		if (data->m_field1ee)
		{
			TheBfmeObjectReferenceStore()->clearObjectEntries();
			return;
		}
		Int kind = 1;
		if (data->m_field20b)
			kind = 2;
		else if (data->m_field20a)
			kind = 3;
		TheBfmeObjectReferenceStore()->configure(kind, data->m_key1dc, (const Object *)player,
			*(const AsciiString *)data->m_name1d0, data->m_value1e8);
		return;
	}

	Bool hasValue = false;
	if (data->m_value1e8)
		hasValue = true;
	const Int *name = *(const Int *const *)data->m_name1d0;
	if ((name == 0 || *(const unsigned short *)((const char *)name + 4) == 0) && !hasValue)
		return;

	Object *object = getObject();
	Coord3D pos;
	if (location)
		pos = *location;
	else
		pos = *object->getPosition();

	Int relationship = 4;
	if (data->m_field1ec)
		relationship = 1;
	if (data->m_field1ed)
		relationship = 7;
	else if (data->m_field1ee)
		relationship = 5;
	else if (hasValue)
		relationship = (relationship != 1) ? 1 : 4;

	Rva00265150RJFilter rjFilter((void *)&data->m_key1dc,
		object->getControllingPlayer(), true);
	PartitionFilterRelationship filterTeam(object, relationship, false);
	Rva0025ED50RootFilter aliveFilter;
	Rva0025ED50ObjectFilter objectFilter(object);
	rjFilter.link(filterTeam.link(&aliveFilter));
	if (!(object->getTemplate()->m_fieldD4 & 0x4000000))
		rjFilter.link(&objectFilter);

	{
	BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
		(Int)&pos, data->m_range1d4, 0, (Int)&rjFilter, 1);
	if (data->m_field1d8)
	{
		if (object->isKindOf(KINDOF_0x6C))
		{
			Rva001BFE20Interface *extra =
				(Rva001BFE20Interface *)object->unidentified_001BFE20();
			if (extra)
			{
				std::list<Object *> objects;
				extra->collectObjects(&objects);
				for (std::list<Object *>::iterator it = objects.begin();
					it != objects.end(); ++it)
				{
					if (*it)
						result.append((Int)*it, 0);
				}
			}
		}
		else
			result.append((Int)object, 0);
	}
	rva00269780(&result);
	}
}
