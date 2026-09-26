namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

struct BfmeNodeZY
{
	BfmeNodeZY *m_bfmeNextZY;
	BfmeNodeZY *m_bfmePrevZY;
	void *m_bfmeValZY;
};

class BfmeListZY
{
public:
	BfmeListZY()
	{
		m_bfmeNodeZY = 0;

		BfmeNodeZY *n = (BfmeNodeZY *)_STL::__new_alloc::allocate(12);

		n->m_bfmeNextZY = n;
		n->m_bfmePrevZY = n;
		m_bfmeNodeZY = n;
	}

	~BfmeListZY();

	BfmeNodeZY *m_bfmeNodeZY;
};

class BfmeMultiBaseZY
{
public:
	virtual ~BfmeMultiBaseZY();

public:
	unsigned int m_bfme04ZY;
	unsigned int m_bfme08ZY;
};

class BfmeIfaceAZY
{
public:
	virtual void bfmeAnchorAZY();
};

class BfmeIfaceBZY
{
public:
	virtual void bfmeAnchorBZY();
};

class BfmeBaseZY : public BfmeMultiBaseZY, public BfmeIfaceAZY, public BfmeIfaceBZY
{
public:
	BfmeBaseZY(void *a, void *b);
	virtual ~BfmeBaseZY() {}
};

class BfmeOwnerZY : public BfmeBaseZY
{
public:
	BfmeOwnerZY(void *a, void *b);
	virtual ~BfmeOwnerZY() {}

	void bfmeInitZY(void *what, int limit);

	unsigned int m_bfme14ZY;
	unsigned int m_bfme18ZY;
	unsigned int m_bfme1CZY;
	unsigned int m_bfme20ZY;
	BfmeListZY m_bfme24ZY;
};

BfmeOwnerZY::BfmeOwnerZY(void *a, void *b)
	: BfmeBaseZY(a, b)
{
	m_bfme20ZY = 0;
	bfmeInitZY((void *)m_bfme08ZY, 0x3fffffff);
}
