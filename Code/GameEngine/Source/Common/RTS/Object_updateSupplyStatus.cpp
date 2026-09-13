// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport
// Object::updateSupplyStatus, retail 0x001C8B20 (152 bytes).

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef unsigned int UnsignedInt;

class ModelConditionFlags
{
public:
	bool test(int bit) const
	{
		return m_bits.test(bit);
	}

	void set(int bit)
	{
		m_bits.set(bit);
	}

	void reset(int bit)
	{
		m_bits.reset(bit);
	}

private:
	_STL::bitset<288> m_bits;
};

class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &flags,
		UnsignedInt a, UnsignedInt b);
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
		if (!m_conditionFlags.test(84))
		{
			m_conditionFlags.set(84);
			notifyModelConditionChanged();
		}
	}
	else
	{
		if (m_conditionFlags.test(84))
		{
			m_conditionFlags.reset(84);
			notifyModelConditionChanged();
		}
	}

	if (m_drawable)
		m_drawable->updateDrawableSupplyStatus(maxSupply, currentSupply);
}
