// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

#include "../../../../Include/Common/ScalarTypes.h"


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

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

class ObjectV28
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual float *getFloatHost() = 0; // vtable+0x28
};

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);

	ObjectV28 *asV28() { return (ObjectV28 *)this; }
};

// The base step goes through ILT 0x0000F975, the ledger's 5-byte row
// ?j_0000f975@@YAXXZ (game/gen_small/thunks_007.cpp), jmp to 0x002A8540, as
// tools/callees.py prints for this body.  Nothing defines the pinned
// ?bfmeOneCRB@BfmeThingCRB@@QAEXPAX0@Z, so the call names the thunk through a
// raw pointer bridge that keeps the thiscall shape.
void j_0000f975();
class BfmeThingCRB
{
};

class Rva0026C8C0Owner : public BfmeThingCRB
{
public:
	void apply(void *a, void *b);

private:
	char m_pad00[8];
	Object *m_object;
};

// ?apply@Rva0026C8C0Owner@@QAEXPAX0@Z
void Rva0026C8C0Owner::apply(void *a, void *b)
{
	float *host = m_object->asV28()->getFloatHost();
	if (host != 0)
	{
		host = m_object->asV28()->getFloatHost();
		host[0xb0 / 4] = 1.0f;
	}
	m_object->setStatus(MAKE_OBJECT_STATUS_MASK(73), false);
	union
	{
		void (*raw)(void);
		void (BfmeThingCRB::*typed)(void *, void *);
	} oneCRB;
	oneCRB.raw = &j_0000f975;
	(this->*oneCRB.typed)(a, b);
}
