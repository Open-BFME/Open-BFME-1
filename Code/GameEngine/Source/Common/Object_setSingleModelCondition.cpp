// cl: /DNDEBUG /MD /Gy /O2 /Ob1
// Object helper at 0x000F2150 (71B): BitFlags local, set one bit, forward.

typedef int Int;
typedef unsigned int UnsignedInt;
#include <string.h>

template<int NUMBITS>
class BitFlags
{
public:
	BitFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

	void set(Int idx)
	{
		m_bits[(unsigned)idx >> 5] |= 1u << (idx & 31);
	}

	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<96> ModelConditionFlags;

class Object
{
public:
	void unidentified_0002181E(const ModelConditionFlags &flags, Int arg);
	void setSingleModelCondition(Int bit);
};

void Object::setSingleModelCondition(Int bit)
{
	ModelConditionFlags flags;
	flags.set(bit);
	unidentified_0002181E(flags, 0);
}
