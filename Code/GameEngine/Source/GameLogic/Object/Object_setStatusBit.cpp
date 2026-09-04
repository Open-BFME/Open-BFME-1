// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: Object helper that builds a single-bit BitFlags<86> mask and
// forwards it to Object::setStatus. Retail 0x000D3EB0, 68 bytes.
// Near-miss: first zero then this/bit then remaining zeros (9B register schedule).

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Int;

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

template <int NUMBITS>
class BitFlags
{
public:
	BitFlags()
	{
	}

	void set(Int index)
	{
		m_bits._Unchecked_set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatusBit(Int bit, Bool set);
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);
};

void Object::setStatusBit(Int bit, Bool set)
{
	ObjectStatusMaskType mask;
	mask.set(bit);
	setStatus(mask, set);
}
