// cl: /DNDEBUG /MD /EHsc
//
// TeamPrototype walks the instance list at +0x274, unlinking every team
// through the DLINK pair at Team+0x10 / +0x14 and optionally invoking a
// C callback on the detached node.

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
	void removeAll_TeamInstanceList(void (*callback)(Team *));

private:
	char m_pad[0x274];
	Team *m_teamInstanceList;			// +0x274
};

void TeamPrototype::removeAll_TeamInstanceList(void (*callback)(Team *))
{
	while (m_teamInstanceList)
	{
		Team *node = m_teamInstanceList;
		if (node->m_next)
			node->m_next->m_prev = node->m_prev;
		if (node->m_prev)
			node->m_prev->m_next = node->m_next;
		else
			m_teamInstanceList = node->m_next;
		node->m_prev = 0;
		node->m_next = 0;
		if (callback)
			callback(node);
	}
}
