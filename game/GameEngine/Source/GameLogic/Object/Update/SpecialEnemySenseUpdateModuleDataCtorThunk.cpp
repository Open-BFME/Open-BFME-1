// cl: /DNDEBUG /MD /EHsc

// vptr, then the RS_Member at 0x08 built out of line, then two plain members.
// ModuleData's inline virtual destructor restores its vptr after member teardown.

#include "../../../../Include/GameLogic/Rva0039D550.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void moduleDataAnchor();
	virtual ~ModuleData() {}

	int m_moduleTagNameKey;
};

class RS_Member
{
public:
	RS_Member();

private:
	void *m_p;
};

class SpecialEnemySenseUpdateModuleData : public ModuleData
{
public:
	SpecialEnemySenseUpdateModuleData();
	virtual ~SpecialEnemySenseUpdateModuleData();

	virtual void moduleDataAnchor();

	RS_Member m_08;
	int m_0c;
	int m_10;
};

// ??0SpecialEnemySenseUpdateModuleData@@QAE@XZ
SpecialEnemySenseUpdateModuleData::SpecialEnemySenseUpdateModuleData()
{
	m_0c = 0;
	m_10 = 1;
}

// Retail tears down the +0x08 handle before restoring ModuleData's vptr.
// This redeclaration suppresses only the redundant derived-vptr store in the
// destructor; the complete class above retains the constructor's real layout.
class __declspec(novtable) SpecialEnemySenseUpdateModuleData;

// ??1SpecialEnemySenseUpdateModuleData@@UAE@XZ
SpecialEnemySenseUpdateModuleData::~SpecialEnemySenseUpdateModuleData()
{
	reinterpret_cast<Rva0039D550 *>(&m_08)->~Rva0039D550();
}
