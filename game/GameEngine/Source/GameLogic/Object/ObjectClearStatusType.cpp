// BFME 1.03 Object::clearStatus(ObjectStatusTypes) at RVA 0x00162CD0.

#include <string.h>

enum ObjectStatusTypes
{
	OBJECT_STATUS_DESTROYED = 0
};
typedef bool Bool;

template <int NUM_BITS> class BitFlags
{
public:
	BitFlags() { memset(m_bits, 0, sizeof(m_bits)); }
	void set(ObjectStatusTypes bit)
	{
		m_bits[(unsigned int)bit >> 5] |= 1U << ((unsigned int)bit & 31);
	}

private:
	unsigned int m_bits[(NUM_BITS + 31) / 32];
};

typedef BitFlags<86> ObjectStatusMaskType;

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void clearStatus(ObjectStatusTypes status);
};

void Object::clearStatus(ObjectStatusTypes status)
{
	ObjectStatusMaskType mask;
	mask.set(status);
	setStatus(mask, false);
}
