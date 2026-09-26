// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
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

class BfmeThingCRB
{
public:
	void bfmeOneCRB(void *a, void *b);
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
	bfmeOneCRB(a, b);
}
