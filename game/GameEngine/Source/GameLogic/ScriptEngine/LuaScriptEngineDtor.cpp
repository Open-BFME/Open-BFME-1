// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

struct lua_State;
extern "C" void lua_close(lua_State *state);

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();

private:
	void *m_name;
};

struct Gen_002df780
{
	unsigned int m_value;
	unsigned char m_active;
	unsigned char m_padding[3];
};

struct BFMERetailAsciiString
{
	void *m_data;
	~BFMERetailAsciiString();
};

struct Mem00887940
{
	~Mem00887940();
};

struct Gen002E1260
{
	char m_lead[4];
	Mem00887940 m_owned;
	char m_trail[7];
};

struct Gen20
{
	BFMERetailAsciiString m_string;
	char m_padding[4];
	_STL::vector<Gen002E1260> m_vector;
};

struct Gen84
{
	char m_data[0x54];
};

struct Gen28
{
	char m_data[0x1c];
};

class LuaScriptEngine : public SubsystemInterface
{
public:
	virtual ~LuaScriptEngine();

private:
	lua_State *m_luaState;
	lua_State *m_luaStateForGame;
	Gen_002df780 m_events[13];
	int m_eventCount;
	_STL::vector<int> m_eventCapacity;
	unsigned char m_eventEnd;
	_STL::vector<Gen20> m_eventBuffer;
	_STL::vector<Gen84> m_eventBufferCapacity;
	_STL::vector<Gen28> m_functionFields;
	int m_functionTable;
	unsigned char m_initialized;
	int m_functionDataTail;
};

LuaScriptEngine::~LuaScriptEngine()
{
	if (m_luaState)
	{
		lua_close(m_luaState);
		m_luaState = 0;
	}
	if (m_luaStateForGame)
	{
		lua_close(m_luaStateForGame);
		m_luaStateForGame = 0;
	}
}
