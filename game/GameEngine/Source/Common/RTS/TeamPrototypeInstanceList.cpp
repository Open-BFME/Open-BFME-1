// cl: /DNDEBUG /MD /EHsc
//
// The two TeamPrototype bodies that unlink teams from the instance list, and
// they are adjacent in the image:
//
//   0x000EC4C0  removeFrom_TeamInstanceList  97B  one node
//   0x000EC540  removeAll_TeamInstanceList   94B  every node, with a callback
//
// Both are MAKE_DLINK_HEAD expansions over the same list: the head at
// TeamPrototype+0x274 and the DLINK pair at Team+0x10 / +0x14. The two files
// declared that same pair of models letter for letter, which is the whole of
// the duplication -- there was no disagreement to resolve here, only two
// copies of one four-line layout.
//
// The unlink sequence itself is deliberately left written out twice. The two
// bodies are not the same shape around it: removeFrom guards on "is the head or
// has either link" and does the unlink once, while removeAll loops on the head
// and calls the callback on each detached node. Factoring the five shared lines
// into a helper is exactly the tidy-up a reader will reach for, and it would be
// inlining a decision the compiler made differently in each body.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	char m_pad[0x10];
	Team *m_prev;					// +0x10
	Team *m_next;					// +0x14
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	void removeFrom_TeamInstanceList(Team *o);
	void removeAll_TeamInstanceList(void (*callback)(Team *));

private:
	char m_pad[0x274];
	Team *m_teamInstanceList;			// +0x274
};

// ?removeFrom_TeamInstanceList@TeamPrototype@@QAEXPAVTeam@@@Z
//
// MAKE_DLINK_HEAD removeFrom: if the node is the head or has either link,
// unlink through +0x10/+0x14 and clear both; a node with neither link and not
// the head is a no-op.
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

// ?removeAll_TeamInstanceList@TeamPrototype@@QAEXP6AXPAVTeam@@@Z@Z
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
