// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include <vector>

extern "C" int __cdecl memcmp( const void *left, const void *right, unsigned int count );
#pragma intrinsic(memcmp)

class BfmeEmotionName
{
public:
	~BfmeEmotionName();

	int compare( const BfmeEmotionName &that ) const
	{
		int thatLength = that.m_data ? *(unsigned short *)( that.m_data + 4 ) : 0;
		const char *thatData = that.m_data ? that.m_data + 8 : "";
		int thisLength = m_data ? *(unsigned short *)( m_data + 4 ) : 0;
		const char *thisData = m_data ? m_data + 8 : "";
		int length = thisLength < thatLength ? thisLength : thatLength;
		int result = memcmp( thisData, thatData, length );
		return result ? result : thisLength - thatLength;
	}

private:
	char *m_data;
};

inline bool operator==( const BfmeEmotionName &left, const BfmeEmotionName &right )
{
	return left.compare( right ) == 0;
}

class EmotionNugget
{
public:
	BfmeEmotionName getName() const;
};

class EmotionSystem
{
public:
	EmotionNugget *findNugget( const BfmeEmotionName &name );

private:
	unsigned char m_unmodelled[ 8 ];
	std::vector<EmotionNugget *> m_nuggets;
};

// ?findNugget@EmotionSystem@@QAEPAVEmotionNugget@@ABVBfmeEmotionName@@@Z
EmotionNugget *EmotionSystem::findNugget( const BfmeEmotionName &name )
{
	for( int i = 0; i < m_nuggets.size(); ++i )
	{
		if( m_nuggets[ i ]->getName() == name )
			return m_nuggets[ i ];
	}

	return 0;
}
