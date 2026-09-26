// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ??0BridgeBehaviorModuleData@@QAE@XZ: game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// Open-BFME5: clean C++ lift of the retail BridgeBehavior module-data constructor.

#include <list>

typedef unsigned int UnsignedInt;

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
struct TimeAndLocationInfo
{
	UnsignedInt delay;
	AsciiString boneName;
};

class FXList;
class ObjectCreationList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
struct BridgeFXInfo
{
	const FXList *fx;
	TimeAndLocationInfo timeAndLocationInfo;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
struct BridgeOCLInfo
{
	const ObjectCreationList *ocl;
	TimeAndLocationInfo timeAndLocationInfo;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleData
{
public:
	virtual ~BehaviorModuleData() {}

private:
	int m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehaviorModuleData : public BehaviorModuleData
{
public:
	BridgeBehaviorModuleData();
	virtual ~BridgeBehaviorModuleData();

private:
	float m_lateralScaffoldSpeed;
	float m_verticalScaffoldSpeed;
	std::list<BridgeFXInfo> m_fx;
	std::list<BridgeOCLInfo> m_ocl;
};

BridgeBehaviorModuleData::BridgeBehaviorModuleData()
{
	m_lateralScaffoldSpeed = 1.0f;
	m_verticalScaffoldSpeed = 1.0f;
}
