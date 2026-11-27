// Walks live objects and calls the existing AI-side action when its predicate succeeds.

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *getFirstObject(void);
};

// Opaque call view of the existing59-byte provider, reached through ILT2E8ED.
// It takes the unchanged receiver in ECX, no stack arguments, and returns AL.
struct Rva003FD060Owner
{
	bool anyBlocked() const;
};

class BfmeObjectAI
{
public:
	void bfmeRunReadyAction(void);

private:
	char m_bfmeHead[0x140];
	Rva003FD060Owner *m_bfmeGate;

	friend void __cdecl bfmeRunReadyObjectAI(void);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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
		if (ai != 0 && ai->m_bfmeGate != 0 && ai->m_bfmeGate->anyBlocked())
			ai->bfmeRunReadyAction();
	}
}
