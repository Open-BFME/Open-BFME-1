// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME layout reconstruction for retail RVA 0x0017EEE0.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

enum WeaponSlotType
{
	RVA_0017EEE0_PRIMARY
};

class Weapon
{
};

template <int NUMBITS>
class BitFlags
{
	public:
		enum _dummy_kInit { kInit };

		BitFlags(_dummy_kInit, int index)
		{
			m_bits.set(index);
		}

	private:
		_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	void setStatus(const ObjectStatusMaskType &, bool);
};

class Rva0017EEE0TailTarget
{
public:
	void apply(void *);
};

extern void j_0003ca65();

void __stdcall Rva0017EEE0WeaponCondition(Object *object)
{
	WeaponSlotType slot = RVA_0017EEE0_PRIMARY;

	if (!object->getCurrentWeapon(&slot))
		return;

	object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 13), true);

	typedef void (Rva0017EEE0TailTarget::*TailCall)(void *);
	union { void *asVoid; TailCall asMember; } tailCast;
	tailCast.asVoid = (void *)j_0003ca65;
	(reinterpret_cast<Rva0017EEE0TailTarget *>(object)->*tailCast.asMember)(
		(char *)object + 0x38);
}
