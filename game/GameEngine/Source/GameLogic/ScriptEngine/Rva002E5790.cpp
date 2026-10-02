// stlport
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB 
// Retail 0x002E5790: three-argument object event dispatcher reached through ILT
// 0x0003D4E7 by matched callers. Owner identity remains address-derived.
// Offset-tail ABI at 0x0026EDD0 is independently proven by its ret-12 callee.
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../Common/Thing/GameLogicObjectLookup.h"

class Object;
struct lua_State;
struct BfmeQ1039;
struct Rva002E32A0IdOwner;

extern "C" void lua_pushnumber(lua_State *, double);
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

extern GameLogic *TheBfmeGameLogic;

class Rva0026EDD0
{ public: void invoke(int, void *, void *); };

class Rva002E5790Call
{
public:
    void dispatch(void **recordSlot, Object *object, void *argument3);
    char pad_00[8];
    lua_State *field_08;
    char pad_0C[0xA4];
    int field_B0;
    char pad_B4[4];
    void *field_B8;
};

// Arguments are 24-byte records: float at +8, bool at +0xc, object id at
// +0x10, kind tag at +0x18 (1 float, 2 bool, 3 object id, else end).
void Rva002E5790Call::dispatch(void **recordSlot, Object *object,
    void *argument3)
{
    if (field_08 == 0) return;
    if (field_B0 > 10)
        return;

    int top = lua_gettop(field_08);
    g_activeObj12F0610 = 0;

    char *objectBytes = (char *)object;
    void *eventSource = *(void **)(objectBytes + 0x204);
    if (eventSource == 0)
        return;

    if ((objectBytes[0x344] & 1) != 0) {
        void *guardKey = *recordSlot;
        if (guardKey != field_B8) return;
    }

    void *eventOwner = *(void **)((char *)eventSource + 0x200);
    if (eventOwner == 0)
        return;

    int key = (int)*recordSlot;
    bool hasEventName;
    const AsciiString &name =
        reinterpret_cast<SortedStrings2E1F80 *>(eventOwner)->find(
            key, &hasEventName);
    AsciiString eventName(name);
    char *eventData = *(char **)&eventName;
    if (eventData == 0 || *(unsigned short *)(eventData + 4) == 0)
        return;

    lua_getglobal(field_08, eventData + 8);
    if (lua_type(field_08, -1) != 5)
    {
        AsciiString error;
        if (lua_type(field_08, -1) == 1)
            error = " is not defined.";
        else
            error = " is not a lua function.";
        lua_settop(field_08, top);
        return;
    }

    ((Rva002E42C0Owner *)this)->rva002E42C0(
        field_08,
        (const Rva002E32A0IdOwner *)object);


    char *argumentBytes = (char *)argument3;
    int argumentCount = 1;
    for (int i = 0; i < 3; ++i)
    {
        char *argument = argumentBytes + i * 24;
        switch (*(int *)(argument + 24))
        {
        case 1:
            lua_pushnumber(field_08,
                *(float *)(argument + 8));
            ++argumentCount;
            break;
        case 2:
        {
            bool flag = *(bool *)(argument + 12);
            bfmeGo1039E((BfmeQ1039 *)field_08,
                flag != 0);
            ++argumentCount;
            break;
        }
        case 3:
        {
            int objectID = *(int *)(argument + 16);
            Object *resolved = TheBfmeGameLogic->findObjectByID(objectID);
            ((Rva002E42C0Owner *)this)->rva002E42C0(
                field_08,
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
        g_activeObj12F0610 = field_08;
    ++field_B0;
    lua_call(field_08, argumentCount, 0);
    --field_B0;

    if (g_activeObj12F0610 != 0 &&
        field_B0 == 0)
    {
        bfmePrintTGD("Stepping out of LUA function - step disabled.\n");
        g_activeObj12F0610 = 0;
    }
    int tailKey = (int)*recordSlot;
    ((Rva0026EDD0 *)eventSource)->invoke(tailKey, object, argument3);
}
