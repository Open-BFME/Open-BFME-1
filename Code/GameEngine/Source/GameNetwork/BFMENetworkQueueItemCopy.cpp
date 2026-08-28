// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <string>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PersistentStorageThread.h
class PSPlayerStats
{
public:
	PSPlayerStats &operator=( const PSPlayerStats &other );

private:
	unsigned char m_data[ 0x1c4 ];
};

class BFMENetworkQueueItem
{
public:
	BFMENetworkQueueItem &operator=( const BFMENetworkQueueItem &other );

private:
	unsigned int m_type;
	PSPlayerStats m_stats;
	_STL::string m_name;
	_STL::string m_map;
	_STL::string m_address;
	_STL::string m_extra;
	bool m_flag0;
	bool m_flag1;
	unsigned char m_padding[ 2 ];
	unsigned int m_value0;
	unsigned int m_value1;
	_STL::string m_tail;
};

// ??4BFMENetworkQueueItem@@QAEAAV0@ABV0@@Z
BFMENetworkQueueItem &BFMENetworkQueueItem::operator=( const BFMENetworkQueueItem &other )
{
	m_type = other.m_type;
	m_stats = other.m_stats;
	m_name = other.m_name;
	m_map = other.m_map;
	m_address = other.m_address;
	m_extra = other.m_extra;
	m_flag0 = other.m_flag0;
	m_flag1 = other.m_flag1;
	m_value0 = other.m_value0;
	m_value1 = other.m_value1;
	m_tail = other.m_tail;
	return *this;
}
