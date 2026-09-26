// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ze
// The Lua registration table at 0x002EC990 pairs this callback with ObjectSpy.

struct lua_State;

unsigned Rva00990030Lookup(lua_State *, int);
extern "C" const char *lua_tostring(lua_State *, int);

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

NameKeyType NAMEKEY(const char *name);

void bfmeLogMsg574(const char *message);
void bfmeNotify2_574(void *state, void *parameter);
void bfmeGoTGD(int state);

struct BfmeArgED8
{
	unsigned char pad[0x74];
	void *val74;
};

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
