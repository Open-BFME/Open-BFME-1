// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: focused clean C++ reconstruction of Object status mutation.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Int;

template <int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	Bool operator!=(const BitFlags &other) const;

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
	_STL::bitset<Bits> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectHelper.h
class ObjectHelper
{
public:
	void sleepUntil(UnsignedInt frame);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionData
{
public:
	void makeDirty();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unmodelled[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);

private:
	unsigned char m_unmodelled0[0x90];
	ObjectStatusMaskType m_status;
	unsigned char m_unmodelled1[0x138];
	ObjectHelper *m_repulsorHelper;
	unsigned char m_unmodelled2[0x1D8];
	PartitionData *m_partitionData;
};

// ?setStatus@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z
void Object::setStatus(const ObjectStatusMaskType &objectStatus, Bool set)
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
