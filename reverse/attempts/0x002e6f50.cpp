// ?ObjectSpy@@YAHPAUlua_State@@@Z
// partial score=0.85 date=2026-09-21
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct lua_State;

extern "C" const char *lua_tostring(lua_State *state, int index);

unsigned Rva00990030Lookup(lua_State *state, int index);
void __cdecl bfmeLogMsg574(const char *message);
void __cdecl bfmeNotify2_574(void *object, void *parameter);
void bfmeGoTGD(int state);
unsigned NAMEKEY(const char *name);

class Object;

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class NameKeyGenerator
{
public:
	unsigned nameToKey(const char *name);
};

class Gen_002E3AB0
{
public:
	int *bfmeFind(int key);
};

struct BfmeArgED8
{
};

class BfmeThingED8
{
public:
	void doProcess(BfmeArgED8 *state, unsigned nameKey, unsigned targetKey);
};

#pragma comment(linker, "/alternatename:?doProcess@BfmeThingED8@@QAEXPAUBfmeArgED8@@II@Z=?doProcess@BfmeThingED8@@QAEXPAUBfmeArgED8@@@Z")

struct Object
{
	unsigned char m_pad00[0x204];
	void *m_field204;
};

#define TheGameLogic (*(GameLogic **)0x012F0898)
#define TheNameKeyGenerator (*(NameKeyGenerator **)0x012ED600)
#define g_bfmeOwnerBR (*(Gen_002E3AB0 **)0x012F060C)

// ?ObjectSpy@@YAHPAUlua_State@@@Z
int ObjectSpy(lua_State *state)
{
	unsigned objectID = Rva00990030Lookup(state, 1);
	if (objectID == 0)
		goto invalid;

	Object *object;
	Object *objectSpill;
	object = TheGameLogic->findObjectByID(objectID);
	objectSpill = object;
	_ReadWriteBarrier();
	*(Object * volatile *)&objectSpill = object;
	_ReadWriteBarrier();
	if (object == 0)
		return 0;

	unsigned targetID = Rva00990030Lookup(state, 2);
	if (targetID == 0)
		goto invalid;

	{
		register Object *target = TheGameLogic->findObjectByID(targetID);
		if (target == 0)
			return 0;

		register unsigned nameKey = TheNameKeyGenerator->nameToKey(lua_tostring(state, 3));
		if (g_bfmeOwnerBR->bfmeFind(nameKey) == 0)
		{
			bfmeGoTGD(reinterpret_cast<int>(state));
			return 0;
		}

		register unsigned targetKey = NAMEKEY(lua_tostring(state, 4));
		if (g_bfmeOwnerBR->bfmeFind(targetKey) == 0)
		{
			bfmeGoTGD(reinterpret_cast<int>(state));
			return 0;
		}

		BfmeThingED8 *processor = reinterpret_cast<BfmeThingED8 *>(target->m_field204);
		if (processor != 0)
		{
			processor->doProcess(
				reinterpret_cast<BfmeArgED8 *>(state), targetKey, nameKey);
		}
	}

	return 0;

	invalid:
	bfmeLogMsg574(reinterpret_cast<const char *>(0x010CF6F0));
	bfmeNotify2_574(state, 0);
	return 0;
}
