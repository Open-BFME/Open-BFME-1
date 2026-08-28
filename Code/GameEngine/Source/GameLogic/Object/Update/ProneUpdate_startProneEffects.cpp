// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: ProneUpdate::startProneEffects, retail 0x002A0030, 73 bytes.
//
// The reference's two lines, both moved onto the object:
//
//   - setModelConditionState is not a drawable call any more.  The object owns
//     the condition flags at +0x110 (Object_notifyModelConditionChanged.cpp
//     measured them) and the setter is inline: test the bit, set it, and notify
//     only when it was not already set.  The prone bit is 70 -- word 2, mask
//     0x40 -- which is not the reference's index for it.
//   - setStatus takes the mask by const reference and a set flag, so the
//     one-bit ObjectStatusMaskType is built in a 12-byte local here.  Bit 5 is
//     OBJECT_STATUS_NO_ATTACK counted without the reference's
//     OBJECT_STATUS_NONE, which is not a bit.
//
// Both flag words are the reference's BitFlags, which is a bitset wrapper --
// that is where the mask-in-a-register test and the read-modify-write come
// from, and spelling the bits by hand does not reach either.
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;

enum ModelConditionFlagType
{
	MODELCONDITION_PRONE = 70
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_NO_ATTACK = 5
};

template<int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

	BitFlags() { }

	Bool test(Int idx) const { return m_bits.test(idx); }
	void set(Int idx) { m_bits.set(idx); }

private:
	_STL::bitset<NUMBITS>	m_bits;
};

typedef BitFlags<288> ModelConditionFlags;
typedef BitFlags<86> ObjectStatusMaskType;			// 86: the setStatus body sanitizes its top word with 0x3FFFFF

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged(void);				// ILT 0x0002191D
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set = true);	// ILT 0x000307E7

	void setModelConditionState(ModelConditionFlagType bit)
	{
		if (!m_conditionFlags.test(bit))
		{
			m_conditionFlags.set(bit);
			notifyModelConditionChanged();
		}
	}

private:
	unsigned char m_unmodelled_000[0x110];
	ModelConditionFlags m_conditionFlags;				// +0x110
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProneUpdate.h
class ProneUpdate
{
private:
	void startProneEffects(void);

	Object *getObject(void) const { return m_object; }

	unsigned char m_unmodelled_000[8];
	Object *m_object;						// +0x08
};

void ProneUpdate::startProneEffects()
{
	Object *me = getObject();
	me->setModelConditionState( MODELCONDITION_PRONE );
	me->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_NO_ATTACK ) );
}
