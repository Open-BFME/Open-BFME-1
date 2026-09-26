// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Horde transport member dispatch, retail 0x0024B7E0.

typedef bool Bool;

class BfmeRvaB7E0AI
{
public:
	Bool isReady(void);
};

class BfmeRvaB7E0Object
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
	virtual BfmeRvaB7E0AI *getAI(void) = 0;

	char m_head[0x68];
	char m_slot;
};

class BfmeRvaB7E0Manager
{
public:
	void notifyReady(void *slot);
	void notifyNotReady(void *slot);
};

class BfmeRvaB7E0Owner
{
public:
	void finish(BfmeRvaB7E0Object *object, Bool flag);
};

class Rva0024B7E0
{
public:
	void dispatch(BfmeRvaB7E0Object *object, Bool flag);
};

void Rva0024B7E0::dispatch(BfmeRvaB7E0Object *object, Bool flag)
{
	BfmeRvaB7E0AI *ai = object->getAI();
	if (ai)
	{
		if (!flag)
		{
			if (ai->isReady() == true)
			{
				((BfmeRvaB7E0Manager *)*(void **)0x012ED5B8)->notifyReady(
					(void *)&object->m_slot);
			}
		}
		else
		{
			if (!ai->isReady())
				((BfmeRvaB7E0Manager *)*(void **)0x012ED5B8)->notifyNotReady(
					(void *)&object->m_slot);
		}
		((BfmeRvaB7E0Owner *)this)->finish(object, flag);
	}
}
