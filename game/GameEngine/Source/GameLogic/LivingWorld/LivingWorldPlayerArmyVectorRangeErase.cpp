// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
