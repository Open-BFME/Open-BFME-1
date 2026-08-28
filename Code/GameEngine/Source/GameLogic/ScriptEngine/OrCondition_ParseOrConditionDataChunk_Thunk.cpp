// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail OrCondition chunky parser in C++.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();
private:
	unsigned int m_data;
};

class OrConditionAllocation
{
public:
	__forceinline OrConditionAllocation()
	{
		m_vtable = 0x010e84d8;
		m_next = 0;
		m_first = 0;
	}
private:
	unsigned int m_vtable;
public:
	OrConditionAllocation *m_next;
private:
	void *m_first;
};

struct DataChunkInfo { AsciiString label; };
class DataChunkInput;
typedef bool (__cdecl *ChunkParser)(DataChunkInput &, DataChunkInfo *, void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkInput
{
public:
	void registerParser(const AsciiString &name, const AsciiString &parent, ChunkParser parser, void *user_data);
	bool parse(void *instance);
};

class ScriptLayout
{
public:
	unsigned char m_prefix[0x1c];
	OrConditionAllocation *m_or_condition;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Condition
{
public:
	static bool __cdecl ParseConditionDataChunk(DataChunkInput &, DataChunkInfo *, void *);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class OrCondition
{
public:
	static bool __cdecl ParseOrConditionDataChunk(DataChunkInput &, DataChunkInfo *, void *);
};

bool __cdecl OrCondition::ParseOrConditionDataChunk(DataChunkInput &file, DataChunkInfo *info, void *user_data)
{
	OrConditionAllocation *condition = new OrConditionAllocation;
	ScriptLayout *script = (ScriptLayout *)user_data;
	OrConditionAllocation *last = script->m_or_condition;
	while (last && last->m_next)
		last = last->m_next;
	if (last)
		last->m_next = condition;
	else
		script->m_or_condition = condition;
	{
		AsciiString name("Condition");
		file.registerParser(name, info->label, Condition::ParseConditionDataChunk, 0);
	}
	return file.parse(condition);
}
