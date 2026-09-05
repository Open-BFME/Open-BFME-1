// ?processDestroyList@GameLogic@@AAEXXZ
// partial score=0.9 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /MD /O2 /D_STLP_USE_STATIC_LIB
// stlport
// BFME 1.03 GameLogic::processDestroyList at RVA 0x0038AE90.
// The retail body uses four phase heaps and one inactive-update vector.  These
// TU-local layouts keep the BFME offsets without changing the Zero Hour header.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include <vector>

class UpdateModuleInterface;

class ObjectModule
{
public:
	virtual void objectModuleSlot00(void);

private:
	int m_objectModule04;
	int m_objectModule08;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot00(void);
	virtual void behaviorSlot04(void);
	virtual void behaviorSlot08(void);
	virtual void behaviorSlot0C(void);
	virtual void behaviorSlot10(void);
	virtual void behaviorSlot14(void);
	virtual void behaviorSlot18(void);
	virtual void behaviorSlot1C(void);
	virtual UpdateModuleInterface *getUpdate(void);
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update(void);
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	int friend_getIndexInLogic(void) const { return m_indexInLogic; }
	int friend_getPhaseInLogic(void) const { return m_phaseInLogic; }
	void friend_setIndexInLogic(int index) { m_indexInLogic = index; }
	void friend_setPhaseInLogic(int phase) { m_phaseInLogic = phase; }

	int m_nextCallFrame;					// +0x14
	int m_indexInLogic;					// +0x18
	int m_phaseInLogic;					// +0x1C
};

class Object
{
public:
	virtual void objectSlot00(void);
	virtual void objectSlot04(void);
	virtual void objectSlot08(void);
	virtual void objectSlot0C(void);
	virtual void objectSlot10(void);
	virtual void objectSlot14(void);
	virtual void objectSlot18(void);
	virtual ~Object(void);					// scalar deleting destructor at +0x1C

	void removeFromList(Object **head, Object **tail);

	char m_beforeID[0x70];
	int m_id;							// +0x74
	char m_beforeBehaviorModules[0x178];
	BehaviorModule **m_behaviorModules;		// +0x1F0
};

class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *object);
};

class AI
{
private:
	char m_beforePathfinder[0x0C];

public:
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectHash;

typedef _STL::vector<UpdateModule *> UpdateVector;

class GameLogic
{
private:
	void processDestroyList(void);

	char m_beforeObjectList[0xA8];
	Object *m_objectList;					// +0x0A8
	Object *m_objectListTail;				// +0x0AC
	ObjectHash m_objectHash;				// +0x0B0
	UpdateVector m_phaseUpdates[4];			// +0x0C4
	UpdateVector m_inactiveUpdates;			// +0x0F4
	UpdateModule *m_currentUpdate;			// +0x100
	_STL::list<Object *> m_objectsToDestroy;		// +0x104
};

void GameLogic::processDestroyList(void)
{
	for (_STL::list<Object *>::iterator iterator = m_objectsToDestroy.begin();
		 iterator != m_objectsToDestroy.end(); ++iterator)
	{
		Object *currentObject = *iterator;
		for (BehaviorModule **behavior = currentObject->m_behaviorModules;
			 *behavior; ++behavior)
		{
			UpdateModule *update = (UpdateModule *)((*behavior)->getUpdate());
			if (update)
			{
				if (update && update->friend_getIndexInLogic() != -1)
				{
					int index = update->friend_getIndexInLogic();
					int phase = update->friend_getPhaseInLogic();
					update->friend_setPhaseInLogic(-1);
					update->friend_setIndexInLogic(-1);

					if (phase < 0)
					{
						int final = m_inactiveUpdates.size() - 1;
						if (index < final)
						{
							m_inactiveUpdates[index] = m_inactiveUpdates[final];
							m_inactiveUpdates[index]->friend_setPhaseInLogic(-1);
							m_inactiveUpdates[index]->friend_setIndexInLogic(index);
						}
						m_inactiveUpdates.pop_back();
					}
					else
					{
						int final = m_phaseUpdates[phase].size() - 1;
						if (index < final)
						{
							m_phaseUpdates[phase][index] = m_phaseUpdates[phase][final];
							m_phaseUpdates[phase][index]->friend_setPhaseInLogic(phase);
							m_phaseUpdates[phase][index]->friend_setIndexInLogic(index);
						}
						m_phaseUpdates[phase].pop_back();
					}
				}
			}
		}

		TheAI->m_pathfinder->removeObjectFromPathfindMap(currentObject);
		currentObject->removeFromList(&m_objectList, &m_objectListTail);
		int id = currentObject->m_id;
		m_objectHash.erase(id);
		delete currentObject;

	}

	m_objectsToDestroy.clear();
}
