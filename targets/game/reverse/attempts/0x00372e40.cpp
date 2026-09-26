// ?Rva00372E40@@YAHPAXHHH@Z
// partial score=0.48 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00372E40, 280B. Identity: not a matched caller, but the string
// literal at the nameToKey call site reads "CastleMemberBehavior" (retail
// .rdata 0x01090D8C), and one callee is pinned to CastleBehavior::
// isPendingObjectUnavailable (0x00372090), matching the same
// local-static-key module lookup idiom already landed in
// CastleMemberBehaviorFind.cpp. Address-derived name kept per naming rules
// since no caller/vtable/name-key proves the enclosing function's own
// identity.

typedef int Bool;

// -- pinned wrapper stubs; each class/method reproduces one retail REL32 pin --

class BfmeX1011;
class BfmeLook1011
{
public:
	BfmeX1011 *bfmeFind1011(int id);
};
extern BfmeLook1011 *TheBfmeGameLogic;

class BfmeSubBIA
{
public:
	int ask();
};

class BfmeQ1060
{
public:
	int bfmeConv1060(int name);
};
extern BfmeQ1060 *TheNameKeyGenerator;

class BfmeItemDJ;
class BfmeThingDJ
{
public:
	BfmeItemDJ *bfmeFindDJ(int key);
};

class BfmeItemE63
{
public:
	Bool checkValid();
};

class BfmeY982
{
public:
	BfmeY982 *bfmeConv982B();
};

class BfmeR1094;
class BfmeK1094
{
public:
	BfmeR1094 *bfmeCur1094();
};

// -- real-layout views of the same retail objects, for field access / vcalls --

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xd0];
	unsigned int m_kindOf0xd8;
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x30];
};

class ProjectileUpdateInterfaceView
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual Bool queryStatus();
};

class FireShimBase
{
public:
	int fireAt(Object *object, int cArg, void *posAddr, int zero,
		void *player, int flag);
};
typedef int (FireShimBase::*FireMember)(Object *, int, void *, int, void *,
	int);

// ?d_00372e40@@YAXXZ
int Rva00372E40(void *unused, int id, int cArg, int flag)
{
	BfmeLook1011 *gameLogic = TheBfmeGameLogic;
	Object *object = (Object *)gameLogic->bfmeFind1011(id);
	if (!object)
		return 0;

	ThingTemplate *tmpl = object->m_template;
	const ThingTemplate *finalTemplate = tmpl;
	if (tmpl)
	{
		if (tmpl->m_nextOverride)
			finalTemplate = (const ThingTemplate *)
				((BfmeSubBIA *)tmpl->m_nextOverride)->ask();
		else
			finalTemplate = tmpl;
	}
	if (finalTemplate->m_kindOf0xd8 & 0x00200000)
		return 0;

	static int key = TheNameKeyGenerator->bfmeConv1060(
		(int)"CastleMemberBehavior");
	BfmeItemDJ *module = ((BfmeThingDJ *)object)->bfmeFindDJ(key);

	if (!flag)
	{
		if (module)
		{
			if (*(int *)((char *)module + 0x14))
			{
				if (((BfmeItemE63 *)module)->checkValid())
					return 0;
			}
		}
	}

	ProjectileUpdateInterfaceView *interface =
		(ProjectileUpdateInterfaceView *)((BfmeY982 *)object)->bfmeConv982B();
	if (!interface)
		return 0;
	if (interface->queryStatus())
		return 0;

	union { void *addr; FireMember member; } fireCast;
	fireCast.addr = *((void **)*(void **)interface + 4);
	BfmeR1094 *player = ((BfmeK1094 *)object)->bfmeCur1094();
	return (((FireShimBase *)interface)->*fireCast.member)(object, cArg,
		(char *)object + 0x38, 0, player, flag);
}
