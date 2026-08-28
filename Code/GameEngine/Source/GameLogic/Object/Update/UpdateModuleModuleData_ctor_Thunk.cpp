// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

void *__cdecl operator new(unsigned int);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

class ModuleDataListStandIn
{
	struct Node
	{
		unsigned char m_flag;
		unsigned char m_pad[3];
		unsigned int m_value;
		Node *m_next;
		Node *m_prev;
		unsigned char m_unused[0x10];
	};

	Node *m_node;
	unsigned int m_count;
	unsigned int m_reserved;
public:
	ModuleDataListStandIn()
	{
		m_node = 0;
		m_node = (Node *)operator new(sizeof(Node));
		m_count = 0;
		m_node->m_flag = 0;
		m_node->m_value = 0;
		m_node->m_next = m_node;
		m_node->m_prev = m_node;
	}
	~ModuleDataListStandIn();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual ~ModuleData() {}
	unsigned int m_04;
};

class UpdateModuleModuleData : public ModuleData
{
public:
	UpdateModuleModuleData();
	virtual ~UpdateModuleModuleData();

private:
	ModuleDataListStandIn m_list;
	int *m_owned[2];
	int m_delay;
	int m_unknown20;
	float m_distance;
	bool m_flag28;
	bool m_flag29;
	unsigned char m_pad2a[2];
	int m_unknown2c;
	AsciiString m_name30;
	int m_unknown34;
	int m_unknown38;
	int m_unknown3c;
	bool m_flag40;
	unsigned char m_pad41[3];
	AsciiString m_machineName;
	int m_unknown48;
	float m_angle;
	ZeroInt m_unknown50;
	bool m_flag54;
	unsigned char m_pad55[3];
	std::vector<AsciiString> m_strings;
};

// ??0UpdateModuleModuleData@@QAE@XZ
UpdateModuleModuleData::UpdateModuleModuleData()
{
	for (int i = 0; i < 2; ++i)
		m_owned[i] = 0;
	m_unknown20 = 0;
	m_distance = 500.0f;
	m_flag28 = false;
	m_delay = 10;
	m_flag29 = false;
	m_unknown2c = 0;
	m_unknown38 = 0;
	m_unknown34 = 0;
	m_unknown3c = 0;
	m_flag40 = false;
	m_unknown48 = 0;

	AsciiStringVectorLayout &strings = *(AsciiStringVectorLayout *)&m_strings;
	eraseAsciiStringRange(strings, strings.m_begin, strings.m_finish);
	m_flag54 = false;
	m_angle = 80.0f;
	m_machineName.set("DefaultAttackPriority", 21);
}
