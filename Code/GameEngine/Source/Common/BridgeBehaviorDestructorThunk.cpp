// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// BFME's BridgeBehavior destructor uses the hash-map object lookup and the
// 0x70-byte AudioEventRTS layout. The reference headers use the later vector
// lookup and a 0x64-byte audio event, so this file keeps the retail ABI slices
// local to the destructor reconstruction.

#define _STLP_USE_NEWALLOC 1
#include <hash_map>
#include <list>

#pragma comment(linker, "/alternatename:??1BfmeAudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")

typedef int ObjectID;
class Object;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class Gen_dtor_00113d40
{
public:
	virtual ~Gen_dtor_00113d40();

private:
	const void *m_moduleData;
};

class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

class ObjectModule : public Gen_dtor_00113d40
{
private:
	void *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule() {}

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class BridgeBehaviorInterface
{
public:
	virtual void setTower(int towerType, Object *tower) = 0;
	virtual ObjectID getTowerID(int towerType) = 0;
	virtual void createScaffolding() = 0;
	virtual void removeScaffolding() = 0;
	virtual bool isScaffoldInMotion() = 0;
	virtual bool isScaffoldPresent() = 0;
};

class DamageModuleInterface
{
public:
	virtual void onDamage(void *damageInfo) = 0;
	virtual void onHealing(void *damageInfo) = 0;
	virtual void onBodyDamageStateChange(const void *damageInfo, int oldState, int newState) = 0;
};

class DieModuleInterface
{
public:
	virtual void onDie(const void *damageInfo) = 0;
};

class BfmeAudioEventRTS
{
public:
	~BfmeAudioEventRTS();

	unsigned char m_unreconstructed_00[0x70];
};

extern void __stlp_deallocate_small(void *node, unsigned int bytes);

template <class T>
class BridgeScaffoldAllocator : public _STL::allocator<T>
{
public:
	template <class U> struct rebind { typedef BridgeScaffoldAllocator<U> other; };

	BridgeScaffoldAllocator() {}
	template <class U> BridgeScaffoldAllocator(const BridgeScaffoldAllocator<U> &) {}

	T *allocate(unsigned int count, const void * = 0) const
	{
		return (T *)_STL::nodeAllocate(count * sizeof(T));
	}

	void deallocate(T *node, unsigned int count) const
	{
		if (node)
			__stlp_deallocate_small(node, count * sizeof(T));
	}
};

template <class T, class U>
BridgeScaffoldAllocator<U> &__stl_alloc_rebind(
	BridgeScaffoldAllocator<T> &allocator, const U *)
{
	return (BridgeScaffoldAllocator<U> &)allocator;
}

typedef _STL::list<ObjectID, BridgeScaffoldAllocator<ObjectID> > BridgeScaffoldList;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;

		return (*it).second;
	}

	void destroyObject(Object *object);

private:
	char m_slice_pad[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class BridgeBehavior
	: public UpdateModule,
	  public BridgeBehaviorInterface,
	  public DamageModuleInterface,
	  public DieModuleInterface
{
public:
	virtual ~BridgeBehavior();
	virtual ObjectID getTowerID(int towerType)
	{
		if (towerType < 0 || towerType >= 4)
			return 0;
		return m_towerID[towerType];
	}

private:
	ObjectID m_towerID[4];
	const void *m_damageToOCL[4][3];
	const void *m_damageToFX[4][3];
	BfmeAudioEventRTS m_damageToSound[4];
	const void *m_repairToOCL[4][3];
	const void *m_repairToFX[4][3];
	BfmeAudioEventRTS m_repairToSound[4];
	bool m_fxResolved;
	bool m_scaffoldPresent;
	BridgeScaffoldList m_scaffoldObjectIDList;
	unsigned int m_deathFrame;
};

BridgeBehavior::~BridgeBehavior()
{
	for (int i = 0; i < 4; ++i)
	{
		Object *tower = TheGameLogic->findObjectByID(getTowerID(i));
		if (tower)
			TheGameLogic->destroyObject(tower);
	}
}
