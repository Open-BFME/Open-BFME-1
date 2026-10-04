// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: retail OrCondition chunky parser in C++.

#include "ascii_string.h"

// Retail vtable 0x00CE84D8 (targets/game/reverse/dir32_addresses.csv,
// 0x010E84D8): ??_7OrCondition@@6B@. The declaration carries no C++ name:
// __identifier spells the retail symbol exactly, so the store below
// references the defining name.
extern "C" const void *__identifier("??_7OrCondition@@6B@")[];

class OrConditionAllocation
{
public:
	__forceinline OrConditionAllocation()
	{
		m_vtable = (unsigned int)__identifier("??_7OrCondition@@6B@");
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Condition
{
public:
	static bool __cdecl ParseConditionDataChunk(DataChunkInput &, DataChunkInfo *, void *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
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
