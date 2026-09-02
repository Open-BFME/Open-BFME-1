// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Object::setStatus(MAKE_OBJECT_STATUS_MASK(bit), true) then store the
// argument at this+0x338 / this+0x33C.  Same 12-byte BitFlags<86> local
// ScriptActions_doNamedSetRepulsor.cpp already matches.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

template<int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

	BitFlags() { }

private:
	_STL::bitset<NUMBITS>	m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);

	void rva001CE6F0(Int value);
	void rva001CE740(Int value);

private:
	char m_pad[0x338];
	Int m_338;
	Int m_33C;
};

void Object::rva001CE6F0(Int value)
{
	setStatus(MAKE_OBJECT_STATUS_MASK(73), true);
	m_338 = value;
}

void Object::rva001CE740(Int value)
{
	setStatus(MAKE_OBJECT_STATUS_MASK(4), true);
	m_33C = value;
}
