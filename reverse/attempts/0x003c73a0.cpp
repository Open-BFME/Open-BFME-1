// ?containsOrEmpty@Gen003C73A0Owner@@QBE_NPAVGen003C73A0Item@@@Z
// partial score=0.82 date=2026-09-02
// Address-derived guarded pointer-vector membership test at 0x003C73A0.
// stlport

#include <vector>

class Gen003C73A0Item
{
public:
	char m_pad00[ 0xE9 ];
	bool m_enabled;
};

class Gen003C73A0Owner
{
public:
	bool containsOrEmpty( Gen003C73A0Item *item ) const;

private:
	char m_pad00[ 0x14 ];
	std::vector<Gen003C73A0Item *> m_items;
};

bool Gen003C73A0Owner::containsOrEmpty( Gen003C73A0Item *item ) const
{
	if( item != 0 && item->m_enabled )
	{
		if( m_items.empty() )
			return true;
		for( unsigned int index = 0; index < m_items.size(); ++index )
		{
			if( m_items[ index ] == item )
				return true;
		}
		return false;
	}
	return false;
}
