// EA FESL gamebrowser list exchange at retail 0x007F73C0.
//
// The three eight-byte lists are copied through the browser lookup object,
// then the eligible hosted entries are folded into the final request.

// cl: /O2 /Ob0 /Oy

class BfmeMsgVJH
{
public:
	BfmeMsgVJH(char *buf, int n) throw();
	~BfmeMsgVJH() throw();
	char m_pad[0x34];
};

struct BfmePairVJU
{
	BfmePairVJU() {}
	int m_value;
	int m_result;
};

class BfmeElementVJU
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void fill(BfmePairVJU *pair) throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual int value(int item) throw();
	virtual void v18() throw();
	virtual int state() throw();
};

class BfmeBrowserLookupVJU
{
public:
	virtual void v00() throw();
	virtual int value0(int item) throw();
	virtual int value1(int item) throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual int listValue() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void v24() throw();
	virtual void v28() throw();
	virtual int count() throw();
	virtual BfmeElementVJU *element(int index) throw();
};

class BfmeBrowserSenderVJU
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void v24() throw();
	virtual void sendList0(BfmeMsgVJH *msg, int zero, BfmePairVJU *output,
		int count, int value) throw();
	virtual void sendList1(BfmeMsgVJH *msg, BfmePairVJU *output,
		int count) throw();
	virtual void sendList2(BfmeMsgVJH *msg, int pairValue,
		BfmePairVJU *output, int count) throw();
	virtual void sendFinal(BfmeMsgVJH *msg, int zero) throw();
};

class BfmeBrowserNotifyVJU
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void send(BfmeMsgVJH *msg, void (__stdcall *callback)(),
		void *owner, int value) throw();
};

class BfmeThingVJU
{
public:
	void bfmeGoVJU() throw();

	char m_pad00[0x10];
	BfmeBrowserSenderVJU *m_bfme10;
	BfmeBrowserNotifyVJU *m_bfme14;
	char m_pad18[0x290];
	BfmePairVJU *m_items0;
	int m_items0Count;
	BfmePairVJU *m_items1;
	int m_items1Count;
	BfmePairVJU *m_items2;
	int m_items2Count;
	BfmePairVJU *m_output0;
	int m_output0Limit;
	BfmePairVJU *m_output1;
	int m_output1Limit;
	BfmePairVJU *m_output2;
	int m_output2Limit;
	BfmeBrowserLookupVJU *m_bfme2d8;
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJU::bfmeGoVJU() throw()
{
	BfmeMsgVJH msg(m_bfmeBuf, 0x400);
	m_bfme10->sendFinal(&msg, 1);
	m_bfme14->send(&msg, 0, this, m_bfme6dc);

	int count0 = m_items0Count;
	BfmePairVJU *output = m_output0;
	for (int i = 0; i < count0; ++i)
	{
		BfmePairVJU *out = (i >= m_output0Limit)
			? 0
			: &m_output0[i];
		BfmePairVJU *input = (i >= m_items0Count)
			? 0
			: &m_items0[i];
		int item = input->m_value;
		out->m_value = item;
		out->m_result = m_bfme2d8->value0(item);
	}
	m_bfme10->sendList0(&msg, 0, output, count0,
		m_bfme2d8->listValue());
	m_bfme14->send(&msg, 0, this, m_bfme6dc);

	int count1 = m_items1Count;
	output = m_output1;
	for (int i = 0; i < count1; ++i)
	{
		BfmePairVJU *out = (i >= m_output1Limit)
			? 0
			: &m_output1[i];
		BfmePairVJU *input = (i >= m_items1Count)
			? 0
			: &m_items1[i];
		int item = input->m_value;
		out->m_value = item;
		out->m_result = m_bfme2d8->value1(item);
	}
	m_bfme10->sendList1(&msg, output, count1);
	m_bfme14->send(&msg, 0, this, m_bfme6dc);

	output = m_output2;
	int count2 = m_items2Count;
	int outerCount = m_bfme2d8->count();
	for (int i = 0; i < outerCount; ++i)
	{
		BfmeElementVJU *element = m_bfme2d8->element(i);
		if (element->state() == 4)
		{
			int pair0;
			int pair1;
			element->fill((BfmePairVJU *)&pair0);
			for (int j = 0; j < count2; ++j)
			{
				BfmePairVJU *out = (j >= m_output2Limit)
					? 0
					: &m_output2[j];
				BfmePairVJU *input = (j >= m_items2Count)
					? 0
					: &m_items2[j];
				int item = input->m_value;
				out->m_value = item;
				out->m_result = element->value(item);
			}
			m_bfme10->sendList2(&msg, pair0, output, count2);
			m_bfme14->send(&msg, 0, this, m_bfme6dc);
		}
	}
	m_bfme10->sendFinal(&msg, 0);
	m_bfme14->send(&msg, 0, this, m_bfme6dc);
}
