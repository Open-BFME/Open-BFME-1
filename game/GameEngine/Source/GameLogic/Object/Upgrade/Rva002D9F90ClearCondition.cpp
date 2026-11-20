// ?clearConfiguredModelCondition@Rva002D9F90Behavior@@QAEXXZ
// The class names keep the address because the original owning class is unknown.
// These are partial field-access views, not recovered complete class sizes.
// BFME retail RVA 0x002D9F90. The owning behavior's lexical identity is not
// recovered; four matched callers reach this body through address-derived
// names. The layout and operation are explicit in the retail instructions:
// module-data +0x64 supplies a ModelConditionFlagType, owner +0x110 is the
// corresponding bit array, and a changed bit tail-calls the Object notifier.

// Existing ILT binding at RVA 0x0002191D; it forwards to the rowed
// Object::notifyModelConditionChanged body at 0x001BE1C0. This declaration
// preserves that recorded __thiscall/no-stack-argument ABI, not a new name.
class Object
{
public:
    void notifyModelConditionChanged();
};

typedef unsigned int UnsignedInt;

class Rva002D9F90Owner
{
public:

private:
	unsigned char m_pad[0x110];
	UnsignedInt m_modelConditionFlags[10];

	friend class Rva002D9F90Behavior;
};

struct Rva002D9F90ModuleData
{
	unsigned char m_pad[0x64];
	int m_condition;
};

class Rva002D9F90Behavior
{
public:
	void clearConfiguredModelCondition();

private:
	void *m_vtable;
	Rva002D9F90ModuleData *m_data;
	Rva002D9F90Owner *m_owner;
};

// ?clearConfiguredModelCondition@Rva002D9F90Behavior@@QAEXXZ
void Rva002D9F90Behavior::clearConfiguredModelCondition()
{
	Rva002D9F90Owner *owner = m_owner;
	Rva002D9F90ModuleData *data = m_data;
	if (owner == 0 || data == 0 || data->m_condition == -1)
		return;

	const UnsignedInt condition = static_cast<UnsignedInt>(data->m_condition);
	const UnsignedInt mask = 1u << (condition & 31);
	// The 32-bit unsigned mask is 1u shifted by 0..31, hence has one bit set.
	// The compiler hint is true for every possible condition; it adds no code.
	// It preserves retail TEST edx,eax instead of the otherwise reversed form.
	__assume((mask & (mask - 1u)) == 0);
	if (owner->m_modelConditionFlags[condition >> 5] & mask)
	{
		owner->m_modelConditionFlags[condition >> 5] &= ~mask;
		reinterpret_cast<Object *>(owner)->notifyModelConditionChanged();
	}
}
