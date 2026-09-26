struct Rva21B1A0RingNode
{
	Rva21B1A0RingNode *next;
};

class Rva21B1A0RingLimit
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual int getLimit(void) = 0;

	bool belowLimit(int unused);

private:
	char m_gap[0x998];
	Rva21B1A0RingNode *m_ring;
};

bool Rva21B1A0RingLimit::belowLimit(int)
{
	int limit = getLimit();
	Rva21B1A0RingNode *sentinel = m_ring;
	int count = 0;

	for (Rva21B1A0RingNode *node = sentinel->next; node != sentinel; node = node->next)
		++count;

	return count < limit;
}
