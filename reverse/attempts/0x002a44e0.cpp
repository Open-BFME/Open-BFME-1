// ?setRepairModelConditionStates@SlavedUpdate@@QAEXW4ModelConditionFlagType@@@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// SlavedUpdate::setRepairModelConditionStates, retail 0x002A44E0.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum ModelConditionFlagType
{
	MODELCONDITION_RELOADING_C = 40,
	MODELCONDITION_RELOADING_B = 42,
	MODELCONDITION_BETWEEN_FIRING_SHOTS_C = 47,
	MODELCONDITION_BETWEEN_FIRING_SHOTS_B = 49,
	MODELCONDITION_FIRING_C = 52,
	MODELCONDITION_FIRING_B = 46,
	MODELCONDITION_PACKING = 93,
	MODELCONDITION_UNPACKING = 95
};

template<int NUMBITS>
class BitFlags
{
public:
	__forceinline Bool test(Int bit) const { return m_bits.test(bit); }
	__forceinline void set(Int bit) { m_bits.set(bit); }
	__forceinline void reset(Int bit) { m_bits.reset(bit); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<288> ModelConditionFlags;

class Object
{
public:
	void notifyModelConditionChanged(void);
	unsigned char m_unmodelled_000[0x110];
	ModelConditionFlags m_conditionFlags;
};

class SlavedUpdate
{
public:
	void setRepairModelConditionStates(ModelConditionFlagType flag);

private:
	Object *getObject(void) const { return m_object; }

	unsigned char m_unmodelled_000[8];
	Object *m_object;
};

// ?setRepairModelConditionStates@SlavedUpdate@@QAEXW4ModelConditionFlagType@@@Z
void SlavedUpdate::setRepairModelConditionStates(ModelConditionFlagType flag)
{
	Object *obj = getObject();
	if (obj->m_conditionFlags.test(MODELCONDITION_PACKING))
	{
		obj->m_conditionFlags.reset(MODELCONDITION_PACKING);
		obj->notifyModelConditionChanged();
	}
	if (obj->m_conditionFlags.test(MODELCONDITION_UNPACKING))
	{
		obj->m_conditionFlags.reset(MODELCONDITION_UNPACKING);
		obj->notifyModelConditionChanged();
	}
	if (obj->m_conditionFlags.test(MODELCONDITION_FIRING_B))
	{
		obj->m_conditionFlags.reset(MODELCONDITION_FIRING_B);
		obj->notifyModelConditionChanged();
	}
	if (obj->m_conditionFlags.test(MODELCONDITION_FIRING_C))
	{
		obj->m_conditionFlags.reset(MODELCONDITION_FIRING_C);
		obj->notifyModelConditionChanged();
	}
	if (obj->m_conditionFlags.test(MODELCONDITION_BETWEEN_FIRING_SHOTS_B))
	{
		obj->m_conditionFlags.reset(MODELCONDITION_BETWEEN_FIRING_SHOTS_B);
		obj->notifyModelConditionChanged();
	}
	volatile UnsignedInt *betweenFiringC = (volatile UnsignedInt *)&obj->m_conditionFlags + 1;
	if (*betweenFiringC & 0x00008000u)
	{
		*betweenFiringC &= 0xffff7fffu;
		obj->notifyModelConditionChanged();
	}
	if (obj->m_conditionFlags.test(MODELCONDITION_RELOADING_B))
	{
		obj->m_conditionFlags.reset(MODELCONDITION_RELOADING_B);
		obj->notifyModelConditionChanged();
	}
	if (obj->m_conditionFlags.test(MODELCONDITION_RELOADING_C))
	{
		obj->m_conditionFlags.reset(MODELCONDITION_RELOADING_C);
		obj->notifyModelConditionChanged();
	}
	UnsignedInt wordIndex = (UnsignedInt)flag >> 5;
	UnsignedInt bitIndex = (UnsignedInt)flag & 31;
	UnsignedInt mask = 1;
	mask <<= bitIndex;
	UnsignedInt *word = (UnsignedInt *)&obj->m_conditionFlags;
	word += wordIndex;
	if (!(*word & mask))
	{
		*word |= mask;
		obj->notifyModelConditionChanged();
	}
}
