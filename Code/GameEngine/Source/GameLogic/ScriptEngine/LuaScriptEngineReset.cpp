// cl: /O2 /EHsc /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

struct lua_State;
extern "C" void lua_close(lua_State *state);

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();

private:
	void *m_name;
};

class Open2Elem2EB190
{
	public:
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

	BFMERetailAsciiString m_string;
	char m_padding[4];
	_STL::vector<Gen002E1260> m_vector;

	~Open2Elem2EB190();
};

struct GenInt
{
	int m_value;

	GenInt &operator=(const GenInt &other)
	{
		m_value = other.m_value;
		return *this;
	}
};

class WeaponTemplateSet
{
	char m_data[0x54];
};

struct BfmeElemKN
{
	char m_data[0x1c];
};

class LuaScriptEngine : public SubsystemInterface
{
public:
	virtual ~LuaScriptEngine();
	virtual void reset();

private:
	lua_State *m_luaState;
	lua_State *m_luaStateForGame;
	char m_events[13 * 8];
	int m_eventCount;
	_STL::vector<GenInt> m_eventCapacity;
	unsigned char m_eventEnd;
	_STL::vector<Open2Elem2EB190> m_eventBuffer;
	_STL::vector<WeaponTemplateSet> m_eventBufferCapacity;
	_STL::vector<BfmeElemKN> m_functionFields;
	int m_functionTable;
	unsigned char m_initialized;
	int m_functionDataTail;
};

// ?reset@LuaScriptEngine@@UAEXXZ
void LuaScriptEngine::reset()
{
	if (m_luaState)
	{
		lua_close(m_luaState);
		m_luaState = 0;
	}

	m_eventCapacity.clear();
	m_eventBuffer.clear();
	m_eventEnd = 0;
	m_eventBufferCapacity.clear();
	m_functionFields.clear();
}
