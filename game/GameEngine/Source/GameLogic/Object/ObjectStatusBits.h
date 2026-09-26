#ifndef GAMELOGIC_OBJECT_STATUS_BITS_H
#define GAMELOGIC_OBJECT_STATUS_BITS_H

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

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

	Bool operator!=(const BitFlags &other) const;

	void set(Int index)
	{
		m_bits._Unchecked_set(index);
	}

	void set(const BitFlags &other)
	{
		m_bits |= other.m_bits;
	}

	void clear(const BitFlags &other)
	{
		m_bits &= ~other.m_bits;
	}

	Bool test(Int index) const
	{
		return m_bits.test(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

class ObjectHelper
{
public:
	void sleepUntil(UnsignedInt frame);
};

class PartitionData
{
public:
	void makeDirty();
};

class GameLogic
{
public:
	unsigned char m_unmodelled[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	__declspec(noinline) void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);
	void setStatusBit(Int bit, Bool set);
	void rva001CE6F0(Int value);
	void rva001CE740(Int value);

private:
	unsigned char m_unmodelled000[0x90];
	ObjectStatusMaskType m_status;
	unsigned char m_unmodelled09c[0x1d4 - 0x9c];
	ObjectHelper *m_repulsorHelper;
	unsigned char m_unmodelled1d8[0x338 - 0x1d8];
	Int m_338;
	Int m_33c;
	unsigned char m_unmodelled340[0x3b0 - 0x340];
	PartitionData *m_partitionData;
};

// ?setStatus@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z
inline __declspec(noinline) void Object::setStatus(const ObjectStatusMaskType &objectStatus, Bool set)
{
	ObjectStatusMaskType &status = m_status;
	ObjectStatusMaskType oldStatus = status;

	if (set)
	{
		status.set(objectStatus);
	}
	else
	{
		status.clear(objectStatus);
	}

	if (status != oldStatus)
	{
		if (set && objectStatus.test(8) && m_repulsorHelper)
		{
			m_repulsorHelper->sleepUntil(TheGameLogic->m_frame + 10);
		}

		if (oldStatus.test(2) != m_status.test(2))
		{
			if (m_partitionData)
			{
				m_partitionData->makeDirty();
			}
		}
	}
}

#endif
