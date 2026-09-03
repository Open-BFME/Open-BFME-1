// Focused ABI reconstruction for the two adjacent object-status wrappers.
// cl: /O2 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template<int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set = true);
};

class Rva002D81StatusOwner
{
public:
	void setStatus18();
	void clearStatus18();
};

void Rva002D81StatusOwner::setStatus18()
{
	Object *object = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
	object->setStatus(MAKE_OBJECT_STATUS_MASK(18), true);
}

void Rva002D81StatusOwner::clearStatus18()
{
	Object *object = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
	object->setStatus(MAKE_OBJECT_STATUS_MASK(18), false);
}
