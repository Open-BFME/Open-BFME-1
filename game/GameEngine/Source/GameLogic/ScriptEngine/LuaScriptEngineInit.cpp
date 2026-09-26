// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// LuaScriptEngine::init, retail RVA 0x002E9220.  The constructor's vtable
// and slot-1 dispatch identify the owner; the callback thunks retain their
// existing retail ILT identities and are cast only at the Lua API boundary.

struct lua_State;
struct lua_Debug;
struct Xfer;
typedef int Int;
typedef bool Bool;

// AsciiString is one data pointer in the retail 32-bit layout.
struct AsciiString { void *m_data; };

typedef int (*LuaCFunction)(lua_State *);
typedef void (*LuaHook)(lua_State *, lua_Debug *);

extern "C" lua_State *lua_open(int stackSize);
extern "C" void lua_baselibopen(lua_State *state);
extern "C" void lua_iolibopen(lua_State *state);
extern "C" void lua_strlibopen(lua_State *state);
extern "C" void lua_mathlibopen(lua_State *state);
extern "C" void lua_dblibopen(lua_State *state);
extern "C" void lua_pushcclosure(lua_State *state, LuaCFunction function, int upvalues);
extern "C" void lua_setglobal(lua_State *state, const char *name);
extern "C" LuaHook lua_setlinehook(lua_State *state, LuaHook hook);

class Rva002E2970Host
{
public:
	void initEventKeys();
};
extern void j_0001bbbc();
extern void j_00039bf3();
extern void j_0003a779();
extern void j_000115e0();
extern void j_00015357();
extern void j_00004c2d();
extern void j_00021aad();
extern void j_00005a79();
extern void j_0000cadb();
extern void j_00007f2c();
extern void j_00022c78();
extern void j_0001c1a7();
extern void j_0001290e();
extern void j_0000c824();
extern void j_00014ab5();
extern void j_00048f22();
extern void j_00032213();
extern void j_00002900();
extern void j_0001da4d();
extern void j_00009ed0();
extern void j_00043806();

// BFME's actual SubsystemInterface prefix is nine slots.  The retail Lua
// table continues with three Lua-owned slots, for twelve total.  This local
// view is declaration-only and novtable: it records the dispatch ABI without
// emitting another table or inventing bodies for the unclaimed slots.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();                  // slot 0
	virtual void init() = 0;                        // slot 1
	virtual Bool loadIniFilesFromLegend();          // slot 2
	virtual void postProcessLoad();                // slot 3, retail no-op
	virtual void reset() = 0;                       // slot 4
	virtual void update() = 0;                      // slot 5
	virtual Bool unidentifiedSlot06(Int arg);        // slot 6, ret 4 false
	virtual void unidentifiedSlot07();              // slot 7, unclaimed no-op
	virtual void unidentifiedSlot08(Int arg);        // slot 8, unclaimed
protected:
	AsciiString m_name;                             // +0x04, four bytes
};

class __declspec(novtable) LuaScriptEngine : public SubsystemInterface
{
public:
	virtual void init();                             // slot 1
	virtual void reset();                            // slot 4
	virtual void update();                           // slot 5
	virtual void loadPostProcess();                  // slot 9, retail ret
	virtual const char *getSnapshotName() const;     // slot 10, literal getter
	virtual void xfer(Xfer &xfer);                   // slot 11, DoXfer ABI

private:
	lua_State *m_luaState;                           // +0x08
	lua_State *m_luaStateForGame;                    // +0x0c, init's state
	char m_eventStorage[0xbc - 0x10];               // remaining constructor-proven fields
};

typedef char LuaScriptEngineRetailSize[(sizeof(LuaScriptEngine) == 0xbc) ? 1 : -1];

void LuaScriptEngine::init()
{
	reinterpret_cast<Rva002E2970Host *>(this)->initEventKeys();
	if (m_luaStateForGame != 0)
		return;

	lua_State *state = lua_open(0x100);
	m_luaStateForGame = state;
	lua_baselibopen(state);
	lua_iolibopen(state);
	lua_strlibopen(state);
	lua_mathlibopen(state);
	lua_dblibopen(state);

	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_0001bbbc), 0);
	lua_setglobal(m_luaStateForGame, "_ALERT");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00039bf3), 0);
	lua_setglobal(m_luaStateForGame, "GetFrame");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_0003a779), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableModelcondition");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_000115e0), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableObjectStatus");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00015357), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableShowSubObject");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00004c2d), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableHideSubObject");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00021aad), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableShowSubObjectPermanently");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00005a79), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableHideSubObjectPermanently");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_0000cadb), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableHideModule");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00007f2c), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableShowModule");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00022c78), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawablePrevAnimationState");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_0001c1a7), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawablePrevAnimation");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_0001290e), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableGetCurrentTargetDistance");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_0000c824), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableGetCurrentTargetHeight");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00014ab5), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawablePrevAnimFraction");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00048f22), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableSetTransitionAnimState");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00032213), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableAllowToContinue");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00002900), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawablePlaySound");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_0001da4d), 0);
	lua_setglobal(m_luaStateForGame, "CurDrawableIsCurrentTargetKindof");
	lua_pushcclosure(m_luaStateForGame, reinterpret_cast<LuaCFunction>(j_00009ed0), 0);
	lua_setglobal(m_luaStateForGame, "GetClientRandomNumberReal");
	lua_setlinehook(m_luaStateForGame, reinterpret_cast<LuaHook>(j_00043806));
}
