// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1

#include <bitset>

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Int;

enum ObjectID
{
	INVALID_ID = 0
};

enum MobStates
{
	MOB_STATE_NONE = 0
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

	BitFlags(InitType, Int bit, const void *anchor)
	{
		m_bits.set(bit);
		__asm { }
	}

	void set(Int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<Bits> m_bits;
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNSELECTABLE = 3
};

enum DisabledType
{
	DISABLED_HELD = 3
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

class DamageInfo;

class MobMemberSlavedUpdateState
{
public:
	virtual void stateSlot();

protected:
	ObjectID m_slaver;
	Int m_framesToWait;
	MobStates m_mobState;
	UnsignedInt m_personalColor;
};

class MobMemberSlavedUpdate : public MobMemberSlavedUpdateState
{
public:
	virtual void onSlaverDie(const DamageInfo *info);
	Object *getObject()
	{
		return *(Object **)((unsigned char *)this - 0x18);
	}

};

void MobMemberSlavedUpdate::onSlaverDie(const DamageInfo *info)
{
	ObjectID *slaver = &m_slaver;
	*slaver = INVALID_ID;
	m_framesToWait = 0;
	m_mobState = MOB_STATE_NONE;
	m_personalColor = 0;
	ObjectStatusMaskType status;
	status.set(OBJECT_STATUS_UNSELECTABLE);
	getObject()->setStatus(status, false);
	getObject()->clearDisabled(DISABLED_HELD);
}
