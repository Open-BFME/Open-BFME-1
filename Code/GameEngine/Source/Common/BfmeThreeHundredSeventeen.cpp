struct BfmeHolderRM
{
	unsigned char m_bfmeHead[0x64];
	void *m_bfmeWhat;
};

typedef unsigned int UnsignedInt;

struct BfmeModelConditionFlagsRM
{
	volatile UnsignedInt m_words[9];
};

struct BfmeDrawableRM
{
	void replaceModelConditionState(const BfmeModelConditionFlagsRM &flags,
		UnsignedInt a, UnsignedInt b);
	void updateDrawableSupplyStatus(void *what, int many);
};

struct BfmeAIUpdateRM
{
	void friend_notifyStateMachineChanged();
};

struct BfmeSinkRM
{
	void bfmeSendRM(void *what, int many);

	private:
	void notifyModelConditionChanged()
	{
		if (m_drawable)
			m_drawable->replaceModelConditionState(m_conditionFlags, 0, 0);
		if (m_ai)
			m_ai->friend_notifyStateMachineChanged();
	}

	unsigned char m_pad00[0x80];
	BfmeDrawableRM *m_drawable;
	unsigned char m_pad84[0x110 - 0x84];
	BfmeModelConditionFlagsRM m_conditionFlags;
	unsigned char m_pad134[0x204 - 0x134];
	BfmeAIUpdateRM *m_ai;
};

struct BfmeOuterRM
{
	BfmeHolderRM *m_bfmeHolder;
	BfmeSinkRM *m_bfmeSink;
};

class BfmeThingRM
{
public:
	bool bfmeDrainRM();
	unsigned char m_bfmeHead[0xb8];
	int m_bfmeCount;
};

bool BfmeThingRM::bfmeDrainRM()
{
	int many = m_bfmeCount;
	if (many == 0)
		return false;
	m_bfmeCount = --many;
	((BfmeOuterRM *)((char *)this - 0x340))->m_bfmeSink->bfmeSendRM(
		((BfmeOuterRM *)((char *)this - 0x340))->m_bfmeHolder->m_bfmeWhat, many);
	return true;
}

void BfmeSinkRM::bfmeSendRM(void *what, int many)
{
	if (many > 0)
	{
		UnsignedInt mask = 0x100000;
		if (!(m_conditionFlags.m_words[2] & mask))
		{
			m_conditionFlags.m_words[2] |= mask;
			notifyModelConditionChanged();
		}
	}
	else
	{
		if (m_conditionFlags.m_words[2] & 0x100000)
		{
			m_conditionFlags.m_words[2] &= 0xffefffff;
			notifyModelConditionChanged();
		}
	}

	if (m_drawable)
		m_drawable->updateDrawableSupplyStatus(what, many);
}
