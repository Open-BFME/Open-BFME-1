// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

// LuaScriptEngine's constructor, retail 0x002EB4A0.
//
// GameEngine::init registers TheLuaScriptEngine through the 188-byte object
// described in targets/game/reverse/gameengine_init_subsystems.tsv. The vtable at
// 0x010CFAC4 and the name literal at 0x002EB5B0 identify this class.

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

	Gen_002df780()
	{
		m();
		m_active = 0;
	}
	void *m();
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

struct Gen12
{
	int m_first;
	int m_second;
	int m_third;

	Gen12()
		: m_first(0), m_second(0), m_third(0)
	{
	}
};

class LuaScriptEngine : public SubsystemInterface
{
public:
	LuaScriptEngine();
	virtual ~LuaScriptEngine();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void draw();
	virtual void registerFunction();
	virtual void unregisterFunction();

private:
	void *m_luaState;
	void *m_luaStateForGame;
	Gen_002df780 m_events[13];
	int m_eventCount;
	_STL::vector<int> m_eventCapacity;
	unsigned char m_eventEnd;
	_STL::vector<Gen20> m_eventBuffer;
	_STL::vector<Gen84> m_eventBufferCapacity;
	Gen12 m_functionFields;
	int m_functionTable;
	unsigned char m_initialized;
	int m_functionDataTail;
};

// ??0LuaScriptEngine@@QAE@XZ
LuaScriptEngine::LuaScriptEngine()
	: m_luaState(0),
	  m_luaStateForGame(0),
	  m_eventCount(0),
	  m_eventEnd(0),
	  m_functionFields(),
	  m_functionTable(0),
	  m_initialized(0),
	  m_functionDataTail(0)
{
}
