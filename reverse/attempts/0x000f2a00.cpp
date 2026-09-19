// ?recruit@Rva000F2A00Team@@QAEPAXPAVThingTemplate@@PBUCoord3D@@M@Z
// partial score=0.25 date=2026-09-19
// Retail 0x000F2A00 candidate, retained for the boundary and ABI experiment.
// The BFME extension scans behavior-module template names before recruiting.

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
	ObjectView *recruit(ThingTemplate *templateToFind,
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

static ThingTemplate *findTemplate(const AsciiString &name)
{
	return TheThingFactory->findTemplate(name);
}

static ObjectView *firstObject(GameLogicView *logic)
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

static Bool candidatePasses(TeamView *team, ObjectView **best, Real *bestDist,
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

static Bool hasTemplateVariation(const ThingTemplate *templateToFind)
{
	const char *base = (const char *)templateToFind;
	const ModuleInfoView *info = (const ModuleInfoView *)(base + 0x294);
	ModuleNugget *it = info->m_begin;
	ModuleNugget *end = info->m_end;
	for (Int index = 0; it != end; ++index, ++it)
	{
		const ModuleDataView *data =
			(const ModuleDataView *)it->m_data;
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
	}
	return false;
}

// ?recruit@Rva000F2A00Team@@QAEPAXPAVThingTemplate@@PBUCoord3D@@M@Z
ObjectView *Rva000F2A00Team::recruit(ThingTemplate *templateToFind,
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
