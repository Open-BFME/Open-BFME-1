// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include <vector>

class BfmeEmotionName
{
public:
	~BfmeEmotionName();

private:
	char *m_data;
};

class EmotionNugget
{
public:
	BfmeEmotionName getName() const;
};

class EmotionSystem
{
public:
	void addNugget( EmotionNugget *nugget );
	EmotionNugget *findNugget( const BfmeEmotionName &name );

private:
	unsigned char m_unmodelled[ 8 ];
	std::vector<EmotionNugget *> m_nuggets;
};

// ?addNugget@EmotionSystem@@QAEXPAVEmotionNugget@@@Z
void EmotionSystem::addNugget( EmotionNugget *nugget )
{
	if( !nugget )
		return;

	EmotionNugget *existing = findNugget( nugget->getName() );
	if( existing )
		return;

	m_nuggets.push_back( nugget );
}
