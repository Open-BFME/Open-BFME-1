// ?d_003c72f0@@YAXXZ
// cl: /DNDEBUG /MD /EHsc
// stlport

#include <vector>

class Rva003C72F0Item
{
public:
	char m_pad00[ 0xAC ];
	int m_tag;
};

class Rva003C72F0Owner
{
public:
	Rva003C72F0Item *findByTag( int tag );

private:
	char m_pad00[ 0x14 ];
	std::vector<Rva003C72F0Item *> m_items;
};

Rva003C72F0Item *Rva003C72F0Owner::findByTag( int tag )
{
	unsigned int index = 0;
	unsigned int count = m_items.size();
	if ( count > 0 )
	{
		Rva003C72F0Item **begin = m_items.begin();
		Rva003C72F0Item **cursor = m_items.begin();
		do
		{
			if ( (*cursor)->m_tag == tag )
				return begin[ index ];
			++index;
			++cursor;
			count = m_items.size();
		} while ( index < count );
	}
	return 0;
}
