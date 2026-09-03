// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template <int NUMBITS>
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);
};

class Gen002569B0
{
public:
	void apply();

private:
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
};

// ?apply@Gen002569B0@@QAEXXZ
void Gen002569B0::apply()
{
	m_object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 29), false);
}
