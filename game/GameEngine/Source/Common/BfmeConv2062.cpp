extern "C" void *__identifier("??_7V3NodeHead@@6B@")[];
#define bfmeVftCUAb __identifier("??_7V3NodeHead@@6B@")

class BfmeLinkCU;

class BfmeListCU
{
public:
	unsigned char m_bfmeGapCU[0x98];
	BfmeLinkCU *m_bfmeTailCU;
	BfmeLinkCU *m_bfmeHeadCU;
};

class BfmeLinkCU
{
public:
	BfmeListCU *m_bfmeListCU;
	BfmeLinkCU *m_bfmeNextCU;
	BfmeLinkCU *m_bfmePrevCU;
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
		link->m_bfmeNextCU = list->m_bfmeHeadCU;
		link->m_bfmePrevCU = 0;
		list->m_bfmeHeadCU = link;

		if (link->m_bfmeNextCU != 0)
			link->m_bfmeNextCU->m_bfmePrevCU = link;
		else
			link->m_bfmeListCU->m_bfmeTailCU = link;
	}
	else
	{
		link->m_bfmePrevCU = 0;
		link->m_bfmeNextCU = 0;
	}

	m_bfmeUserCU = user;
}
