// The matched caller at 0x003BCA30 proves the outer niladic member identity.
// Its +0x30 vector is the campaign's LivingWorldRegion pointer vector: the
// loop's ILT 0x0000C18A resolves to the region reset at 0x0061AB60.
// stlport

#include <vector>

class LivingWorldRegion
{
public:
	void rva0061AB60();
};

class Gen003C75A0List
{
public:
	char m_pad00[ 0x30 ];
	std::vector<LivingWorldRegion *> m_items;
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
	std::vector<LivingWorldRegion *> &items = list->m_items;
	for( unsigned int index = 0; index < items.size(); ++index )
		items[ index ]->rva0061AB60();
}
