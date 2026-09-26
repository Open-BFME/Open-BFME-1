class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);

	unsigned char m_bfmeHeadCE[4];
};

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ(void) {}
	virtual void bfmePureVUQ(void) = 0;

	int m_bfmeCVUQ;
};

class BfmeOwnCE : public SubsystemInterface, public BfmeBaseVUQ
{
public:
	virtual ~BfmeOwnCE(void);

	void bfmeShutdownCE(void);
};

BfmeOwnCE::~BfmeOwnCE(void)
{
	bfmeShutdownCE();
}
