// Retail 0x0026D8A0: SpecialAbilityUpdate sets one Object status bit.
// The clear twin at 0x0026D950 uses the same module-data selector and notify call.
// ObjectStatusMaskType places the status words at Object+0x12C.

// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

extern void j_00017d5f(void);

template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags() { }

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

	void set(Int index)
	{
		m_bits._Unchecked_set(index);
	}

	Bool test(Int index) const
	{
		return m_bits.test(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object
{
public:
	void notifyModelConditionChanged(void);

	char m_pad[0x12c];
	ObjectStatusMaskType m_status;
};

class SpecialAbilityUpdateModuleData
{
public:
	char m_pad[0x258];
	int m_which;
	unsigned char m_flag25c;
};

class SpecialAbilityUpdate
{
public:
	void setAbilityBits(void);

private:
	void *m_vtable;
	SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_obj;
	char m_pad0C[0x18];
	void *m_field24;
};

// ?setAbilityBits@SpecialAbilityUpdate@@QAEXXZ
void SpecialAbilityUpdate::setAbilityBits(void)
{
	j_00017d5f();
	SpecialAbilityUpdateModuleData *md = m_moduleData;
	Object *obj = m_obj;
	if (md->m_flag25c && m_field24)
		return;
	switch (md->m_which)
	{
	case 3:
		if (obj->m_status.test(11))
			return;
		obj->m_status.set(11);
		obj->notifyModelConditionChanged();
		return;
	case 2:
		if (obj->m_status.test(10))
			return;
		obj->m_status.set(10);
		obj->notifyModelConditionChanged();
		return;
	case 1:
		if (obj->m_status.test(9))
			return;
		obj->m_status.set(9);
		obj->notifyModelConditionChanged();
		return;
	}
}
