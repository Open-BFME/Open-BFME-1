// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template<int Bits>
class BitFlags
{
public:
	Bool test(Int bit) const { return m_bits.test(bit); }
	void set(Int bit) { m_bits.set(bit); }
	void reset(Int bit) { m_bits.reset(bit); }

private:
	_STL::bitset<Bits> m_bits;
};

class Object
{
public:
	void notifyModelConditionChanged(void);

	unsigned char m_unmodelled000[0x110];
	BitFlags<288> m_modelConditionFlags;
};

static __forceinline void applyDockCondition(Object *object)
{
	if (object->m_modelConditionFlags.test(81) ||
		!object->m_modelConditionFlags.test(82))
	{
		object->m_modelConditionFlags.reset(81);
		object->m_modelConditionFlags.set(82);
		object->notifyModelConditionChanged();
	}
}

class DockUpdate
{
public:
	virtual void onDockReached(Object *docker);
};

void DockUpdate::onDockReached(Object *docker)
{
	applyDockCondition(*(Object **)((char *)this - 0x18));
	applyDockCondition(docker);
}
