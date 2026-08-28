// cl: /DNDEBUG /MD /EHsc
// readable body: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp

enum CommandSourceType {};

class AIUpdateInterface
{
public:
	virtual CommandSourceType getLastCommandSource() const;
	virtual void notifyVictimIsDead();

private:
	// BFME carries eight fewer bytes than the Zero Hour interface before this field.
	unsigned char m_unmodelled_04[ 0x48 - 4 ];
	CommandSourceType m_lastCommandSource;
};

// ?getLastCommandSource@AIUpdateInterface@@UBE?AW4CommandSourceType@@XZ
CommandSourceType AIUpdateInterface::getLastCommandSource() const
{
	return m_lastCommandSource;
}

// ?notifyVictimIsDead@AIUpdateInterface@@UAEXXZ
void AIUpdateInterface::notifyVictimIsDead()
{
}
