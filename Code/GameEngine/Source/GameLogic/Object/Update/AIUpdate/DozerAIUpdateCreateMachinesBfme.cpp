// cl: /DNDEBUG /MD /EHsc

class Object;

class DozerPrimaryStateMachine
{
public:
	DozerPrimaryStateMachine(Object *owner);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void initDefaultState();

private:
	unsigned char m_body[0x40];
};

class DozerAIUpdate
{
private:
	void createMachines();
	Object *getObject() const { return m_object; }

	virtual void anchor();
	unsigned char m_beforeObject[4];
	Object *m_object;
	unsigned char m_beforeMachine[0x350];
	DozerPrimaryStateMachine *m_dozerMachine;
};

// @?createMachines@DozerAIUpdate@@AAEXXZ 0x002B7B20
void DozerAIUpdate::createMachines()
{
	if (m_dozerMachine == 0)
	{
		m_dozerMachine = new DozerPrimaryStateMachine(getObject());
		m_dozerMachine->initDefaultState();
	}
}
