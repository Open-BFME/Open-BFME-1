// ?updateSupplyStatus@Object@@QAEXHH@Z
// partial score=0.95 date=2026-09-04
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
typedef unsigned int UnsignedInt;

class ModelConditionFlags
{
public:
	UnsignedInt m_words[9];
};

class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &flags, UnsignedInt a, UnsignedInt b);
	void updateDrawableSupplyStatus(int maxSupply, int currentSupply);
};

class AIUpdateInterface
{
public:
	virtual void friend_notifyStateMachineChanged();
};

class Object
{
public:
	void updateSupplyStatus(int maxSupply, int currentSupply);

private:
	void notifyModelConditionChanged()
	{
		if (m_drawable)
			m_drawable->replaceModelConditionState(m_conditionFlags, 0, 0);
		if (m_ai)
			m_ai->AIUpdateInterface::friend_notifyStateMachineChanged();
	}

	unsigned char m_unmodelled_00[0x80];
	Drawable *m_drawable;
	unsigned char m_unmodelled_84[0x110 - 0x84];
	ModelConditionFlags m_conditionFlags;
	unsigned char m_unmodelled_134[0x204 - 0x134];
	AIUpdateInterface *m_ai;
};

void Object::updateSupplyStatus(int maxSupply, int currentSupply)
{
	if (currentSupply > 0)
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
		m_drawable->updateDrawableSupplyStatus(maxSupply, currentSupply);
}
