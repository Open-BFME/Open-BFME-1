// Looking through a list for the first entry that will take what the whole is
// offering, remembering it, and then asking it to get on with the job.

class BfmeItemCK;
class BfmeResultCK;

class BfmePartCK
{
public:
	virtual void bfmeSpare000CK(void);
	virtual void bfmeSpare001CK(void);
	virtual void bfmeSpare002CK(void);
	virtual void bfmeSpare003CK(void);
	virtual void bfmeSpare004CK(void);
	virtual void bfmeSpare005CK(void);
	virtual void bfmeSpare006CK(void);
	virtual BfmeItemCK *bfmeFindCK(void);
	virtual void bfmeSpare008CK(void);
	virtual void bfmeSpare009CK(void);
	virtual void bfmeSpare010CK(void);
	virtual void bfmeSpare011CK(void);
	virtual void bfmeSpare012CK(void);
	virtual void bfmeSpare013CK(void);
	virtual void bfmeSpare014CK(void);
	virtual void bfmeSpare015CK(void);
	virtual void bfmeSpare016CK(void);
	virtual void bfmeSpare017CK(void);
	virtual void bfmeSpare018CK(void);
	virtual void bfmeSpare019CK(void);
	virtual void bfmeSpare020CK(void);
	virtual void bfmeSpare021CK(void);
	virtual void bfmeSpare022CK(void);
	virtual void bfmeSpare023CK(void);
	virtual BfmeResultCK *bfmeGetCK(void);
};

class BfmeItemCK
{
public:
	virtual unsigned char bfmeAskCK(void *what) = 0;
};

class BfmeResultCK
{
public:
	virtual void bfmeSpare000CL(void) = 0;
	virtual void bfmeSpare001CL(void) = 0;
	virtual unsigned char bfmeDoCK(void) = 0;
};

struct BfmeEntryCK
{
	unsigned char m_bfmeHead[0xc];		// 0x0
	BfmePartCK m_bfmePart;			// 0xc
};

struct BfmeOfferCK
{
	unsigned char m_bfmeHead[0x210];	// 0x000
	void *m_bfmeWhat;			// 0x210
};

struct BfmeKeeperCK
{
	unsigned char m_bfmeHead[0x1f0];	// 0x000
	BfmeEntryCK **m_bfmeList;		// 0x1f0
};

class BfmeSubCK
{
public:
	unsigned char bfmeGoCK(void);

	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeEntryCK *m_bfmeFound;		// 0x1c
};

struct BfmeHostCK
{
	BfmeOfferCK *m_bfmeOffer;		// 0x0
	BfmeKeeperCK *m_bfmeKeeper;		// 0x4
	unsigned char m_bfmeGap[4];		// 0x8
	BfmeSubCK m_bfmeSub;			// 0xc
};

unsigned char BfmeSubCK::bfmeGoCK(void)
{
	BfmeEntryCK *found = m_bfmeFound;

	if (found == 0)
	{
		if (((const BfmeHostCK *)((const char *)this - 0xc))->m_bfmeOffer->m_bfmeWhat == 0)
			return 0;

		BfmeEntryCK **at = ((const BfmeHostCK *)((const char *)this - 0xc))->m_bfmeKeeper->m_bfmeList;

		while (*at != 0)
		{
			BfmeItemCK *item = (*at)->m_bfmePart.bfmeFindCK();

			if (item != 0 &&
				item->bfmeAskCK(((const BfmeHostCK *)((const char *)this - 0xc))->m_bfmeOffer->m_bfmeWhat) != 0)
			{
				m_bfmeFound = *at;

				break;
			}

			++at;
		}

		found = m_bfmeFound;

		if (found == 0)
			return 0;
	}

	BfmeResultCK *result = found->m_bfmePart.bfmeGetCK();

	if (result != 0)
		return result->bfmeDoCK();

	return 1;
}

