// cl: /DNDEBUG /MD /EHsc
// readable body of ?getCurrentVictim@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

// AIUpdateInterface::getCurrentVictim, retail 0x002739D0.
// BFME stores the current victim ID at +0x40.  The shared AIUpdate header's
// layout is for Zero Hour, so this small ABI slice keeps the retail offset
// local to the accessor while preserving the real GameLogic lookup call.

typedef int ObjectID;

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	Object *getCurrentVictim(void) const;

private:
	unsigned char m_unmodelled_00[0x40];
	ObjectID m_currentVictimID;
};

// ?getCurrentVictim@AIUpdateInterface@@QBEPAVObject@@XZ
Object *AIUpdateInterface::getCurrentVictim(void) const
{
	if (m_currentVictimID != 0)
		return TheGameLogic->findObjectByID(m_currentVictimID);

	return 0;
}
