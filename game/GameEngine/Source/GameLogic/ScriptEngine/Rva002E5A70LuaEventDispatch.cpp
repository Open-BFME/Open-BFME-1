// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Retail 0x002E5A70: Lua event callback reached from Rva002E0E30RecordDispatch
// through ILT 0x000122A6. Owner and method identity are unproven: address-derived names.
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Object;
struct lua_State;
struct BfmeQ1039;
struct Rva002E32A0IdOwner;

extern "C" int lua_gettop(lua_State *state);
extern "C" void lua_getglobal(lua_State *state, const char *name);
extern "C" int lua_type(lua_State *state, int index);
extern "C" void lua_call(lua_State *state, int arguments, int results);
extern "C" void lua_settop(lua_State *state, int index);

extern void *g_activeObj12F0610;
extern void bfmeGo1039E(BfmeQ1039 *q, int value);
extern void bfmePrintTGD(const char *message);

class SortedStrings2E1F80
{
public:
    const AsciiString &find(int key, bool *flag);
};

class Rva002E42C0Owner
{
public:
    void rva002E42C0(lua_State *state,
        const Rva002E32A0IdOwner *owner);
};

class GameLogic
{
public:
    Object *findObjectByID(int id);
};

extern GameLogic *TheBfmeGameLogic;

class Rva002E5A70Call
{
public:
    void dispatch(void *recordData, Object *object, void *argument2,
        void *argument3);
};

// Arguments are 24-byte records: float at +8, bool at +0xc, object id at
// +0x10, kind tag at +0x18 (1 float, 2 bool, 3 object id, else end).
void Rva002E5A70Call::dispatch(void *recordData, Object *object,
    void *argument2, void *argument3)
{
    if (*(int *)((char *)this + 0xb0) > 10)
        return;

    int top = lua_gettop(*(lua_State **)((char *)this + 8));
    g_activeObj12F0610 = 0;

    char *objectBytes = (char *)object;
    void *eventSource = *(void **)(objectBytes + 0x204);
    if (eventSource == 0 || (objectBytes[0x344] & 1) != 0)
        return;

    void *eventOwner = *(void **)((char *)eventSource + 0x200);
    if (eventOwner == 0)
        return;

    bool hasEventName;
    const AsciiString &name =
        reinterpret_cast<SortedStrings2E1F80 *>(eventOwner)->find(
            (int)recordData, &hasEventName);
    AsciiString eventName(name);
    char *eventData = *(char **)&eventName;
    if (eventData == 0 || *(unsigned short *)(eventData + 4) == 0)
        return;

    lua_getglobal(*(lua_State **)((char *)this + 8), eventData + 8);
    if (lua_type(*(lua_State **)((char *)this + 8), 1) != 5)
    {
        AsciiString error;
        if (lua_type(*(lua_State **)((char *)this + 8), 1) == 1)
            error = " is not defined.";
        else
            error = " is not a lua function.";
        return;
    }

    ((Rva002E42C0Owner *)this)->rva002E42C0(
        *(lua_State **)((char *)this + 8),
        (const Rva002E32A0IdOwner *)object);
    ((Rva002E42C0Owner *)this)->rva002E42C0(
        *(lua_State **)((char *)this + 8),
        (const Rva002E32A0IdOwner *)argument2);

    char *argumentBytes = (char *)argument3;
    int argumentCount = 2;
    for (int i = 0; i < 3; ++i)
    {
        char *argument = argumentBytes + i * 24;
        switch (*(int *)(argument + 24))
        {
        case 1:
            bfmeGo1039E((BfmeQ1039 *)*(lua_State **)((char *)this + 8),
                (int)*(float *)(argument + 8));
            ++argumentCount;
            break;
        case 2:
        {
            bool flag = *(bool *)(argument + 12);
            bfmeGo1039E((BfmeQ1039 *)*(lua_State **)((char *)this + 8),
                flag != 0);
            ++argumentCount;
            break;
        }
        case 3:
        {
            int objectID = *(int *)(argument + 16);
            Object *resolved = TheBfmeGameLogic->findObjectByID(objectID);
            ((Rva002E42C0Owner *)this)->rva002E42C0(
                *(lua_State **)((char *)this + 8),
                (const Rva002E32A0IdOwner *)resolved);
            ++argumentCount;
            break;
        }
        default:
            i = 3;
            break;
        }
    }

    if (hasEventName)
        g_activeObj12F0610 = *(lua_State **)((char *)this + 8);
    ++*(int *)((char *)this + 0xb0);
    lua_call(*(lua_State **)((char *)this + 8), argumentCount, 0);
    lua_settop(*(lua_State **)((char *)this + 8), top);
    --*(int *)((char *)this + 0xb0);

    if (g_activeObj12F0610 != 0 &&
        *(int *)((char *)this + 0xb0) == 0)
    {
        bfmePrintTGD("Stepping out of LUA function - step disabled.\n");
        g_activeObj12F0610 = 0;
    }
}
