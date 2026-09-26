// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME5: CreateCrateDieModuleData constructor lifted from retail.

#include <list>

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}

private:
	unsigned char m_data[4];
};

class InstantDeathDieMuxData
{
public:
	InstantDeathDieMuxData();

private:
	unsigned char m_data[0x2c];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData : public Snapshot
{
public:
	DieModuleData() {}
	virtual ~DieModuleData();

private:
	InstantDeathDieMuxData m_dieMuxData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateCrateDie.h
class CreateCrateDieModuleData : public DieModuleData
{
public:
	CreateCrateDieModuleData();
	virtual ~CreateCrateDieModuleData();

private:
	std::list<AsciiString> m_crateNameList;
};

// ??0CreateCrateDieModuleData@@QAE@XZ
CreateCrateDieModuleData::CreateCrateDieModuleData()
	: DieModuleData(), m_crateNameList()
{
	m_crateNameList.clear();
}
