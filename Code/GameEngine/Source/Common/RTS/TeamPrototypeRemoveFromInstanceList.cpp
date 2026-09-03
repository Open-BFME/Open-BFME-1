// cl: /DNDEBUG /MD /EHsc
//
// TeamPrototype::removeFrom_TeamInstanceList. MAKE_DLINK_HEAD removeFrom:
// if the node is the head or has either link, unlink through +0x10/+0x14
// and clear both; a node with neither link and not the head is a no-op.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	char m_pad[0x10];
	Team *m_prev;					// +0x10
	Team *m_next;					// +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	void removeFrom_TeamInstanceList(Team *o);

private:
	char m_pad[0x274];
	Team *m_teamInstanceList;			// +0x274
};

void TeamPrototype::removeFrom_TeamInstanceList(Team *o)
{
	if (m_teamInstanceList == o || o->m_prev || o->m_next)
	{
		if (o->m_next)
			o->m_next->m_prev = o->m_prev;
		if (o->m_prev)
			o->m_prev->m_next = o->m_next;
		else
			m_teamInstanceList = o->m_next;
		o->m_prev = 0;
		o->m_next = 0;
	}
}
