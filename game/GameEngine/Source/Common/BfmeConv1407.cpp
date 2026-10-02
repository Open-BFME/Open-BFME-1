// Object's two-mask model-condition update at retail RVA 0x001C7720.

template <int N> class BitFlags;

class ModelConditionFlags
{
public:
	bool operator!=(const ModelConditionFlags &other) const;
	void clearAndSet(const ModelConditionFlags &clear, const ModelConditionFlags &set);
	unsigned int m_bits[10];
};

class Drawable
{
public:
	void replaceModelConditionState(const ModelConditionFlags &flags,
		unsigned int forceReplace, unsigned int value);
};

class AIUpdateInterface
{
public:
	virtual void friend_notifyStateMachineChanged();
};

#define BFME_HAVE_MODELCONDITIONFLAGS 1
#define OBJECT_TU_MEMBERS void clearAndSetModelConditionFlags(const BitFlags<320> &, const BitFlags<320> &);
#include "../GameLogic/Object/object.h"

void Object::clearAndSetModelConditionFlags(const BitFlags<320> &clear,
	const BitFlags<320> &set)
{
	ModelConditionFlags *cur = &m_modelConditionFlags;
	ModelConditionFlags oldFlags = m_modelConditionFlags;
	cur->clearAndSet(reinterpret_cast<const ModelConditionFlags &>(clear),
		reinterpret_cast<const ModelConditionFlags &>(set));
	if (oldFlags != *cur)
	{
		if (m_drawable)
			m_drawable->replaceModelConditionState(*cur, 0, 0);
		if (m_ai)
			m_ai->AIUpdateInterface::friend_notifyStateMachineChanged();
	}
}
