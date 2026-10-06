// StealthUpgrade, UpgradeMux table 0x010CDD58 (stored at +0x10 by the registered constructor
// 0x002D8000):
//   slot 9 -> 0x002D8170 StealthUpgrade::upgradeImplementation (ILT 0x0000E304, sole image ref)
//   slot 7 -> 0x002D81B0 StealthUpgrade::removeUpgrade (ILT 0x000361B5, sole image ref); slot 7 is
//            EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot), undoing slot 9.
// Evidence: targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md
// Slot 9 is the upgradeImplementation call in UpgradeMux::attemptUpgrade
// (0x002D9AD0). Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md
// Focused ABI reconstruction for the two adjacent object-status wrappers.
// cl: /O2 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template<int NUMBITS>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set = true);
};

class StealthUpgrade
{
protected:
	virtual void upgradeImplementation();
public:
	virtual void removeUpgrade();
};

void StealthUpgrade::upgradeImplementation()
{
	Object *object = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
	object->setStatus(MAKE_OBJECT_STATUS_MASK(18), true);
}

void StealthUpgrade::removeUpgrade()
{
	Object *object = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
	object->setStatus(MAKE_OBJECT_STATUS_MASK(18), false);
}
