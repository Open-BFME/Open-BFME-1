class BfmeMultiBaseZX
{
public:
	virtual ~BfmeMultiBaseZX();

private:
	unsigned int m_bfme04ZX;
	unsigned int m_bfme08ZX;
};

class BfmeIfaceAZX
{
public:
	virtual void bfmeAnchorAZX();
};

class BfmeIfaceBZX
{
public:
	virtual void bfmeAnchorBZX();
};

class BfmeIfaceCZX
{
public:
	virtual void bfmeAnchorCZX();
};

class BfmeDeepBaseZX : public BfmeMultiBaseZX, public BfmeIfaceAZX
{
public:
	virtual ~BfmeDeepBaseZX() {}
};

class BfmeMiddleZX : public BfmeDeepBaseZX, public BfmeIfaceBZX
{
public:
	virtual ~BfmeMiddleZX() {}

	unsigned int m_bfme14ZX;
	unsigned int m_bfme18ZX;
	unsigned int m_bfme1CZX;
};

class BfmeListAZX
{
public:
	~BfmeListAZX();

	void *m_bfmeHeadAZX;
	void *m_bfmeTailAZX;
};

class BfmeListBZX
{
public:
	~BfmeListBZX();

	void *m_bfmeHeadBZX;
	void *m_bfmeTailBZX;
};

class BfmeOwnerZX : public BfmeMiddleZX, public BfmeIfaceCZX
{
public:
	virtual ~BfmeOwnerZX();

	unsigned int m_bfme24ZX;
	BfmeListAZX m_bfme28ZX;
	BfmeListBZX m_bfme30ZX;
};

BfmeOwnerZX::~BfmeOwnerZX()
{
}
