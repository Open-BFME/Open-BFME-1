// ?newObject@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@ABV?$BitFlags@$0FG@@@I@Z
// partial score=0.971223021583 date=2026-09-22
// ?newObject@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@ABV?$BitFlags@$0FG@@@I@Z
// cl: /DNDEBUG /MD /EHsc

// ?newObject@ThingFactory@@QAEPAVObject@@PBVThingTemplate@@PAVTeam@@ABV?$BitFlags@$0FG@@@I@Z
// Retail 0x00138520 is ThingFactory::newObject. The retail newObj string and
// thirteen named callers prove that identity.

// The body uses the build-variation array at +0x2d0 and the behavior array at
// +0x1f0 before it initializes and logs the new Object.
// The call through ILT 0x000168DD reaches GameLogic::friend_createObject at
// 0x003830C0. That callee now has a verified BFME identity and source body.
// Resumed with the analyst pack docs/analysis/0x001d88c0.md.
// The status mask is three DWORDs, as both hub calls independently witness.
// Native StringInline and a symbolic GameLogic global preserve the full body.
// Measured: 278 bytes; 8 masked byte differences, including a displaced DIR32.
// This is the same unresolved argument register schedule, not an instruction
// improvement over the old 12-byte residue with a literal global address.
// Compiler tuning and per-argument compiler barriers did not resolve it.

typedef unsigned int UnsignedInt;

template <int N>
class BitFlags
{
public:
	UnsignedInt m_words[3];
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
#include "../../reference/shims/stringinline/StringInline.h"

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
extern GameLogic *TheGameLogic;

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

	Object *obj = TheGameLogic->friend_createObject(
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
		const char *name = tmplate->m_name.str();
		((void (__cdecl *)(void *, const char *, ...))j_0003a17a)(
			g_012ED4FC, "newObj %s id %i", name, id);
	}

	return obj;
}
