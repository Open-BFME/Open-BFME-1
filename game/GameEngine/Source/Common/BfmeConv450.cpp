class AIUpdateInterface
{
public:
	virtual bool isIdle() const;
};

class BfmeThingBEE
{
public:
	bool bfmeGoBEE();
	unsigned char m_bfmeHead[0x3e0];
	bool m_bfmeFlag;
};

bool BfmeThingBEE::bfmeGoBEE()
{
	if (m_bfmeFlag)
		return false;
	return ((AIUpdateInterface *)this)->AIUpdateInterface::isIdle();
}
