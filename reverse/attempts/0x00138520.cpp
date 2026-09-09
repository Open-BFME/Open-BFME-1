// ?newObject@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@ABV?$BitFlags@$0FG@@@I@Z
// partial score=0.97 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc

// ?newObject@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@ABV?$BitFlags@$0FG@@@I@Z
// Retail 0x00138520.  The BFME body uses the build-variation array at +0x2d0,
// creates through GameLogic, then runs each behavior's create interface before
// calling Object::initObject.  The retail string and thirteen named callers
// identify this as ThingFactory::newObject.
//
// Fixed vs the prior 0.95 stash: the #pragma comment(linker,"/alternatename:
// ...=?j_000168dd@@YAXXZ") on GameLogic::friend_createObject never took
// effect in this build (the call stayed an unresolved self-relative e8
// 00000000). Dropped it and pinned the mangled name directly in
// reverse/symbols.csv instead: the thunk j_000168dd forwards to FUN_007830c0
// = RVA 0x003830C0, which is ALREADY LANDED as the address-derived
// ?createRva003830C0@@YGPAXPAX000@Z (Code/GameEngine/Source/GameClient/
// Rva003830C0FourArgFactory.cpp, stdcall/4-void*, identity itself still
// unconfirmed) -- pin_consistency reports the address consistent, multiple
// names on one claimed address is expected. With that pin the call resolves
// and the body reaches the exact 278-byte size with ONLY 7 lines of
// register-choice residue left in the four-argument push sequence (extra/
// team/statusBits shuffled through ecx/edx/eax, "this" load interleaved
// between the first and second push) -- classified instruction/register
// encoding mismatch, the same argument-shuttle-register class as
// 0x0042D460. Tried: naming TheBfmeGameLogic in a local before the call
// (regressed to 277B with an extra reload, do not retry). Re-add the
// symbols.csv pin on ?friend_createObject@GameLogic@@QAEPAVObject@@
// PBVThingTemplate@@ABV?$BitFlags@$0FG@@@PAVTeam@@I@Z -> 0x003830C0 before
// touching the register residue on the next attempt.

typedef unsigned int UnsignedInt;

template <int N>
class BitFlags
{
public:
	UnsignedInt m_words[6];
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object;
class ThingTemplate;
class Team;
class GameLogic
{
public:
	Object *friend_createObject(const ThingTemplate *thing,
		const ObjectStatusMaskType &statusBits, Team *team, UnsignedInt extra);
};
class CRCParameterCheck;
class AsciiString
{
public:
	void *m_data;
};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x20];
	AsciiString m_name;
	unsigned char m_pad24[0x2ac];
	AsciiString *m_buildVariationsBegin;
	AsciiString *m_buildVariationsEnd;
};

class CreateModuleInterface
{
public:
	virtual void onCreate() = 0;
};

class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual CreateModuleInterface *getCreate() = 0;
};

class ObjectModule
{
public:
	virtual void objectModuleAnchor() = 0;

private:
	UnsignedInt m_data[2];
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class Object
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
	virtual void initObject() = 0;

	unsigned char m_pad04[0x70];
	UnsignedInt m_id;
	unsigned char m_pad78[0x178];
	BehaviorModule **m_behaviors;
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team,
		const ObjectStatusMaskType &statusBits, UnsignedInt extra);
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
extern void j_000168dd();
extern void j_0003a17a();
extern const char Rva006A16B0Empty[];
extern void *g_012ED4FC;

extern "C" __declspec(dllimport) void __stdcall Sleep(UnsignedInt milliseconds);
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	CRCParameterCheck *check, const char *format, ...);

#define BFME_NEW_OBJECT_DEBUG (*(unsigned char *)0x012EF1DC)
#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)

Object *ThingFactory::newObject(const ThingTemplate *tmplate, Team *team,
	const ObjectStatusMaskType &statusBits, UnsignedInt extra)
{
	if (tmplate == 0)
		return 0;

	if (BFME_NEW_OBJECT_DEBUG)
		Sleep(0);

	if (tmplate->m_buildVariationsBegin != tmplate->m_buildVariationsEnd)
	{
		UnsignedInt count = (UnsignedInt)(tmplate->m_buildVariationsEnd -
			tmplate->m_buildVariationsBegin);
		int which = GetGameLogicRandomValue(
			0, count - 1,
			"F:\\bfme\\Code\\gameengine\\Source\\Common\\Thing\\ThingFactory.cpp",
			0x184);
		AsciiString *variation = tmplate->m_buildVariationsBegin + which;
		ThingTemplate *replacement = findTemplate(*variation);
		if (replacement != 0)
			tmplate = replacement;
	}

	Object *obj = TheBfmeGameLogic->friend_createObject(
		tmplate, statusBits, team, extra);

	for (BehaviorModule **m = obj->m_behaviors; *m != 0; ++m)
	{
		if (BFME_NEW_OBJECT_DEBUG)
			Sleep(0);
		CreateModuleInterface *create = (*m)->getCreate();
		if (create != 0)
			create->onCreate();
	}

	if (BFME_NEW_OBJECT_DEBUG)
		Sleep(0);
	obj->initObject();

	if (BFME_NEW_OBJECT_DEBUG)
		Sleep(0);
	if (g_012ED4FC != 0)
	{
		UnsignedInt id = obj->m_id;
		char *name = (char *)tmplate->m_name.m_data;
		if (name != 0)
			name += 8;
		else
			name = (char *)Rva006A16B0Empty;
		((void (__cdecl *)(void *, const char *, ...))j_0003a17a)(
			g_012ED4FC, "newObj %s id %i", name, id);
	}

	return obj;
}
