// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <hash_map>
#include <vector>

typedef unsigned int UnsignedInt;
typedef int Int;
typedef int ObjectID;
typedef bool Bool;

enum
{
	FALSE = 0,
	TRUE = 1,
	INVALID_ID = 0
};

template <int Bits>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit
	};

	BitFlags()
	{
	}

	BitFlags(BogusInitType, Int bit1, Int bit2, Int bit3, Int bit4)
	{
		m_bits.set(bit1);
		m_bits.set(bit2);
		m_bits.set(bit3);
		m_bits.set(bit4);
	}

	void set(Int bit)
	{
		m_bits.set(bit);
	}

	void reset()
	{
		m_bits.reset();
	}

private:
	_STL::bitset<Bits> m_bits;
};

typedef BitFlags<320> ModelConditionFlags;

class Object
{
public:
	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(reinterpret_cast<const char *>(this) + 0x74);
	}

	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
};

struct ObjectIDNode
{
	ObjectIDNode *m_next;
	ObjectID m_id;
	Object *m_object;
};

struct ObjectIDBuckets
{
	UnsignedInt m_unused;
	ObjectIDNode **m_begin;
	ObjectIDNode **m_end;

	UnsignedInt size() const
	{
		return static_cast<UnsignedInt>(m_end - m_begin);
	}

	ObjectIDNode *operator[](UnsignedInt index) const
	{
		return m_begin[index];
	}
};

class Rva00367E30Logic
{
public:
	__forceinline ObjectIDNode *find(ObjectID id)
	{
		UnsignedInt bucketCount = m_buckets.size();
		ObjectIDNode *node = m_buckets[id % bucketCount];
		for (; node != 0 && node->m_id != id; node = node->m_next)
		{
		}
		return node;
	}

	__forceinline ObjectIDNode *end()
	{
		return 0;
	}

	__forceinline Object *findObjectByID(ObjectID id)
	{
		if (id == INVALID_ID)
			return 0;

		ObjectIDNode *it = find(id);
		if (it == end())
			return 0;

		return it->m_object;
	}

	public:
	char m_slice_pad[0xB0];
	ObjectIDBuckets m_buckets;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class DockUpdateStorage
{
public:
	void removeApproachPosition(Int index);
};

typedef _STL::vector<ObjectID> ObjectIDVector;

class DockUpdate
{
public:
	virtual void cancelDock(Object *docker);

private:
	char m_unmodelled_004[0x3C];
	ObjectIDVector m_approachPositionOwners;
	char m_unmodelled_04C[0x14];
	ObjectID m_activeDocker;
	Bool m_dockerInside;

	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(reinterpret_cast<const char *>(this) - 0x18);
	}
};

struct DockModelConditionMasks
{
	ModelConditionFlags clear;
	ModelConditionFlags set;

	void resetSet()
	{
		set.reset();
	}
};

// ?cancelDock@DockUpdate@@UAEXPAVObject@@@Z
void DockUpdate::cancelDock(Object *docker)
{
	ObjectID dockerID = docker->getID();
	for (Int positionIndex = 0; positionIndex < m_approachPositionOwners.size(); ++positionIndex)
	{
		if (m_approachPositionOwners[positionIndex] == dockerID)
		{
			reinterpret_cast<DockUpdateStorage *>(reinterpret_cast<char *>(this) - 0x20)->removeApproachPosition(positionIndex);
			break;
		}
	}

	if (m_activeDocker == dockerID)
	{
		Object *dockingObject;
		if (m_activeDocker == INVALID_ID)
			dockingObject = 0;
		else
		{
			dockingObject = TheBfmeGameLogic->findObjectByID(m_activeDocker);
		}
		m_activeDocker = INVALID_ID;
		m_dockerInside = FALSE;
		DockModelConditionMasks masks = {
			ModelConditionFlags(ModelConditionFlags::kInit, 80, 81, 82, 83),
			ModelConditionFlags()
		};
		getObject()->clearAndSetModelConditionFlags(masks.clear, masks.set);
		if (dockingObject)
		{
			masks.resetSet();
			dockingObject->clearAndSetModelConditionFlags(masks.clear, masks.set);
		}
	}
}
