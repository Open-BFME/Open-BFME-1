extern "C" int _bfmeVftVE[];
extern "C" int _bfmeVftXB[];
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeInnerCN
{
public:
	void bfmeCloseCN(void *value);

	int m_bfmeDataCN;
};

class BfmeBaseVE
{
public:
	~BfmeBaseVE()
	{
		m_bfmeVfVE = _bfmeVftVE;

		m_bfmeInnerVE->bfmeCloseCN(m_bfmeArgVE);
	}

	int *volatile m_bfmeVfVE;
	BfmeInnerCN *m_bfmeInnerVE;
	void *m_bfmeArgVE;
	int m_bfmePadVE[2];
};

class BfmeItemCP
{
public:
	virtual void bfmeReleaseCP(int flag);
};

class BfmeEntryCP
{
public:
	char m_bfmeHeadCP[8];
	BfmeItemCP *m_bfmeItemCP;
	char m_bfmeTailCP[12];
};

class BfmeContainerCP
{
public:
	char m_bfmeHeadCP[0x28];
	int m_bfmeCountCP;
	BfmeEntryCP m_bfmeEntriesCP[1];

	BfmeEntryCP *bfmeAtCP(int index)
	{
		if (index < 0 || index >= m_bfmeCountCP)
			return 0;

		return &m_bfmeEntriesCP[index];
	}

	BfmeEntryCP *bfmeAtWithLimitCP(int index, int limit)
	{
		if (index < 0 || index >= limit)
			return 0;

		return &m_bfmeEntriesCP[index];
	}
};

class Rva0035BFB0CallTarget
{
public:
	bool invoke(void *first, void *second);
};

class BfmeOwnCP : public BfmeBaseVE
{
public:
	~BfmeOwnCP(void);
	bool rva001916f0(void *first, void *second);

	BfmeContainerCP *m_bfmeContainerCP;
	BfmeItemCP *m_bfmeItemsCP[32];
	union
	{
		int m_bfmeCountCP;
		volatile int m_bfmeVolatileCountCP;
	};
};

BfmeOwnCP::~BfmeOwnCP(void)
{
	m_bfmeVfVE = _bfmeVftXB;

	for (int index = 0; index < m_bfmeVolatileCountCP; ++index)
	{
		BfmeItemCP *item = m_bfmeItemsCP[index];

		if (item)
			item->bfmeReleaseCP(1);
	}
}

bool BfmeOwnCP::rva001916f0(void *first, void *second)
{
	if (!reinterpret_cast<Rva0035BFB0CallTarget *>(this)->invoke(first, second))
		return false;

	while (m_bfmeCountCP > 0)
	{
		--m_bfmeCountCP;
		BfmeContainerCP *container = m_bfmeContainerCP;
		const int limit = container->m_bfmeCountCP;
		const int innerLimit = container->m_bfmeCountCP;
		int index = m_bfmeCountCP;
		_ReadWriteBarrier();

		if (index < limit)
		{
			BfmeEntryCP *entry = container->bfmeAtWithLimitCP(index, innerLimit);

			BfmeItemCP *oldItem = entry->m_bfmeItemCP;
			if (oldItem)
				oldItem->bfmeReleaseCP(1);

			entry = m_bfmeContainerCP->bfmeAtCP(m_bfmeCountCP);
			entry->m_bfmeItemCP = m_bfmeItemsCP[m_bfmeCountCP];
		}
		else
		{
			BfmeItemCP *item = m_bfmeItemsCP[index];
			if (item)
				item->bfmeReleaseCP(1);
		}
	}

	return true;
}
