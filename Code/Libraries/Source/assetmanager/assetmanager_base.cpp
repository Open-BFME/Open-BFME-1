// ?bfmeAdvanceStages@BfmeFlagStageSequence@@QAEIXZ
// cl: /O2 /Ob0

class BfmeFlagStageSequence
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot04();
	virtual void bfmeSlot08();
	virtual void bfmeSlot0C();
	virtual void bfmeSlot10();
	virtual void bfmeStage4();
	virtual void bfmeStage5();
	virtual void bfmeStage6();
	virtual void bfmeSlot20();
	virtual unsigned int bfmeStage7(unsigned int finalStage);
	virtual bool bfmeCanAdvanceStages();

	unsigned int bfmeAdvanceStages();

private:
	volatile unsigned int m_flags;
};

unsigned int BfmeFlagStageSequence::bfmeAdvanceStages()
{
	if (bfmeCanAdvanceStages())
	{
		m_flags = (m_flags & 0xFF04FFFF) | 0x00040000;
		bfmeStage4();
		m_flags = (m_flags & 0xFF05FFFF) | 0x00050000;
		bfmeStage5();
		m_flags = (m_flags & 0xFF06FFFF) | 0x00060000;
		bfmeStage6();
		m_flags = (m_flags & 0xFF07FFFF) | 0x00070000;
	}

	return bfmeStage7(true);
}
