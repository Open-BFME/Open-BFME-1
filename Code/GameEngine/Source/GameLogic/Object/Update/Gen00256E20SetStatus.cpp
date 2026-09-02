// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template <int NUMBITS>
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

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);
};

class Gen00256E20
{
public:
	unsigned int apply();
};

// ?apply@Gen00256E20@@QAEIXZ
unsigned int Gen00256E20::apply()
{
	Object *obj = *(Object **)((char *)this - 8);
	obj->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 8), false);
	return 0x3FFFFFFF;
}
