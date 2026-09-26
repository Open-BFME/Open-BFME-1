class BfmeStrCD
{
public:
	~BfmeStrCD();

	int m_bfmeDataCD;
};

class BfmeTgtCD
{
public:
	void bfmeSetCD(const BfmeStrCD &other);
};

class BfmeOwnCD
{
public:
	virtual ~BfmeOwnCD(void);
	virtual void bfmePureCD(void) = 0;

	BfmeStrCD m_bfmeTextCD;
	BfmeTgtCD *m_bfmeTargetCD;
};

BfmeOwnCD::~BfmeOwnCD(void)
{
	BfmeTgtCD *target = m_bfmeTargetCD;

	target->bfmeSetCD(m_bfmeTextCD);
}
