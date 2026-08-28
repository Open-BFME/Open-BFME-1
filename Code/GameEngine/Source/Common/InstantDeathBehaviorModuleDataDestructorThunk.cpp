// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ lift of the retail module-data destructor.

#include <vector>

class FXList;
class ObjectCreationList;
class WeaponTemplate;

class InstantDeathBehaviorModuleDataAllocator
{
public:
	~InstantDeathBehaviorModuleDataAllocator();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}

private:
	unsigned char m_data[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData : public Snapshot
{
public:
	virtual ~DieModuleData() {}

private:
	unsigned char m_data[0x2c];
};

class __declspec(novtable) InstantDeathBehaviorModuleData : public DieModuleData
{
public:
	virtual ~InstantDeathBehaviorModuleData();

private:
	std::vector<const FXList *> m_fx;
	std::vector<const ObjectCreationList *> m_ocls;
	std::vector<const WeaponTemplate *> m_weapons;
	InstantDeathBehaviorModuleDataAllocator m_allocator;
};

// ??1InstantDeathBehaviorModuleData@@UAE@XZ
InstantDeathBehaviorModuleData::~InstantDeathBehaviorModuleData()
{
}
