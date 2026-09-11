// cl: /O2 /Ob2 /G6 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

typedef unsigned int UnsignedInt;
typedef int Int;
typedef int ObjectID;
typedef bool Bool;

enum
{
	FALSE = 0,
	INVALID_ID = 0,
	BFME_MODELCONDITION_DOCKING = 80,
	BFME_MODELCONDITION_DOCKING_BEGINNING = 81,
	BFME_MODELCONDITION_DOCKING_ACTIVE = 82,
	BFME_MODELCONDITION_DOCKING_ENDING = 83
};

// BFME uses a 320-bit model-condition block.  The flat word view preserves
// BitFlags' value semantics while avoiding the later Zero Hour flag layout.
template <int Bits>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit
	};

	BitFlags(BogusInitType, Int bit)
	{
		memset(m_bits, 0, sizeof(m_bits));
		m_bits[bit / 32] |= 1U << (bit % 32);
	}

	__forceinline BitFlags(BogusInitType, Int bit1, Int bit2)
	{
		memset(m_bits, 0, sizeof(m_bits));
		m_bits[bit1 / 32] |= 1U << (bit1 % 32);
		m_bits[bit2 / 32] |= 1U << (bit2 % 32);
	}

private:
	UnsignedInt m_bits[Bits / 32];
};

typedef BitFlags<320> ModelConditionFlags;

#define MAKE_MODELCONDITION_MASK(bit) \
	ModelConditionFlags(ModelConditionFlags::kInit, (bit))
#define MAKE_MODELCONDITION_MASK2(bit1, bit2) \
	ModelConditionFlags(ModelConditionFlags::kInit, (bit1), (bit2))

class Object
{
public:
	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(
			reinterpret_cast<const char *>(this) + 0x74);
	}

	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
};

class DockUpdate
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void onExitReached(Object *docker);
	virtual void slot12();
	virtual void slot13();
	virtual Bool isDockOpen();

private:
	// This method is entered through the DockUpdateInterface subobject.  These
	// offsets are therefore relative to that secondary-base view of DockUpdate.
	char m_unmodelled004[0x5c];
	ObjectID m_activeDocker;
	Bool m_dockerInside;

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) - 0x18);
	}
};

// DockUpdateInterface vtable slot 11.  The neighboring pinned slot 10 is
// DockUpdate::onDockReached, and the body follows the canonical ZH transition
// with BFME's condition indices and object layout.
void DockUpdate::onExitReached(Object *docker)
{
	Object *me = getObject();
	me->clearAndSetModelConditionFlags(
		MAKE_MODELCONDITION_MASK2(BFME_MODELCONDITION_DOCKING_ACTIVE,
			BFME_MODELCONDITION_DOCKING),
		MAKE_MODELCONDITION_MASK(BFME_MODELCONDITION_DOCKING_ENDING));
	docker->clearAndSetModelConditionFlags(
		MAKE_MODELCONDITION_MASK2(BFME_MODELCONDITION_DOCKING_ACTIVE,
			BFME_MODELCONDITION_DOCKING),
		MAKE_MODELCONDITION_MASK(BFME_MODELCONDITION_DOCKING_ENDING));
	m_dockerInside = FALSE;

	ObjectID dockerID = docker->getID();
	if (dockerID == m_activeDocker)
		m_activeDocker = INVALID_ID;
	else if (isDockOpen())
	{
		// The retail release build retains the virtual condition evaluation
		// after compiling out the assertion guarded by this branch.
	}
}
