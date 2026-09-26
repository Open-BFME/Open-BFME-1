// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// LuaScriptEngine's script-side function registration, retail RVA 0x002EC990.
// The body fills m_luaState at +0x08, the field the landed constructor at
// 0x002EB4A0 zeroes, while the virtual init at 0x002E9220 fills +0x0c.  The
// callback thunks keep their retail ILT identities and are cast only at the
// Lua API boundary, the same way the landed init does.

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

// The landed 156-byte body at 0x002E55C0 reads one script file through
// TheFileSystem and runs it with lua_dobuffer on the lua_State at +0x08.
class Rva002E55C0LuaHost
{
public:
	void loadFile(const char *filename);
};

extern void j_0001bbbc();
extern void j_00039bf3();
extern void j_0001a0c3();
extern void j_00031061();
extern void j_0003a13e();
extern void j_0002332b();
extern void j_0001a578();
extern void j_00014d67();
extern void j_000395a9();
extern void j_0002d614();
extern void j_0003c53d();
extern void j_00004782();
extern void j_000330be();
extern void j_00021c51();
extern void j_0002cd59();
extern void j_0002bcbf();
extern void j_0003d1fe();
extern void j_000155a5();
extern void j_0002336c();
extern void j_00029f28();
extern void j_0003d4bf();
extern void j_0002f24d();
extern void j_00009a84();
extern void j_0003c3ad();
extern void j_00008ca6();
extern void j_0000c55e();
extern void j_0003b683();
extern void j_00015389();
extern void j_0000d409();
extern void j_0000a79f();
extern void j_00047e33();
extern void j_0001ff14();
extern void j_0000fd8f();
extern void j_000376f5();
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
	virtual void postProcessLoad();                 // slot 3, retail no-op
	virtual void reset() = 0;                       // slot 4
	virtual void update() = 0;                      // slot 5
	virtual Bool unidentifiedSlot06(Int arg);       // slot 6, ret 4 false
	virtual void unidentifiedSlot07();              // slot 7, unclaimed no-op
	virtual void unidentifiedSlot08(Int arg);       // slot 8, unclaimed
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

	void rva002EC990RegisterScriptFunctions();
	void rva002EC840ParseTokenFile(const char *filename, Bool keepOpen);
	void rva002E3360ScanEventKeys();

private:
	lua_State *m_luaState;                           // +0x08, this body's state
	lua_State *m_luaStateForGame;                    // +0x0c, init's state
	char m_eventStorage[0xbc - 0x10];                // remaining constructor-proven fields
};

typedef char LuaScriptEngineRetailSize[(sizeof(LuaScriptEngine) == 0xbc) ? 1 : -1];

void LuaScriptEngine::rva002EC990RegisterScriptFunctions()
{
	if (m_luaState == 0)
	{
		lua_State *state = lua_open(0x100);
		m_luaState = state;
		lua_baselibopen(state);
		lua_iolibopen(state);
		lua_strlibopen(state);
		lua_mathlibopen(state);
		lua_dblibopen(state);

	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0001bbbc), 0);
	lua_setglobal(m_luaState, "_ALERT");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_00039bf3), 0);
	lua_setglobal(m_luaState, "GetFrame");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0001a0c3), 0);
	lua_setglobal(m_luaState, "EvaluateCondition");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_00031061), 0);
	lua_setglobal(m_luaState, "ExecuteAction");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0003a13e), 0);
	lua_setglobal(m_luaState, "ObjectDescription");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0002332b), 0);
	lua_setglobal(m_luaState, "ObjectSpy");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0001a578), 0);
	lua_setglobal(m_luaState, "ObjectDispatchEvent");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_00014d67), 0);
	lua_setglobal(m_luaState, "ObjectBroadcastEventToEnemies");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_000395a9), 0);
	lua_setglobal(m_luaState, "ObjectBroadcastEventToAllies");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0002d614), 0);
	lua_setglobal(m_luaState, "ObjectBroadcastEventToCivilians");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0003c53d), 0);
	lua_setglobal(m_luaState, "ObjectBroadcastEventToUnits");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_00004782), 0);
	lua_setglobal(m_luaState, "HordeBroadcastEventToMembers");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_000330be), 0);
	lua_setglobal(m_luaState, "ObjectTeamName");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_00021c51), 0);
	lua_setglobal(m_luaState, "ObjectTemplateName");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0002cd59), 0);
	lua_setglobal(m_luaState, "ObjectTestModelCondition");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0002bcbf), 0);
	lua_setglobal(m_luaState, "ObjectTestCanSufferFear");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0003d1fe), 0);
	lua_setglobal(m_luaState, "ObjectCountNearbyEnemies");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_000155a5), 0);
	lua_setglobal(m_luaState, "ObjectEnterFearState");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0002336c), 0);
	lua_setglobal(m_luaState, "ObjectEnterRunAwayPanicState");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_00029f28), 0);
	lua_setglobal(m_luaState, "ObjectEnterCowerState");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0003d4bf), 0);
	lua_setglobal(m_luaState, "ObjectEnterUncontrollableCowerState");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0002f24d), 0);
	lua_setglobal(m_luaState, "ObjectEnterAlertState");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_00009a84), 0);
	lua_setglobal(m_luaState, "ObjectEnterRampageState");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0003c3ad), 0);
	lua_setglobal(m_luaState, "ObjectPlaySound");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_00008ca6), 0);
	lua_setglobal(m_luaState, "ObjectSetChanting");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0000c55e), 0);
	lua_setglobal(m_luaState, "ObjectSetFearFactor");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0003b683), 0);
	lua_setglobal(m_luaState, "ObjectSetEnragedState");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_00015389), 0);
	lua_setglobal(m_luaState, "ObjectDoSpecialPower");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0000d409), 0);
	lua_setglobal(m_luaState, "ObjectCreateAndFireTempWeapon");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0000a79f), 0);
	lua_setglobal(m_luaState, "ObjectGrantUpgrade");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_00047e33), 0);
	lua_setglobal(m_luaState, "ObjectSetDelayedDeath");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0001ff14), 0);
	lua_setglobal(m_luaState, "ObjectHideSubObject");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_0000fd8f), 0);
	lua_setglobal(m_luaState, "ObjectHideSubObjectPermanently");
	lua_pushcclosure(m_luaState, reinterpret_cast<LuaCFunction>(j_000376f5), 0);
	lua_setglobal(m_luaState, "GetRandomNumber");
		lua_setlinehook(m_luaState, reinterpret_cast<LuaHook>(j_00043806));
	}

	reinterpret_cast<Rva002E55C0LuaHost *>(this)->loadFile("Data\\Scripts\\Scripts.lua");
	rva002EC840ParseTokenFile("Data\\Scripts\\ScriptEvents.xml", false);
	rva002E3360ScanEventKeys();
}
