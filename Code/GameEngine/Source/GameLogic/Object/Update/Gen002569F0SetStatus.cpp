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

class Gen_001BF4F0
{
public:
	void bfmeForward(void *obj);
};

class Gen002569F0
{
public:
	void apply(Gen_001BF4F0 *arg);

private:
	void *m_vtable;
	void *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x14];
	void *m_field20;
};

// ?apply@Gen002569F0@@QAEXPAVGen_001BF4F0@@@Z
void Gen002569F0::apply(Gen_001BF4F0 *arg)
{
	if (!arg)
		return;
	if (!m_field20)
		return;
	Object *obj = m_object;
	m_field20 = 0;
	arg->bfmeForward(obj);
	m_object->setStatus(ObjectStatusMaskType(ObjectStatusMaskType::kInit, 29), false);
}
