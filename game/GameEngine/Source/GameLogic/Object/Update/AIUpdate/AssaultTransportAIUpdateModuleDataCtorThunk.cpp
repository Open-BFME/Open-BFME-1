// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

// Retail allocates this node out of STLport's node pool
// (__node_alloc<true,0>::_M_allocate, 0x0082E540), not ::operator new.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	void *m_data;
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
	AsciiString &operator=(const AsciiString &source);
	void set(const char *text, int length);
};

struct AsciiStringVectorLayout
{
	AsciiString *m_begin;
	AsciiString *m_finish;
	AsciiString *m_capacity;
};

class ZeroInt
{
	int m_value;
public:
	ZeroInt() : m_value(0) {}
};

static __forceinline void eraseAsciiStringRange(
	AsciiStringVectorLayout &vector,
	AsciiString *first,
	AsciiString *last)
{
	AsciiString *source = last;
	AsciiString *destination = first;
	int count = vector.m_finish - last;
	while (count > 0)
	{
		*destination = *source;
		++source;
		++destination;
		--count;
	}

	AsciiString *oldFinish = vector.m_finish;
	for (AsciiString *current = destination; current != oldFinish; ++current)
		current->~AsciiString();
	vector.m_finish = destination;
}

class ModuleDataTreeStandIn
{
	// upstream layout: inputs/vendor/stlport/stl/_tree.h
	struct Node
	{
		unsigned char m_color;
		unsigned char m_pad[3];
		Node *m_parent;
		Node *m_left;
		Node *m_right;
		unsigned char m_unused[0x10];
	};

	Node *m_header;
	unsigned int m_count;
	unsigned int m_reserved;
public:
	ModuleDataTreeStandIn()
	{
		m_header = 0;
		m_header = (Node *)_STL::_Node_alloc::allocate(sizeof(Node));
		m_count = 0;
		m_header->m_color = 0;
		m_header->m_parent = 0;
		m_header->m_left = m_header;
		m_header->m_right = m_header;
	}
	~ModuleDataTreeStandIn();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual ~ModuleData() {}
	unsigned int m_moduleTagNameKey;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AssaultTransportAIUpdate.h
class AssaultTransportAIUpdateModuleData : public ModuleData
{
public:
	AssaultTransportAIUpdateModuleData();
	virtual ~AssaultTransportAIUpdateModuleData();

private:
	ModuleDataTreeStandIn m_tree;
	int *m_owned[2];
	int m_delay;
	int m_autoAcquireEnemiesWhenIdle;
	float m_distance;
	bool m_standGround;
	bool m_canAttackWhileContained;
	unsigned char m_pad2a[2];
	int m_holdGroundCloseRangeDistance;
	AsciiString m_name30;
	int m_maxCowerTime;
	int m_minCowerTime;
	int m_rampageTime;
	bool m_rampageRequiresAflame;
	unsigned char m_pad41[3];
	AsciiString m_machineName;
	int m_timeToEjectPassengersOnRampage;
	float m_angle;
	ZeroInt m_unknown50;
	bool m_fadeOnPortals;
	unsigned char m_pad55[3];
	std::vector<AsciiString> m_strings;
};

// ??0AssaultTransportAIUpdateModuleData@@QAE@XZ
AssaultTransportAIUpdateModuleData::AssaultTransportAIUpdateModuleData()
{
	for (int i = 0; i < 2; ++i)
		m_owned[i] = 0;
	m_autoAcquireEnemiesWhenIdle = 0;
	m_distance = 500.0f;
	m_standGround = false;
	m_delay = 10;
	m_canAttackWhileContained = false;
	m_holdGroundCloseRangeDistance = 0;
	m_minCowerTime = 0;
	m_maxCowerTime = 0;
	m_rampageTime = 0;
	m_rampageRequiresAflame = false;
	m_timeToEjectPassengersOnRampage = 0;

	AsciiStringVectorLayout &strings = *(AsciiStringVectorLayout *)&m_strings;
	eraseAsciiStringRange(strings, strings.m_begin, strings.m_finish);
	m_fadeOnPortals = false;
	m_angle = 80.0f;
	m_machineName.set("DefaultAttackPriority", 21);
}
