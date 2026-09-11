// BFME 1.03 Object::onRemovedFrom at RVA 0x001CBAE0.
//
// The canonical Object.cpp declaration and the named TunnelTracker caller
// establish the identity.  BFME removes the status mask supplied by the old
// container before clearing the containment fields.  This focused view reuses
// the Object status and containment layouts proven by ObjectStatusBits.cpp and
// ObjectOnContainedBy.cpp.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
public:
	__declspec(noinline) Bool operator!=(const BitFlags &other) const
	{
		return m_bits != other.m_bits;
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

class Object;

struct ContainmentStatus
{
	UnsignedInt m_bits[3];
};

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8c();
	virtual void slot90(); virtual void slot94(); virtual void slot98();
	virtual ContainmentStatus getStatus(const Object *object) const;
};

class PartitionData
{
public:
	void makeDirty();
};

class Object
{
public:
	void onRemovedFrom(Object *removedFrom);
	ContainModuleInterface *getContain() const { return m_contain; }
	__forceinline void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);
	__forceinline void clearStatus(ObjectStatusMaskType objectStatus);

private:
	void *m_vtable;
	void *m_template;
	unsigned char m_pad008[0x88];
	ObjectStatusMaskType m_status;
	unsigned char m_pad09c[0x160];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[0x14];
	Object *m_containedBy;
	unsigned char m_pad218[4];
	UnsignedInt m_containedByFrame;
	unsigned char m_pad220[0x125];
	unsigned char m_containedFlags;
	unsigned char m_pad346[0x6a];
	PartitionData *m_partitionData;
};

__forceinline void Object::setStatus(const ObjectStatusMaskType &objectStatus, Bool set)
{
	ObjectStatusMaskType &status = m_status;
	ObjectStatusMaskType oldStatus = status;

	if (set)
		status.set(objectStatus);
	else
		status.clear(objectStatus);

	if (status != oldStatus)
	{
		if (oldStatus.test(2) != m_status.test(2))
		{
			if (m_partitionData)
				m_partitionData->makeDirty();
		}
	}
}

__forceinline void Object::clearStatus(ObjectStatusMaskType objectStatus)
{
	setStatus(objectStatus, false);
}

// ?onRemovedFrom@Object@@QAEXPAV1@@Z
void Object::onRemovedFrom(Object *removedFrom)
{
	ContainModuleInterface *contain = removedFrom ? removedFrom->getContain() : 0;
	if (contain)
		clearStatus(reinterpret_cast<const ObjectStatusMaskType &>(
			contain->getStatus(this)));

	m_containedFlags &= ~1;
	m_containedBy = 0;
	m_containedByFrame = 0;
}
