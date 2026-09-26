class BfmeIfaceERP
{
public:
	virtual void bfmeIface00ERP();
	virtual void bfmeIface01ERP();
	virtual void bfmeIface02ERP();
	virtual void bfmeIface03ERP();
	virtual void bfmeIface04ERP();
	virtual void bfmeIface05ERP();
	virtual void bfmeIface06ERP();
	virtual void bfmeIface07ERP();
	virtual void bfmeIface08ERP();
	virtual void bfmeIface09ERP();
	virtual void bfmeIface10ERP();
	virtual void bfmeIface11ERP();
	virtual void bfmeIface12ERP();
	virtual void bfmeIface13ERP();
	virtual void bfmeIface14ERP();
	virtual void bfmeIface15ERP();
	virtual void bfmeIface16ERP();
	virtual void bfmeIface17ERP();
	virtual void bfmeIface18ERP();
	virtual void bfmeIface19ERP();
	virtual void bfmeIface20ERP();
	virtual void bfmeIface21ERP();
	virtual void bfmeIface22ERP();
	virtual void bfmeIface23ERP();
	virtual void *bfmeIface24ERP();
};

class BfmeModERP
{
public:
	unsigned char m_bfmeHeadERP[0x24];
};

class BfmeThingERP
{
public:
	BfmeModERP *bfmeFindERP(int key);

	unsigned char m_bfmeHeadERP[0x344];
	unsigned char m_bfmeFlagsERP;
};

class BfmeLogicERP
{
public:
	BfmeThingERP *bfmeFindByIdERP(int id);
};

extern BfmeLogicERP *g_bfmeLogicERP;

class BfmeKeyGenERP
{
public:
	int bfmeNameToKeyERP(const char *name);
};

extern BfmeKeyGenERP *g_bfmeKeyGenERP;

class BfmeNodeERP
{
public:
	unsigned char m_bfmeHeadERP[0x20];
	int m_bfmeIdERP;
};

class BfmeOwnerERP
{
public:
	unsigned char m_bfmeHeadERP[0x74];
	void *m_bfmeWantERP;
};

class BfmeHostERP
{
public:
	void bfmeSweepERP();

	unsigned char m_bfmeHeadERP[8];
	BfmeOwnerERP *m_bfmeOwnerERP;
	unsigned char m_bfmeMidERP[0x18];
	BfmeNodeERP **m_bfmeFirstERP;
	BfmeNodeERP **m_bfmeLastERP;
};

void BfmeHostERP::bfmeSweepERP()
{
	for (BfmeNodeERP **it = m_bfmeFirstERP; it != m_bfmeLastERP; ++it)
	{
		BfmeNodeERP *node = *it;

		if (node == 0)
			continue;

		if (node->m_bfmeIdERP == 0)
			continue;

		BfmeThingERP *thing = g_bfmeLogicERP->bfmeFindByIdERP(node->m_bfmeIdERP);

		if (thing != 0 && (thing->m_bfmeFlagsERP & 1) == 0)
		{
			static int s_bfmeKeyERP =
				g_bfmeKeyGenERP->bfmeNameToKeyERP("SiegeDeploySpecialPower");

			BfmeModERP *mod = thing->bfmeFindERP(s_bfmeKeyERP);

			if (mod != 0)
			{
				void *want = m_bfmeOwnerERP->m_bfmeWantERP;

				if (((BfmeIfaceERP *)((char *)mod + 0x24))->bfmeIface24ERP() == want)
					continue;
			}
		}

		node->m_bfmeIdERP = 0;
	}
}
