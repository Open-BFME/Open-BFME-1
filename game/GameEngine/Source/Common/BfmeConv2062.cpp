extern "C" void *__identifier("??_7V3NodeHead@@6B@")[];
#define bfmeVftCUAb __identifier("??_7V3NodeHead@@6B@")

class BfmeLinkCU;

class BfmeListCU
{
public:
	unsigned char m_bfmeGapCU[0x98];
	BfmeLinkCU *m_tail;
	BfmeLinkCU *m_head;
};

class BfmeLinkCU
{
public:
	BfmeListCU *m_bfmeListCU;
	BfmeLinkCU *m_next;
	BfmeLinkCU *m_prev;
};

class BfmeHolderCU
{
public:
	BfmeHolderCU(BfmeListCU **pl, void *user);

	void *m_bfmeVftCU;
	BfmeLinkCU m_bfmeLinkCU;
	void *m_bfmeUserCU;
};

BfmeHolderCU::BfmeHolderCU(BfmeListCU **pl, void *user)
{
	m_bfmeVftCU = bfmeVftCUAb;

	BfmeListCU *list = *pl;
	BfmeLinkCU *link = &m_bfmeLinkCU;

	link->m_bfmeListCU = list;

	if (list != 0)
	{
		link->m_next = list->m_head;
		link->m_prev = 0;
		list->m_head = link;

		if (link->m_next != 0)
			link->m_next->m_prev = link;
		else
			link->m_bfmeListCU->m_tail = link;
	}
	else
	{
		link->m_prev = 0;
		link->m_next = 0;
	}

	m_bfmeUserCU = user;
}
