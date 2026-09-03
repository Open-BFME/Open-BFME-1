// cl: /DNDEBUG /MD
//
// Address-derived recovery for the BFME state transition body at 0x002BD630.

#pragma comment(linker, "/alternatename:?find@Rva002BD630TeamFactory@@QAEPAXH@Z=?j_00044c2e@@YAXXZ")

typedef int Int;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

class Rva002BD630TeamFactory
{
public:
	void *find(Int id);
};

class Team
{
public:
	Coord3D *getEstimateTeamPosition_000EDCD0(Coord3D *position) const;
	unsigned char m_unreconstructed000[0x38];
	Coord3D m_position;
};

class Rva002BD630Object
{
public:
	unsigned char m_unreconstructed000[0x38];
	Coord3D m_position;
};

class Rva002BD630Machine
{
public:
	virtual void unused000() = 0;
	virtual void unused004() = 0;
	virtual void unused008() = 0;
	virtual void unused00c() = 0;
	virtual void unused010() = 0;
	virtual void unused014() = 0;
	virtual Int update() = 0;
	virtual void unused01c() = 0;
	virtual void unused020() = 0;
	virtual void unused024() = 0;
	virtual void unused028() = 0;
	virtual void unused02c() = 0;
	virtual void unused030() = 0;
	virtual void unused034() = 0;
	virtual void unused038() = 0;
	virtual void unused03c() = 0;
	virtual void unused040() = 0;
	virtual void unused044() = 0;
	virtual bool isComplete() = 0;

	unsigned char m_unreconstructed01c[0x40];
	Int m_teamID;
	Int m_otherID;
};

class Rva002BD630State
{
public:
	virtual void unused000() = 0;
	virtual void unused004() = 0;
	virtual void unused008() = 0;
	virtual void unused00c() = 0;
	virtual Int activeTransition() = 0;

	Int run();

private:
	unsigned char m_unreconstructed004[0x18];
	Rva002BD630Machine *m_machine;
	unsigned char m_unreconstructed020[0xc];
	Coord3D m_position;
	unsigned char m_unreconstructed038[8];
	Rva002BD630Machine *m_subMachine;
	unsigned char m_active;
};

extern GameLogic *TheBfmeGameLogic;
extern Rva002BD630TeamFactory *TheBfmeTeamFactory;

Int Rva002BD630State::run()
{
	if (m_active)
	{
		m_active = 0;
		return activeTransition();
	}

	if (m_subMachine == 0)
		return -1;

	Rva002BD630Machine *machine = m_machine;
	Rva002BD630Object *object = (Rva002BD630Object *)TheBfmeGameLogic->findObjectByID(machine->m_teamID);
	Team *teamResult = (Team *)TheBfmeTeamFactory->find(machine->m_otherID);
	if (object)
	{
		Coord3D *objectPosition = (Coord3D *)((char *)object + 0x38);
		m_position = *objectPosition;
	}
	else if (teamResult)
		teamResult->getEstimateTeamPosition_000EDCD0(&m_position);

	Int result = m_subMachine->update();
	if (m_subMachine && m_subMachine->isComplete())
		return -1;
	return result;
}
