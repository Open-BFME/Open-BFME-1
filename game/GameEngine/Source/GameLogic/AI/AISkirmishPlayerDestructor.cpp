// cl: /DNDEBUG /MD /EHsc
// Retail 0x00168710, 79 bytes. Player::setPlayerType (0xC9240) selects
// the 0xA0-byte skirmish allocation and calls constructor 0x168660 through
// ILT 0x4ADE. That constructor installs the same vtable, 0x01096FB0.
// There is no RTTI locator at this vtable; identity comes from the factory
// branch, canonical class contract, constructor and base-destructor chain.
//
// clearTeamsInQueue (0x160E70) drains the two intrusive lists at AIPlayer+4
// and +8 through 0x1607C0/0x160990, passing the null-checked deleting callback
// at 0x160E50. This matches AIPlayer.cpp's two removeAll calls and deleteQueue.
// The final call reaches the independently matched AIPlayer destructor.
//
// Retail EH ownership: destructor operand +3 names handler 0x01005828;
// that handler loads FuncInfo 0x011F3DE0, whose one-entry UnwindMap at
// 0x011F3DD8 contains state -1 / action 0x01005820. The 8-byte cleanup
// invokes the AIPlayer base destructor, as does this TU's compiler funclet.

class AIPlayer
{
protected:
	virtual ~AIPlayer();
	void clearTeamsInQueue();

private:
	char m_unmodelled04[0x74];
};

class AISkirmishPlayer : public AIPlayer
{
public:
	virtual ~AISkirmishPlayer();

private:
	char m_unmodelled78[0x28];
};

AISkirmishPlayer::~AISkirmishPlayer()
{
	clearTeamsInQueue();
}
