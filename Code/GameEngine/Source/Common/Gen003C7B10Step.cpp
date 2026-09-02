// Address-derived pointer-vector walk at 0x003C7B10.
// stlport

#include <vector>

class Gen003C7B10Context
{
};

class Gen003C7B10Item
{
public:
	void step( Gen003C7B10Context *context );
};

class Gen003C7B10Owner
{
public:
	void step();

private:
	char m_pad00[ 4 ];
	Gen003C7B10Context m_context;
	char m_pad05[ 0x2B ];
	std::vector<Gen003C7B10Item *> m_items;
};

void Gen003C7B10Owner::step()
{
	for( unsigned int index = 0; index < m_items.size(); ++index )
	{
		Gen003C7B10Context *context = &m_context;
		m_items[ index ]->step( context );
	}
}
