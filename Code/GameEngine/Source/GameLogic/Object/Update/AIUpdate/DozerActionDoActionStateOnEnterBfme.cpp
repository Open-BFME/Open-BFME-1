// cl: /DNDEBUG /MD /EHsc

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_FAILURE = -2
};

class DozerAIInterface2B6240
{
public:
	virtual void slot000(); virtual void slot004();
	virtual void slot008(); virtual void slot00c();
	virtual void slot010(); virtual void slot014();
	virtual void slot018(); virtual void slot01c();
	virtual void slot020(); virtual void slot024();
	virtual void slot028(); virtual void slot02c();
	virtual void slot030(); virtual void slot034();
	virtual void slot038(); virtual void slot03c();
	virtual void slot040(); virtual void slot044();
	virtual void setBuildSubTask(int task);
};

class AIUpdateInterface2B6240
{
public:
	virtual void slot000(); virtual void slot004();
	virtual void slot008(); virtual void slot00c();
	virtual void slot010(); virtual void slot014();
	virtual void slot018(); virtual void slot01c();
	virtual void slot020(); virtual void slot024();
	virtual void slot028(); virtual void slot02c();
	virtual void slot030(); virtual void slot034();
	virtual void slot038(); virtual void slot03c();
	virtual void slot040(); virtual void slot044();
	virtual void slot048(); virtual void slot04c();
	virtual void slot050(); virtual void slot054();
	virtual void slot058(); virtual void slot05c();
	virtual void slot060(); virtual void slot064();
	virtual void slot068(); virtual void slot06c();
	virtual void slot070(); virtual void slot074();
	virtual void slot078(); virtual void slot07c();
	virtual void slot080(); virtual void slot084();
	virtual void slot088(); virtual void slot08c();
	virtual void slot090(); virtual void slot094();
	virtual void slot098(); virtual void slot09c();
	virtual void slot0a0(); virtual void slot0a4();
	virtual void slot0a8(); virtual void slot0ac();
	virtual void slot0b0(); virtual void slot0b4();
	virtual void slot0b8(); virtual void slot0bc();
	virtual void slot0c0(); virtual void slot0c4();
	virtual void slot0c8(); virtual void slot0cc();
	virtual void slot0d0(); virtual void slot0d4();
	virtual void slot0d8(); virtual void slot0dc();
	virtual void slot0e0(); virtual void slot0e4();
	virtual void slot0e8(); virtual void slot0ec();
	virtual void slot0f0(); virtual void slot0f4();
	virtual void slot0f8(); virtual void slot0fc();
	virtual void slot100(); virtual void slot104();
	virtual void slot108(); virtual void slot10c();
	virtual void slot110(); virtual void slot114();
	virtual void slot118(); virtual void slot11c();
	virtual void slot120(); virtual void slot124();
	virtual void slot128(); virtual void slot12c();
	virtual void slot130(); virtual void slot134();
	virtual void slot138();
	virtual DozerAIInterface2B6240 *getDozerAIInterface();
};

class DozerObject2B6240
{
public:
	AIUpdateInterface2B6240 *getAIUpdateInterface() const { return m_ai; }

	unsigned char m_beforeAI[0x204];
	AIUpdateInterface2B6240 *m_ai;
};

class DozerMachine2B6240
{
public:
	unsigned char m_beforeOwner[0x10];
	DozerObject2B6240 *m_owner;
};

class GameLogic2B6240
{
public:
	unsigned char m_beforeFrame[0x3c];
	unsigned int m_frame;
};

extern GameLogic2B6240 *TheGameLogic;

class DozerActionDoActionState
{
public:
	virtual StateReturnType onEnter();

private:
	DozerObject2B6240 *getMachineOwner() const { return m_machine->m_owner; }

	unsigned char m_beforeMachine[0x18];
	DozerMachine2B6240 *m_machine;
	unsigned int m_unused20;
	int m_task;
	unsigned int m_enterFrame;
};

// @?onEnter@DozerActionDoActionState@@UAE?AW4StateReturnType@@XZ 0x002B6240
StateReturnType DozerActionDoActionState::onEnter()
{
	DozerObject2B6240 *dozer = getMachineOwner();
	DozerAIInterface2B6240 *dozerAI = dozer->getAIUpdateInterface()->getDozerAIInterface();
	if (!dozerAI)
		return STATE_FAILURE;

	m_enterFrame = TheGameLogic->m_frame;
	if (m_task == 0 || m_task == 1)
		dozerAI->setBuildSubTask(0);

	return STATE_CONTINUE;
}
