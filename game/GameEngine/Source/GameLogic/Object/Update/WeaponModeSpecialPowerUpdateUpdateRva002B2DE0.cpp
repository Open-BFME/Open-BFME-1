// Open-BFME5: clean recovery of the UpdateModuleInterface body at 0x002B2DE0.

enum UpdateSleepTimeRva002B2DE0
{
	UPDATE_SLEEP_FOREVER_RVA002B2DE0 = 0x3fffffff
};

class BfmeItem1005
{
public:
	void bfmeDoD1005(int value);
};

class BfmeH1040
{
public:
	void bfmeAdd1040(void *value);
};

class BfmeObjE10
{
public:
	void actionB(int value);
};

class Rva002B2DE0ModuleData
{
public:
	unsigned char m_pad[0x1dc];
	unsigned int m_flags;
};

class Rva002B2DE0UpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void wake(int value);

	UpdateSleepTimeRva002B2DE0 update();
};

// @?update@Rva002B2DE0UpdateInterface@@QAE?AW4UpdateSleepTimeRva002B2DE0@@XZ 0x002B2DE0
UpdateSleepTimeRva002B2DE0 Rva002B2DE0UpdateInterface::update()
{
	BfmeItem1005 *object = *(BfmeItem1005 **)((char *)this - 8);

	object->bfmeDoD1005(2);
	for (int i = 0; i < 0x1d; ++i)
	{
		if ((*(Rva002B2DE0ModuleData **)((char *)this - 0xc))->m_flags & (1u << (i & 0x1f)))
			((BfmeObjE10 *)object)->actionB(i);
	}

	((BfmeH1040 *)object)->bfmeAdd1040((char *)*(Rva002B2DE0ModuleData **)((char *)this - 0xc) + 0x1d0);
	*(unsigned char *)((char *)this + 0x28) = 0;
	((Rva002B2DE0UpdateInterface *)((char *)this + 0x14))->wake(0);
	return UPDATE_SLEEP_FOREVER_RVA002B2DE0;
}
