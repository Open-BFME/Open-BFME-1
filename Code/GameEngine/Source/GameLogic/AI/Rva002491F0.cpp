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

class BfmeRva491F0View
{
public:
	void update(void *, int);
};

class BfmeRva491F0Object
{
public:
	void activate(void);
	void setStatus(const ObjectStatusMaskType &, Bool);

	char m_head[0x368];
	unsigned char m_active;
};

class Rva002491F0
{
public:
	void apply(BfmeRva491F0Object *);
};

void Rva002491F0::apply(BfmeRva491F0Object *member)
{
	((BfmeRva491F0View *)((char *)this + 0x20))->update(member, 0);
	if (!member->m_active)
		member->activate();

	member->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 3), false);
}
