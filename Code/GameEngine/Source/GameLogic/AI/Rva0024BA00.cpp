// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Horde transport member cleanup, retail 0x0024BA00.

typedef bool Bool;

class BfmeRvaBA00AI
{
public:
	Bool isReady(void);
	void stop(int value);
};

class BfmeRvaBA00Object
{
public:
	virtual void unused0(void) = 0;
	virtual void unused1(void) = 0;
	virtual void unused2(void) = 0;
	virtual void unused3(void) = 0;
	virtual void unused4(void) = 0;
	virtual void unused5(void) = 0;
	virtual void unused6(void) = 0;
	virtual void unused7(void) = 0;
	virtual void unused8(void) = 0;
	virtual void unused9(void) = 0;
	virtual BfmeRvaBA00AI *getAI(void) = 0;

	char m_head[0x12c - 4];
	unsigned int m_status;

	void action(int value);
	void notifyStatus(void);
};

class BfmeRvaBA00View
{
public:
	void dispatch(BfmeRvaBA00Object *object, int value);
	void remove(BfmeRvaBA00Object *object);
};

class Rva0024BA00
{
public:
	void cleanup(BfmeRvaBA00Object *object);
};

void Rva0024BA00::cleanup(BfmeRvaBA00Object *object)
{
	BfmeRvaBA00View *view = (BfmeRvaBA00View *)((char *)this + 0x20);
	view->dispatch(object, 0);
	view->remove(object);
	object->action(0x14);

	if (((unsigned char)object->m_status & 0x80) != 0)
	{
		object->m_status &= 0xffffff7f;
		object->notifyStatus();
	}

	BfmeRvaBA00AI *ai = object->getAI();
	if (ai && ai->isReady() == true)
		ai->stop(0);
}
