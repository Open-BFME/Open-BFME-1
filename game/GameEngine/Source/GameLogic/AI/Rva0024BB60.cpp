// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: Horde contain member notification, retail 0x0024BB60.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template <int NUMBITS>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, Int bitIndex)
	{
		m_bits.set(bitIndex);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class BfmeRvaBB60Object
{
public:
	char m_head[0x6c];
	char m_slot;
};

// Retail calls reach 0x00227B60 (ILT 0x0002CE44), 0x001C9AC0 (ILT
// 0x000122AB) and 0x001C7370 (ILT 0x000307E7); declared as those ledger
// rows name them.
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &, Bool);
};

class Gen001C9AC0
{
public:
	void handle(int value);
};

class Rva00227B60ContainDispatch
{
public:
	void dispatch(Object *object, bool value);
};

typedef Rva00227B60ContainDispatch BfmeRvaBB60View;

// retail 0x0024BB60 pushes the value before calling 0x009F2660, which
// tail-jumps to ?bfmeAddEQR@BfmeHostEQR@@QAEXPAXBfmeThingEQR@@@Z (a void* one).
// The matched ledger row names the callee ?m@Gen_009f2660@@QAEXXZ, so the call
// is made through that exact symbol with the forwarded argument.
class Gen_009f2660
{
public:
	void m(void);
};

typedef void (Gen_009f2660::*Gen009f2660WithSlot)(void *);

class PartitionManager;
extern PartitionManager *ThePartitionManager;

class Rva0024BB60
{
public:
	void notifyMember(BfmeRvaBB60Object *object);
};

void Rva0024BB60::notifyMember(BfmeRvaBB60Object *object)
{
	((BfmeRvaBB60View *)((char *)this + 0x20))->dispatch((Object *)object, false);

	void *value;
	if (object)
		value = (void *)&object->m_slot;
	else
		value = 0;

	(((Gen_009f2660 *)ThePartitionManager)
		->*(Gen009f2660WithSlot)&Gen_009f2660::m)(value);
	((Gen001C9AC0 *)object)->handle(0x14);
	((Object *)object)->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 3), false);
}
