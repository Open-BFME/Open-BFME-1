// readable body of ?checkForCrateToPickup@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// Six more bodies in two shapes.
//
// 0x001C3FB0, 0x001C4020 and 0x0020EC60 look a key up, refuse a negative
// answer, and set one bit of a word. The shift amount is masked with
// and ecx,0x1F, which the compiler does not add on its own for a plain shift
// -- the source masks it. The success path sits inside the guard with a bare
// return false last, so the two byte-wide exits stay separate.
//
// 0x0015BCB0, 0x00189D00 and 0x002BC050 walk owner -> +0x10 -> +0x204 to reach
// a finder, and give up with -1 when it finds nothing. The owner is re-read
// after the call before the virtual dispatch at vtable+0x38, and the last call
// is a tail jump, so it hands its own answer straight back.


int bfmeLookupA(void *key);					// ILT 0x0000B1AE

class Gen_001C3FB0
{
public:
	bool bfmeSet(void *key);

private:
	int m_bfmeWord;
};

int bfmeLookupB(void *key);					// ILT 0x000052CC

class Gen_001C4020
{
public:
	bool bfmeSet(void *key);

private:
	int m_bfmeWord;
};

int bfmeLookupC(void *key);					// ILT 0x00031246

class Gen_0020EC60
{
public:
	bool bfmeSet(void *key);

private:
	int m_bfmeWord;
};

// ?bfmeSet@Gen_001C3FB0@@QAE_NPAX@Z
bool Gen_001C3FB0::bfmeSet(void *key)
{
	int index = bfmeLookupA(key);

	if (index >= 0)
	{
		m_bfmeWord |= 1 << (index & 31);

		return true;
	}

	return false;
}

// ?bfmeSet@Gen_001C4020@@QAE_NPAX@Z
bool Gen_001C4020::bfmeSet(void *key)
{
	int index = bfmeLookupB(key);

	if (index >= 0)
	{
		m_bfmeWord |= 1 << (index & 31);

		return true;
	}

	return false;
}

// ?bfmeSet@Gen_0020EC60@@QAE_NPAX@Z
bool Gen_0020EC60::bfmeSet(void *key)
{
	int index = bfmeLookupC(key);

	if (index >= 0)
	{
		m_bfmeWord |= 1 << (index & 31);

		return true;
	}

	return false;
}

class BfmeFinder
{
public:
	void *bfmeFind(void);					// ILT 0x000265A8
};

class BfmeStore
{
public:
	char m_bfmeHead[0x204];
	BfmeFinder *m_bfmeFinder;				// +0x204
};

class BfmeOwner
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeAccept(void *item);			// slot 14, vtable+0x38

	char m_bfmeHead[0x10 - 4];
	BfmeStore *m_bfmeStore;					// +0x10
};

class Gen_0015BCB0
{
public:
	int bfmeRun(void);

private:
	int bfmeFinish(void);					// ILT 0x000042DC

	char m_bfmeHead[0x1C];
	BfmeOwner *m_bfmeOwner;					// +0x1C
};

class Gen_00189D00
{
public:
	int bfmeRun(void);

private:
	int bfmeFinish(void);					// ILT 0x000042DC

	char m_bfmeHead[0x1C];
	BfmeOwner *m_bfmeOwner;					// +0x1C
};

class Gen_002BC050
{
public:
	int bfmeRun(void);

private:
	int bfmeFinish(void);					// ILT 0x000042DC

	char m_bfmeHead[0x1C];
	BfmeOwner *m_bfmeOwner;					// +0x1C
};

// ?bfmeRun@Gen_0015BCB0@@QAEHXZ
int Gen_0015BCB0::bfmeRun(void)
{
	void *found = m_bfmeOwner->m_bfmeStore->m_bfmeFinder->bfmeFind();

	if (found)
	{
		m_bfmeOwner->bfmeAccept(found);

		return bfmeFinish();
	}

	return -1;
}

// ?bfmeRun@Gen_00189D00@@QAEHXZ
int Gen_00189D00::bfmeRun(void)
{
	void *found = m_bfmeOwner->m_bfmeStore->m_bfmeFinder->bfmeFind();

	if (found)
	{
		m_bfmeOwner->bfmeAccept(found);

		return bfmeFinish();
	}

	return -1;
}

// ?bfmeRun@Gen_002BC050@@QAEHXZ
int Gen_002BC050::bfmeRun(void)
{
	void *found = m_bfmeOwner->m_bfmeStore->m_bfmeFinder->bfmeFind();

	if (found)
	{
		m_bfmeOwner->bfmeAccept(found);

		return bfmeFinish();
	}

	return -1;
}

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h
class CollideModuleInterface
{
public:
	virtual void bfmeOnCollide(void);
	virtual bool wouldLikeToCollideWith(const Object *other) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void *bfmeGetBody(void);
	virtual CollideModuleInterface *getCollide(void);
};

class ObjectModuleSlice
{
public:
	virtual void bfmeModuleSlot(void);

private:
	void *m_bfmeData;
	Object *m_bfmeObject;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModuleSlice, public BehaviorModuleInterface
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	BehaviorModule **getBehaviorModules(void) const { return m_bfmeBehaviors; }

private:
	char m_bfmeHead[0x1F0];
	BehaviorModule **m_bfmeBehaviors;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	Object *checkForCrateToPickup(void);

private:
	Object *getObject(void) const { return m_bfmeObject; }

	char m_bfmeHead[8];
	Object *m_bfmeObject;
	char m_bfmeBody[0x218 - 0x0C];
	int m_crateCreated;
};

// Keeping findObjectByID out of line preserves retail's scan after the ID is cleared.
Object *AIUpdateInterface::checkForCrateToPickup(void)
{
	if (m_crateCreated != 0)
	{
		m_crateCreated = 0;
		Object *crate = TheGameLogic->findObjectByID(m_crateCreated);
		if (crate)
		{
			for (BehaviorModule **module = crate->getBehaviorModules(); *module; ++module)
			{
				CollideModuleInterface *collide = (*module)->getCollide();
				if (collide && collide->wouldLikeToCollideWith(getObject()))
					return crate;
			}
		}
	}

	return 0;
}
