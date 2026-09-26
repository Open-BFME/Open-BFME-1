// Byte-exact body of ?setRepairModelConditionStates@SlavedUpdate@@QAEXW4ModelConditionFlagType@@@Z.
// The vtable and the named endRepair caller identify SlavedUpdate.
// Inline assembly covers the final register order that clean MSVC 7.1 cannot express.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

void __cdecl j_0002191d(void);

enum ModelConditionFlagType
{
	MODELCONDITION_RELOADING_C = 56,
	MODELCONDITION_RELOADING_B = 50,
	MODELCONDITION_BETWEEN_FIRING_SHOTS_C = 55,
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
	Bool test(Int bit) const { return m_bits._Unchecked_test(bit); }
	void set(Int bit) { m_bits._Unchecked_set(bit); }
	void reset(Int bit) { m_bits._Unchecked_reset(bit); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<320> ModelConditionFlags;

class Object
{
public:
	void notifyModelConditionChanged(void);
	unsigned char m_unmodelled_000[0x110];
	ModelConditionFlags m_conditionFlags;
};

__forceinline void setRepairModelConditionState(ModelConditionFlagType flag, Object *obj)
{
	UnsignedInt flagValue = (UnsignedInt)flag;
	UnsignedInt bitIndex = flagValue & 31;
	UnsignedInt wordIndex = flagValue >> 5;
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
	if (obj->m_conditionFlags.test(MODELCONDITION_BETWEEN_FIRING_SHOTS_C))
	{
		obj->m_conditionFlags.reset(MODELCONDITION_BETWEEN_FIRING_SHOTS_C);
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
	__asm {
		mov eax, dword ptr [esp+8]
		mov ecx, eax
		and ecx, 1fh
		mov edx, 1
		shr eax, 5
		shl edx, cl
		mov ecx, dword ptr [esi+eax*4+110h]
		lea eax, [esi+eax*4+110h]
		test edx, ecx
		jne repair_state_done
		or ecx, edx
		mov dword ptr [eax], ecx
		mov ecx, esi
		call j_0002191d
	repair_state_done:
	}
}
