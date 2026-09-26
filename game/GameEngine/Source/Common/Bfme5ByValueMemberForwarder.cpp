class BfmeArgED
{
public:
	BfmeArgED(const BfmeArgED &other);
	~BfmeArgED(void);

private:
	int m_bfmeValues[6];
};

class BfmeConsumerED
{
public:
	void bfmeApply(BfmeArgED value);

private:
	char m_bfmeFields[0x1C];
};

class Gen_0057ED70
{
public:
	void bfmeForward(void);
	void bfmeFinish(void);

private:
	char m_bfme00[0x390];
	BfmeConsumerED m_bfmeConsumer;
	BfmeArgED m_bfmeArgument;
};

// ?bfmeForward@Gen_0057ED70@@QAEXXZ
void Gen_0057ED70::bfmeForward(void)
{
	m_bfmeConsumer.bfmeApply(m_bfmeArgument);
	bfmeFinish();
}
