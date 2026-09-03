// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: Horde contain member notification, retail 0x0024BB60.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template <int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, Int index)
	{
		m_bits.set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class BfmeRvaBB60Object
{
public:
	void action(int value);
	void setStatus(const ObjectStatusMaskType &, Bool);

	char m_head[0x6c];
	char m_slot;
};

class BfmeRvaBB60View
{
public:
	void dispatch(BfmeRvaBB60Object *object, int value);
};

class BfmeRvaBB60Manager
{
public:
	void notify(void *value);
};

class Rva0024BB60
{
public:
	void notifyMember(BfmeRvaBB60Object *object);
};

void Rva0024BB60::notifyMember(BfmeRvaBB60Object *object)
{
	((BfmeRvaBB60View *)((char *)this + 0x20))->dispatch(object, 0);

	void *value;
	if (object)
		value = (void *)&object->m_slot;
	else
		value = 0;

	((BfmeRvaBB60Manager *)*(void **)0x012ED5B8)->notify(value);
	object->action(0x14);
	object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 3), false);
}
