// ?setStatusBit@Object@@QAEXH_N@Z
// partial score=0.95 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Object helper that builds a single-bit BitFlags<86> mask and
// forwards it to Object::setStatus. Retail 0x000D3EB0, 68 bytes.
// Near-miss: first zero then this/bit then remaining zeros (9B register schedule).

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Int;

struct ObjectStatusMaskType
{
	UnsignedInt m_bits[3];
};

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
	volatile UnsignedInt *p = mask.m_bits;
	*p = 0;
	++p;
	*p = 0;
	Object *self = this;
	UnsignedInt index = (UnsignedInt)bit;
	++p;
	*p = 0;
	mask.m_bits[index >> 5] |= 1U << (index & 31);
	self->setStatus(mask, set);
}
