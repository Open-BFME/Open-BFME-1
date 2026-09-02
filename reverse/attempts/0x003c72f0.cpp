// ?findByTag@Gen003C72F0Owner@@QAEPAVGen003C72F0Item@@H@Z
// partial score=0.86 date=2026-09-02
// Address-derived reconstruction of the pointer-vector lookup at 0x003C72F0.
// stlport

#include <vector>

class Gen003C72F0Item
{
public:
	char m_pad00[ 0xAC ];
	int m_tag;
};

class Gen003C72F0Owner
{
public:
	Gen003C72F0Item *findByTag( int tag );

private:
	char m_pad00[ 0x14 ];
	std::vector<Gen003C72F0Item *> m_items;
};

Gen003C72F0Item *Gen003C72F0Owner::findByTag( int tag )
{
	unsigned int count = m_items.size();
	for( unsigned int index = 0; index < count; ++index )
	{
		if( m_items[ index ]->m_tag == tag )
			return m_items[ index ];
	}
	return 0;
}
