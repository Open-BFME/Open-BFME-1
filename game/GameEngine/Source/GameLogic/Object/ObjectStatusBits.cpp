// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Everything that moves Object's status mask at +0x90:
//
//   setStatus     0x001C7370  the one mutator; set or clear a whole mask
//   setStatusBit  0x000D3EB0  build a one-bit mask and forward
//   rva001CE6F0   0x001CE6F0  set bit 73, then store a value at +0x338
//   rva001CE740   0x001CE740  set bit 4,  then store a value at +0x33C
//
// plus the two out-of-line template bodies setStatus' own compiland emits,
// BitFlags<86>::clear (0x001C60B0) and _STL::bitset<86>::operator~ (0x001C4BF0).
//
// The mask is 86 bits in three dwords, and retail says so in the open: every
// clear path sanitises the top word with 0x3FFFFF, which is 22 bits, and
// 64 + 22 = 86.  All four bodies agreed on that much.  What they did not agree on
// was BitFlags itself -- three files, three class definitions, no two alike:
//
//   setStatus     operator!=, set(const BitFlags&), clear(const BitFlags&), test(Int)
//   setStatusBit  a default ctor and set(Int) over bitset::_Unchecked_set
//   rva001CE6F0   a default ctor and a kInit ctor that sets one index
//
// They are one class.  It is written once below with all six members, and each
// body uses the ones it needs; MSVC emits a COMDAT only for what is used, which
// is why merging them does not add a body the ledger has no row for.
//
// Object drifted too.  setStatus placed m_status at +0x90 and reached
// m_repulsorHelper (+0x1D4) and m_partitionData (+0x3B0) behind two blind pads;
// the other file knew nothing above +0x338 and reached its own two fields behind
// a third.  All five members are named here in one list, so the pads between them
// are the only thing left unmodelled.
//
// The bit indices are retail's, read off the masks the two small bodies build:
// `or eax,0x200` into word 2 is bit 73, `or eax,0x10` into word 0 is bit 4.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectHelper.h
class ObjectHelper
{
public:
	void sleepUntil(UnsignedInt frame);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionData
{
public:
	void makeDirty();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned char m_unmodelled[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);
	void setStatusBit(Int bit, Bool set);
	void rva001CE6F0(Int value);
	void rva001CE740(Int value);

private:
	unsigned char m_unmodelled000[0x90];
	ObjectStatusMaskType m_status;			// +0x090, three dwords
	unsigned char m_unmodelled09c[0x1d4 - 0x9c];
	ObjectHelper *m_repulsorHelper;			// +0x1D4
	unsigned char m_unmodelled1d8[0x338 - 0x1d8];
	Int m_338;					// +0x338, written after status bit 73
	Int m_33c;					// +0x33C, written after status bit 4
	unsigned char m_unmodelled340[0x3b0 - 0x340];
	PartitionData *m_partitionData;			// +0x3B0
};

// ?setStatus@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z
//
// The old mask is snapshotted before the change and both later tests read it, so
// it stays a by-value local rather than being re-read.
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

// ?setStatusBit@Object@@QAEXH_N@Z
//
// The single bit goes in with bitset::_Unchecked_set, which is one
// `or [mem],reg`; the checked spelling costs a load, an or and a store.
void Object::setStatusBit(Int bit, Bool set)
{
	ObjectStatusMaskType mask;
	mask.set(bit);
	setStatus(mask, set);
}

// ?rva001CE6F0@Object@@QAEXH@Z
void Object::rva001CE6F0(Int value)
{
	setStatus(MAKE_OBJECT_STATUS_MASK(73), true);
	m_338 = value;
}

// ?rva001CE740@Object@@QAEXH@Z
void Object::rva001CE740(Int value)
{
	setStatus(MAKE_OBJECT_STATUS_MASK(4), true);
	m_33c = value;
}
