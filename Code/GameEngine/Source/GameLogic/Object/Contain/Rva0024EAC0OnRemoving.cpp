// ?onRemoving@Rva0024EAC0@@UAEXPAVObject@@@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport
// Retail 0x0024EAC0/48. The secondary vtable at 0x010B0F40, installed at
// module +0x20 by the adjacent constructor, points slot 18 (+0x48) through
// ILT 0x000282D1 to this body. The corresponding
// GarrisonContain slot names onRemoving(Object *) and reaches the base body
// through ILT 0x00005C22. This body calls that same ILT before setting the
// owner's model condition bit 10 and notifying through ILT 0x0002191D.
// The exact declaring class is unsettled: existing ctor/dtor ledger rows
// assign this same vtable to SlaughterHordeContain and its Base. The owner
// therefore keeps its address token while the slot-proven method is named.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

class ModelConditionFlags
{
public:
	bool test(int bit) const { return m_bits.test(bit); }
	void set(int bit) { m_bits.set(bit); }

private:
	_STL::bitset<320> m_bits;
};

class Object
{
public:
	void notifyModelConditionChanged();
	unsigned char m_bfmeHeadAZ[0x110];
	ModelConditionFlags m_modelConditionFlags;
};

// This TU models the secondary interface pointer accepted at +0x20.
class GarrisonContain
{
public:
	virtual void onRemoving(Object *object);
};

class Rva0024EAC0 : public GarrisonContain
{
public:
	virtual void onRemoving(Object *object);
};

void Rva0024EAC0::onRemoving(Object *object)
{
	GarrisonContain::onRemoving(object);

	// The secondary interface's this-0x18 is the owner Object* at module +0x08.
	Object *owner = *(Object **)((char *)this - 0x18);
	if (!owner->m_modelConditionFlags.test(10))
	{
		owner->m_modelConditionFlags.set(10);
		owner->notifyModelConditionChanged();
	}
}
