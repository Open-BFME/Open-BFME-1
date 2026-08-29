// ?CurDrawablePlaySound@@YAHPAUlua_State@@@Z
// partial score=0.93 date=2026-08-28
// cl: /DNDEBUG /DWIN32 /MD /O2

typedef float Real;

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" void lua_pushnumber(lua_State *state, double value);
extern "C" const char *lua_tostring(lua_State *state, int index);
extern "C" void lua_pushnil(lua_State *state);
extern "C" void lua_pushboolean(lua_State *state, int value);

extern Real GetGameClientRandomValueReal(Real low, Real high, char *file, int line);

int GetClientRandomNumberReal(lua_State *state)
{
	if (lua_gettop(state) <= 1) {
		lua_pushnumber(state, 0.0);
	} else {
		Real low = (Real)lua_tonumber(state, 1);
		Real high = (Real)lua_tonumber(state, 2);
#line 1744 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\ScriptEngine\\LuaScriptEngine.cpp"
		lua_pushnumber(state, GetGameClientRandomValueReal(low, high, __FILE__, __LINE__));
	}
	return 1;
}

enum KindOfType { KINDOF_INVALID = -1 };

template<int Bits> class BitFlags
{
public:
	static int getSingleBitFromName(const char *name);
};

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing {};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

struct LuaTargetRecord
{
	char m_targetPad[0x2B4];
	int m_targetID;
};

enum DrawableID { INVALID_DRAWABLE_ID = 0 };

class Drawable
{
	public:
	DrawableID getID() const;
	char m_targetPad[0xFC];
	LuaTargetRecord *m_target;
};

struct LuaDrawableLink
{
	char m_drawablePad[0x0C];
	Drawable *m_drawable;
};

struct LuaDrawableState
{
	char m_drawablePad[0x78];
	LuaDrawableLink *m_drawable;
};

extern LuaDrawableState *g_obj12F060C;

int CurDrawableIsCurrentTargetKindof(lua_State *state)
{
	LuaDrawableLink *selection = g_obj12F060C->m_drawable;
	if (selection != 0 && selection->m_drawable != 0 && selection->m_drawable->m_target != 0) {
		Object *target = TheGameLogic->findObjectByID(selection->m_drawable->m_target->m_targetID);
		if (target != 0 && lua_gettop(state) > 0) {
			int kind = BitFlags<17>::getSingleBitFromName(lua_tostring(state, 1));
			if (target->isKindOf((KindOfType)kind)) {
				lua_pushboolean(state, 1);
				return 1;
			}
		}
	} else {
		lua_pushnil(state);
	}

	lua_pushboolean(state, 0);
	return 1;
}

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, DrawableID drawableID);
	virtual ~AudioEventRTS();

private:
	char m_eventData[0x6C];
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual unsigned int addAudioEvent(const AudioEventRTS *event);
};

extern AudioManager *TheAudio;

int CurDrawablePlaySound(lua_State *state)
{
	LuaDrawableLink *selection = g_obj12F060C->m_drawable;
	if (selection != 0) {
		Drawable *drawable = selection->m_drawable;
		if (drawable != 0 && lua_gettop(state) > 0 && TheAudio != 0) {
			AudioEventRTS event(lua_tostring(state, 1), drawable->getID());
			TheAudio->addAudioEvent(&event);
		}
	}
	return 0;
}
