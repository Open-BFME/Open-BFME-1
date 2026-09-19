// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/moduledata /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"
#include <vector>

class LivingWorldPlayerArmy
{
public:
	LivingWorldPlayerArmy &operator=( const LivingWorldPlayerArmy &other );
	virtual ~LivingWorldPlayerArmy();

private:
	char m_body[ 0x54 ];
};

typedef std::vector<LivingWorldPlayerArmy> LivingWorldPlayerArmyVector;
typedef LivingWorldPlayerArmy *( LivingWorldPlayerArmyVector::*
	LivingWorldPlayerArmyEraseRange )( LivingWorldPlayerArmy *,
		LivingWorldPlayerArmy * );

// Taking the member address preserves retail's out-of-line range-erase COMDAT.
static LivingWorldPlayerArmyEraseRange forceLivingWorldPlayerArmyEraseRange =
	static_cast<LivingWorldPlayerArmyEraseRange>(
		&LivingWorldPlayerArmyVector::erase );
