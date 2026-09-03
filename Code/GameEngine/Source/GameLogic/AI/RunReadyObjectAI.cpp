// Walks every live object and runs the AI-side action whose readiness gate is set.

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *getFirstObject(void);
};

class BfmeReadyGate
{
public:
	bool bfmeReady(void);
};

class BfmeObjectAI
{
public:
	void bfmeRunReadyAction(void);

private:
	char m_bfmeHead[0x140];
	BfmeReadyGate *m_bfmeGate;

	friend void __cdecl bfmeRunReadyObjectAI(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	char m_bfmeHead[0x88];
	Object *m_bfmeNext;
	char m_bfmeToAI[0x204 - 0x8c];
	BfmeObjectAI *m_bfmeAI;

	friend void __cdecl bfmeRunReadyObjectAI(void);
};

extern GameLogic *TheGameLogic; // retail 0x012F0898

// ?bfmeRunReadyObjectAI@@YAXXZ
void __cdecl bfmeRunReadyObjectAI(void)
{
	for (Object *object = TheGameLogic->getFirstObject(); object != 0;
		object = object->m_bfmeNext)
	{
		BfmeObjectAI *ai = object->m_bfmeAI;
		if (ai != 0 && ai->m_bfmeGate != 0 && ai->m_bfmeGate->bfmeReady())
			ai->bfmeRunReadyAction();
	}
}
