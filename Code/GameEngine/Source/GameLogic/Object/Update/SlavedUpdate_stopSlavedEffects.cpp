// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Int;

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNSELECTABLE = 3
};

enum DisabledType
{
	DISABLED_HELD = 3
};

template <int Bits>
class BitFlags
{
public:
	enum InitType { kInit };

	BitFlags() {}

	BitFlags(InitType, Int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<Bits> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void clearStatus(const ObjectStatusMaskType &status)
	{
		setStatus(status, false);
	}
	Bool clearDisabled(DisabledType type);
};

struct Coord3D
{
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0;
		y = 0;
		z = 0;
	}
};

class SlavedUpdate
{
	// In the retail class this helper is private; keeping the access in the
	// declaration preserves its real decorated identity.
	private:
	void stopSlavedEffects();

	unsigned int m_unmodelled_00;
	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0c[0x24 - 0x0c];
	UnsignedInt m_slaver;
	Coord3D m_guardPointOffset;
};

// ?stopSlavedEffects@SlavedUpdate@@QAEXXZ
void SlavedUpdate::stopSlavedEffects()
{
	m_slaver = 0;
	__asm { }
	m_guardPointOffset.zero();
	m_object->clearStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_UNSELECTABLE));
	m_object->clearDisabled(DISABLED_HELD);
}
