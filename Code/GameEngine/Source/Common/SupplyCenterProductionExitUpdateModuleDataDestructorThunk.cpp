// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ lift of the retail module-data destructor.

#include <vector>

class SupplyCenterProductionExitEntry
{
public:
	~SupplyCenterProductionExitEntry();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleData
{
public:
	virtual ~UpdateModuleData();

private:
	unsigned int m_moduleTagNameKey;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterProductionExitUpdate.h
class SupplyCenterProductionExitUpdateModuleData : public UpdateModuleData
{
public:
	virtual ~SupplyCenterProductionExitUpdateModuleData();

private:
	std::vector<SupplyCenterProductionExitEntry *> m_entries;
	std::vector<unsigned int> m_values;
};

// ??1SupplyCenterProductionExitUpdateModuleData@@UAE@XZ
SupplyCenterProductionExitUpdateModuleData::~SupplyCenterProductionExitUpdateModuleData()
{
	for (std::vector<SupplyCenterProductionExitEntry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
		delete *it;
}
