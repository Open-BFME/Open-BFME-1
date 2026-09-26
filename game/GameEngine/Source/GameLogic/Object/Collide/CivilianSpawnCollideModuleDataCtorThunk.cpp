// cl: /DNDEBUG /MD /EHsc

// A ModuleData base supplying the vptr, then the four-byte indexed handle at
// +0x08 whose constructor is out of line -- the call resolves to the existing
// pin for ??0RS_Member@@QAE@XZ at 0x0003747A. The named module-data factory
// allocates 0x0c bytes, independently fixing this member's size and the full
// object layout.

#include "../../../../Include/GameLogic/Rva0039D550.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void moduleDataAnchor();		///< vptr at 0x00

	virtual ~ModuleData() {}

	int m_moduleTagNameKey;
};

class RS_Member
{
public:
	RS_Member();

private:
	void *m_handle;
};

class CivilianSpawnCollideModuleData : public ModuleData
{
public:
	CivilianSpawnCollideModuleData();
	virtual ~CivilianSpawnCollideModuleData();

	virtual void moduleDataAnchor();

	RS_Member m_member;						///< 0x08
};

// ??0CivilianSpawnCollideModuleData@@QAE@XZ
CivilianSpawnCollideModuleData::CivilianSpawnCollideModuleData()
{
}

// The factory's 0x0c allocation and the complete destructor's +0x08 indexed
// handle teardown prove that this is the same three-word ModuleData object.
// Keep the handle ABI view address-qualified until the original member name is
// recovered; its destructor call is the exact retail ILT 0x0001A401 route.
class __declspec(novtable) CivilianSpawnCollideModuleData;

// ??1CivilianSpawnCollideModuleData@@UAE@XZ
CivilianSpawnCollideModuleData::~CivilianSpawnCollideModuleData()
{
	reinterpret_cast<Rva0039D550 *>(&m_member)->~Rva0039D550();
}
