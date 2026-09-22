// ?d_0061d5a0@@YAXXZ
// partial score=0.98 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc

struct BfmeUniformPayload
{
	int m_value0; int m_value1; int m_value2; int m_value3;
	int m_value4; int m_value5; int m_value6; int m_value7;
	int m_value8; int m_value9;
	volatile int m_value10;
	int m_value11;
};

class BfmeUniformPayloadReceiver
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void updatePayload(void);
	virtual void applyPayload(const BfmeUniformPayload *payload);

	unsigned char m_beforeValues[0x14];
	int m_values[11];
};

class BfmeAnimationHolder
{
public:
	void applyUniformPayload(int value);

private:
	unsigned char m_beforeReceivers[8];
	BfmeUniformPayloadReceiver *m_primary;
	BfmeUniformPayloadReceiver *m_secondary;
};

// ?applyUniformPayload@BfmeAnimationHolder@@QAEXH@Z
void BfmeAnimationHolder::applyUniformPayload(int value)
{
	BfmeUniformPayloadReceiver *primary = m_primary;
	if (primary == 0)
		return;

	primary->updatePayload();

	BfmeUniformPayload payload;
	payload.m_value0 = primary->m_values[0];
	payload.m_value1 = primary->m_values[1];
	payload.m_value2 = primary->m_values[2];
	payload.m_value3 = primary->m_values[3];
	payload.m_value4 = primary->m_values[4];
	payload.m_value5 = primary->m_values[5];
	payload.m_value6 = primary->m_values[6];
	payload.m_value7 = primary->m_values[7];
	payload.m_value8 = primary->m_values[8];
	payload.m_value9 = primary->m_values[9];
	payload.m_value10 = primary->m_values[10];
	int valueCopy = value;
	payload.m_value7 = valueCopy;
	BfmeUniformPayloadReceiver *callTarget = m_primary;
	payload.m_value11 = valueCopy;
	payload.m_value3 = value;

	callTarget->applyPayload(&payload);
	if (m_secondary != 0)
		m_secondary->applyPayload(&payload);
}
