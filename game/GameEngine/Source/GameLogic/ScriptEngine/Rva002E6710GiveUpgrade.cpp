// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME7: Lua binding at 0x002E6710 resolves an object ID, looks up an
// upgrade by name, gives it to the object, and returns one on success.
// The adjacent Lua binding and the 0x002E6710 family record identify the
// GameLogic, UpgradeCenter, and Object callees used here.

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_type(lua_State *state, int index);
extern "C" const char *lua_tostring(lua_State *state, int index);

unsigned Rva00990030Lookup(lua_State *state, int index);

#include "ascii_string.h"

class BFMERetailAsciiString;

class BfmeStringLiteralBase
{
	friend class BFMERetailAsciiString;
	private:
	BfmeStringLiteralBase(const char *text);
};

class BFMERetailAsciiString : private BfmeStringLiteralBase
{
public:
	BFMERetailAsciiString(const char *text) : BfmeStringLiteralBase(text) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

class Object
{
public:
	void giveUpgrade(const UpgradeTemplate *upgrade);
};

class GameLogic
{
public:
	Object *bfmeFind1011(int id);
};

extern GameLogic *TheGameLogic;
extern UpgradeCenter *TheUpgradeCenter;
extern void *TheAudioClientUpdate;

// ?Rva002E6710GiveUpgrade@@YAHPAUlua_State@@@Z
int Rva002E6710GiveUpgrade(lua_State *state)
{
	if (lua_gettop(state) < 2 || !TheAudioClientUpdate)
		return 0;

	unsigned id = Rva00990030Lookup(state, 1);
	if (!id && lua_type(state, 1) != 1)
		return 0;

	Object *object = TheGameLogic->bfmeFind1011(id);
	if (!object)
		return 0;

	const UpgradeTemplate *upgrade = 0;
	{
		BFMERetailAsciiString name(lua_tostring(state, 2));
		upgrade = TheUpgradeCenter->findUpgrade(*(const AsciiString *)&name);
	}
	if (!upgrade)
		return 0;
	object->giveUpgrade(upgrade);
	return 1;
}
