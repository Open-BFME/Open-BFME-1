// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of MonsterDockUpdateModuleData.

#include "../../../../../Include/GameLogic/Rva0039D550.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h
class DockUpdateModuleData
{
public:
	DockUpdateModuleData();
	virtual ~DockUpdateModuleData() {}

private:
	unsigned char m_pad[0x0c];
};

class MonsterDockDataMember
{
public:
	MonsterDockDataMember();

private:
	unsigned int m_value;
};

class MonsterDockUpdateModuleData : public DockUpdateModuleData
{
public:
	MonsterDockUpdateModuleData();
	virtual ~MonsterDockUpdateModuleData();

private:
	MonsterDockDataMember m_member;
	unsigned int m_initialDockCount;
};

// ??0MonsterDockUpdateModuleData@@QAE@XZ
MonsterDockUpdateModuleData::MonsterDockUpdateModuleData() :
	DockUpdateModuleData(),
	m_member(),
	m_initialDockCount(0)
{
}

// Retail does not rewrite the derived vtable before member teardown.
class __declspec(novtable) MonsterDockUpdateModuleData;

// ??1MonsterDockUpdateModuleData@@UAE@XZ
MonsterDockUpdateModuleData::~MonsterDockUpdateModuleData()
{
	reinterpret_cast<Rva0039D550 *>(&m_member)->~Rva0039D550();
}
