// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
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

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);
};

class Rva00266EB0SiegeDeployBase
{
public:
	void transition(int value);
	void clearStatusBit63();

private:
	unsigned char m_pad00[8];
	Object *m_object;
	unsigned char m_pad0C[0x40 - 0x0C];
	unsigned m_field40;
};

// ?clearStatusBit63@Rva00266EB0SiegeDeployBase@@QAEXXZ
void Rva00266EB0SiegeDeployBase::clearStatusBit63()
{
	m_object->setStatus(MAKE_OBJECT_STATUS_MASK(63), false);
	transition(0);
	m_field40 = 0;
}
