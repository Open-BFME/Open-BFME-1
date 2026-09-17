// cl: /DNDEBUG /MD

class AddressThunk0015EA70
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();

	void forwardSlot4();
};

void AddressThunk0015EA70::forwardSlot4()
{
	slot4();
}

class AddressThunk00105360
{
public:
	virtual void slot0();
	virtual void slot1();

	void forwardSlot1();
};

void AddressThunk00105360::forwardSlot1()
{
	slot1();
}
