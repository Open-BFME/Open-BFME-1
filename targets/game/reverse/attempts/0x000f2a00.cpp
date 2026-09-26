// ?d_000f2a00@@YAXXZ
// partial score=0.3 date=2026-09-24
// ?rva000F2A00@Rva000F2A00Team@@QAEPAXPAVThingTemplate@@PBUCoord3D@@M@Z
// This source keeps the address in its owner and method names because callers
// prove the Team receiver but do not prove the method name.
// Retail reads the module count from ThingTemplate+0x294 and divides its byte
// span by 0x14. Inline size() and begin() accessors reproduce those reads.

typedef int Int;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct AsciiString
{
	void *m_data;
};

class Object;
class ObjectView;
class ThingTemplate;

struct ModuleNugget
{
	AsciiString m_name;
	AsciiString m_tag;
	const void *m_data;
	Int m_interfaceMask;
	Bool m_copiedFromDefault;
	Bool m_inheritable;
	Bool m_overrideable;
};

struct ModuleInfoView
{
	ModuleNugget *m_begin;
	ModuleNugget *m_end;
	ModuleNugget *m_capacity;

	ModuleNugget *begin() const { return m_begin; }
	Int size() const { return (Int)(m_end - m_begin); }
};

class ModuleDataView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void *getRecruitmentOwner() const = 0;
};

class RecruitmentOwnerView
{
public:
	ModuleNugget *begin() const
	{
		return *(ModuleNugget **)((const char *)this + 0x23c);
	}

	ModuleNugget *end() const
	{
		return *(ModuleNugget **)((const char *)this + 0x240);
	}
};

class ThingFactoryView
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

class GameLogicView
{
public:
	Object *firstObject();
};

class TeamView
{
public:
	TeamView *getDefaultTeam();
};

class Rva000F2A00Team
{
public:
	void *rva000F2A00(ThingTemplate *templateToFind,
		const Coord3D *home, Real maxDist);
};

class ObjectView
{
public:
	ObjectView *nextObject() const
	{
		return *(ObjectView **)((const char *)this + 0x88);
	}

	Bool disabled() const
	{
		return (**(const unsigned char **)((const char *)this + 0x90) & 1) != 0;
	}
};

extern ThingFactoryView *TheThingFactory;
extern GameLogicView *TheBfmeGameLogic;
extern "C" void j_0000103c();
extern "C" void j_000358be();

static __forceinline ThingTemplate *findTemplate(const AsciiString &name)
{
	return TheThingFactory->findTemplate(name);
}

static __forceinline ObjectView *firstObject(GameLogicView *logic)
{
	typedef ObjectView *(GameLogicView::*Call)();
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_000358be;
	return (logic->*call.member)();
}

static __forceinline Bool candidatePasses(TeamView *team, ObjectView **best, Real *bestDist,
	ObjectView *candidate, ThingTemplate *templateToFind, const Coord3D *home)
{
	typedef Bool (TeamView::*Call)(ObjectView **, Real *, ObjectView *,
		ThingTemplate *, const Coord3D *);
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_0000103c;
	return (team->*call.member)(best, bestDist, candidate, templateToFind, home);
}

static __forceinline Bool hasTemplateVariation(const ThingTemplate *templateToFind)
{
	const char *base = (const char *)templateToFind;
	const ModuleInfoView *info = (const ModuleInfoView *)(base + 0x294);
	if (info->size() > 0)
	{
		Int index = 0;
		Int offset = 0;
		do
		{
			ModuleNugget *it = (ModuleNugget *)((char *)info->begin() + offset);
			const ModuleDataView *data = (const ModuleDataView *)it->m_data;
			if (data != 0)
			{
				const RecruitmentOwnerView *owner =
					(const RecruitmentOwnerView *)data->getRecruitmentOwner();
				if (owner != 0)
				{
					ModuleNugget *names = owner->begin();
					ModuleNugget *namesEnd = owner->end();
					if (names != 0 && namesEnd - names > 1)
					{
						if (findTemplate(*(const AsciiString *)names) != 0 &&
							findTemplate(*(const AsciiString *)(names + 1)) != 0)
							return true;
					}
				}
			}
			++index;
			offset += sizeof(ModuleNugget);
		} while (index < info->size());
	}
	return false;
}

// ?rva000F2A00@Rva000F2A00Team@@QAEPAXPAVThingTemplate@@PBUCoord3D@@M@Z
void *Rva000F2A00Team::rva000F2A00(ThingTemplate *templateToFind,
	const Coord3D *home, Real maxDist)
{
	Real bestDist = maxDist * maxDist;
	ObjectView *best = 0;
	Bool variation = hasTemplateVariation(templateToFind);
	for (ObjectView *candidate = firstObject(TheBfmeGameLogic);
		candidate != 0; candidate = candidate->nextObject())
	{
		if (candidate->disabled())
			continue;
		if (candidatePasses((TeamView *)this, &best, &bestDist,
			candidate, templateToFind, home))
			continue;
		if (!variation)
			continue;
		if (candidatePasses((TeamView *)this, &best, &bestDist,
			candidate, templateToFind, home))
			continue;
		candidatePasses((TeamView *)this, &best, &bestDist,
			candidate, templateToFind, home);
	}
	return best;
}
