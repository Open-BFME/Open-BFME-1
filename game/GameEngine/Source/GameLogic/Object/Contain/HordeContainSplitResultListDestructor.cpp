// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Open-BFME5: split-result-list destructor, retail 0x00240590.

#define BFME_STLP_NODE_ALLOC 1
#include "PreRTS.h"
#include <algorithm>

namespace _STL
{
	void vectorLargeDeallocate( void *memory );
	void vectorSmallDeallocate( void *memory, unsigned int bytes );
}

class BfmeSplitResultListName
{
public:
	~BfmeSplitResultListName();

private:
	void *m_data;
};

struct BfmeSplitResultValue
{
	int m_value[ 3 ];
};

class BfmeSplitResultVector
{
public:
	void clear()
	{
		m_finish = std::copy( m_finish, m_finish, m_start );
	}

	__forceinline ~BfmeSplitResultVector()
	{
		if ( m_start )
		{
			unsigned int bytes = ( m_capacity - m_start ) * sizeof( BfmeSplitResultValue );
			if ( bytes > 128 )
				_STL::vectorLargeDeallocate( m_start );
			else
				_STL::vectorSmallDeallocate( m_start, bytes );
		}
	}

private:
	BfmeSplitResultValue *m_start;
	BfmeSplitResultValue *m_finish;
	BfmeSplitResultValue *m_capacity;
};

class __declspec(novtable) BfmeHordeContainSplitResultList
{
public:
	virtual void bfmeSlot0( void );
	~BfmeHordeContainSplitResultList();

private:
	BfmeSplitResultListName m_name;
	BfmeSplitResultVector m_values;
};

BfmeHordeContainSplitResultList::~BfmeHordeContainSplitResultList()
{
	m_values.clear();
}
