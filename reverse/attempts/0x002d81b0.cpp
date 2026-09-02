// ?clearStatus@Rva002D81B0StatusOwner@@QAEXXZ
// partial score=0.9 date=2026-09-01
// cl: /O2 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef bool Bool;

template<int NUMBITS>
class BitFlags
{
public:
	void set(unsigned int bit) { m_bits.set(bit); }

private:
	std::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set = true);
};

class Rva002D81B0StatusOwner
{
public:
	void clearStatus();
};

void Rva002D81B0StatusOwner::clearStatus()
{
	ObjectStatusMaskType status;
	status.set(18);
	Object *object = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) - 8);
	object->setStatus(status, false);
}
