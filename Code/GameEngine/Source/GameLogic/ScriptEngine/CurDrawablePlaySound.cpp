// cl: /DNDEBUG /DWIN32 /MD /O2

struct lua_State;

extern "C" int lua_gettop(lua_State *state);
extern "C" const char *lua_tostring(lua_State *state, int index);

enum DrawableID
{
	INVALID_DRAWABLE_ID = 0
};

class Drawable
{
public:
	DrawableID getID() const;
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
	virtual void unusedVirtual();
	~AudioEventRTS();

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

// ?CurDrawablePlaySound@@YAHPAUlua_State@@@Z
int CurDrawablePlaySound(lua_State *state)
{
	LuaDrawableLink *selection = g_obj12F060C->m_drawable;
	Drawable *drawable;
	if (selection == 0
		|| (drawable = selection->m_drawable) == 0
		|| lua_gettop(state) <= 0
		|| TheAudio == 0)
		return 0;
	AudioEventRTS event(lua_tostring(state, 1), drawable->getID());
	TheAudio->addAudioEvent(&event);
	return 0;
}
