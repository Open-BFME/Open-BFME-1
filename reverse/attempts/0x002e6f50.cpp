// ?ObjectSpy@@YAHPAUlua_State@@@Z
// partial score=0.98 date=2026-09-21
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ze
// ?ObjectSpy@@YAHPAUlua_State@@@Z, retail RVA 0x002E6F50.
// Identity: the Lua registration table at 0x002EC990 pairs this body with the
// "ObjectSpy" script-function name.

struct lua_State;

unsigned Rva00990030Lookup(lua_State *, int);
extern "C" const char *lua_tostring(lua_State *, int);

// matches reference/shims/namekeygenerator/Common/NameKeyGenerator.h exactly;
// NameKeyType must mangle as the enum (W4NameKeyType), not a plain unsigned,
// to match ?NAMEKEY@@YA?AW4NameKeyType@@PBD@Z (0x000B9810, functions.csv) and
// ?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z (0x0008FFC0)
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

NameKeyType NAMEKEY(const char *name);

void bfmeLogMsg574(const char *message);
// ?bfmeNotify2_574@@YAXPAX0@Z (reverse/symbols.csv pin @0x0000630C): both args
// are void*, not lua_State* -- lua_State* mangles differently and does not resolve.
void bfmeNotify2_574(void *state, void *parameter);
// ?bfmeGoTGD@@YAXH@Z (reverse/functions.csv, 0x002E55A0): takes an int, not a
// lua_State* -- the lua_State* spelling does not match the landed body's name.
void bfmeGoTGD(int state);

struct BfmeArgED8
{
	unsigned char pad[0x74];
	void *val74;
};

// 0x0026ED80 is a 22-byte thiscall stub that rewrites its FIRST stack argument
// (arg->val74), adds 0x204 to ecx and tail-jmps through ILT 0x000283F8 to
// 0x002E2110, whose epilogue is `ret 0xc`: three stack arguments, of which the
// stub passes slots 2 and 3 through untouched.  Its ledger row in
// Code/GameEngine/Source/Common/BfmeConv818.cpp still spells it with one
// argument, which is the ABI defect this body's last relocation trips over.
struct BfmeThingED8
{
	void doProcess(BfmeArgED8 *arg, NameKeyType key1, NameKeyType key2);
};

class Object
{
	unsigned char m_prefix[0x204];

public:
	BfmeThingED8 *m_module204;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

// reverse/symbols.csv names RVA 0x00EF060C (VA 0x012F060C) TheLuaScriptEngine:
// GameEngine::init at 0x00079F36 pushes it into initSubsystem<LuaScriptEngine>.
class LuaScriptEngine;

extern LuaScriptEngine *TheLuaScriptEngine;

struct BfmeCallJ63
{
	void *invoke(void *event);
};

struct Gen_002E3AB0
{
	int *bfmeFind(int key);
};

int ObjectSpy(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup(state, 1);
	if (objectID == 0)
		goto debugMode;

	{
		Object *object = TheGameLogic->findObjectByID(objectID);
		if (object == 0)
			return 0;

		unsigned targetID = Rva00990030Lookup(state, 2);
		if (targetID == 0)
			goto debugMode;

		Object *target = TheGameLogic->findObjectByID(targetID);
		if (target == 0)
			return 0;

		const char *eventName = lua_tostring(state, 3);
		NameKeyType eventKey = TheNameKeyGenerator->nameToKey(eventName);
		if (reinterpret_cast<BfmeCallJ63 *>(TheLuaScriptEngine)->invoke(
				(void *)eventKey) == 0)
		{
			bfmeGoTGD(reinterpret_cast<int>(state));
			return 0;
		}

		const char *spyName = lua_tostring(state, 4);
		NameKeyType spyKey = NAMEKEY(spyName);
		if (reinterpret_cast<Gen_002E3AB0 *>(TheLuaScriptEngine)->bfmeFind(spyKey) == 0)
		{
			bfmeGoTGD(reinterpret_cast<int>(state));
			return 0;
		}

		if (target->m_module204 != 0)
		{
			target->m_module204->doProcess(
				reinterpret_cast<BfmeArgED8 *>(object), eventKey, spyKey);
		}

		return 0;
	}

debugMode:
	bfmeLogMsg574(
		"\nEntering LUA debug mode.  Type ? for help, 'cont' to exit debug mode\n");
	bfmeNotify2_574(state, 0);
	return 0;
}
