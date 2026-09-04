// ?bfmeSendRM@BfmeSinkRM@@QAEXPAXH@Z
// partial score=0.95 date=2026-09-02
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
	if (currentSupply <= 0)
	{
		UnsignedInt flags = *reinterpret_cast<volatile UnsignedInt *>(
			reinterpret_cast<char *>(this) + 0x118);
		if (flags & 0x100000)
		{
			flags &= 0xffefffff;
			*reinterpret_cast<volatile UnsignedInt *>(
				reinterpret_cast<char *>(this) + 0x118) = flags;
			notifyModelConditionChanged();
		}
	}
	else
	{
		UnsignedInt flags = *reinterpret_cast<volatile UnsignedInt *>(
			reinterpret_cast<char *>(this) + 0x118);
		UnsignedInt mask = 0x100000;
		if (!(flags & mask))
		{
			flags |= mask;
			*reinterpret_cast<volatile UnsignedInt *>(
				reinterpret_cast<char *>(this) + 0x118) = flags;
			notifyModelConditionChanged();
		}
	}

	if (m_drawable)
		m_drawable->updateDrawableSupplyStatus(maxSupply, currentSupply);
}
