// The matched caller at 0x003BCA30 proves this niladic member identity.
// stlport

#include <vector>

class Gen003C75A0Item
{
public:
	void step();
};

class Gen003C75A0List
{
public:
	char m_pad00[ 0x30 ];
	std::vector<Gen003C75A0Item *> m_items;
};

class Gen003C75A0Owner
{
public:
	void step();

private:
	char m_pad00[ 4 ];
	Gen003C75A0List *m_list;
};

void Gen003C75A0Owner::step()
{
	Gen003C75A0List *list = m_list;
	std::vector<Gen003C75A0Item *> &items = list->m_items;
	for( unsigned int index = 0; index < items.size(); ++index )
		items[ index ]->step();
}
