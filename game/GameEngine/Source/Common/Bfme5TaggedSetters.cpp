// Five tagged-pointer setters.
//
// The member holds a pointer with its low bit used as a flag, so the old value
// is masked before being spoken to. The incoming pointer is notified through
// slot 0, the old one through slot 4, and then the new pointer is tagged if it
// answers 1 and stored.
//
// Two things about the shape. The parameter is copied into a local declared
// before the mask: without that copy the masked member is defined first and
// takes esi, leaving the parameter in edi -- same size, swapped registers,
// no match. And the null case returns early with its own copy of the store, so
// the two exits stay separate; a single store at the end folds them and loses
// nine bytes.

class BfmeTaggedItem
{
public:
	virtual void bfmeSlot0(void);				// slot +0x00
	virtual void bfmeSlot1(void);				// slot +0x04
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual char bfmeKind(void);				// slot +0x14
};

class Gen_008974C0
{
public:
	void bfmeSet(BfmeTaggedItem *value);

private:
	int m_bfmeFields[2];					// +0x00
	unsigned int m_bfmeTagged;				// +0x08
};

class Gen_00897510
{
public:
	void bfmeSet(BfmeTaggedItem *value);

private:
	int m_bfmeFields[3];					// +0x00
	unsigned int m_bfmeTagged;				// +0x0C
};

class Gen_008992C0
{
public:
	void bfmeSet(BfmeTaggedItem *value);

private:
	int m_bfmeFields[2];					// +0x00
	unsigned int m_bfmeTagged;				// +0x08
};

class Gen_00899320
{
public:
	void bfmeSet(BfmeTaggedItem *value);

private:
	int m_bfmeFields[3];					// +0x00
	unsigned int m_bfmeTagged;				// +0x0C
};

class Gen_008C5EE0
{
public:
	void bfmeSet(BfmeTaggedItem *value);

private:
	int m_bfmeFields[4];					// +0x00
	unsigned int m_bfmeTagged;				// +0x10
};

// ?bfmeSet@Gen_008974C0@@QAEXPAVBfmeTaggedItem@@@Z
void Gen_008974C0::bfmeSet(BfmeTaggedItem *value)
{
	BfmeTaggedItem *item = value;
	BfmeTaggedItem *previous = (BfmeTaggedItem *)(m_bfmeTagged & ~1);

	if (item)
		item->bfmeSlot0();

	if (previous)
		previous->bfmeSlot1();

	if (item == 0)
	{
		m_bfmeTagged = (unsigned int)item;
		return;
	}

	if (item->bfmeKind() == 1)
		item = (BfmeTaggedItem *)((unsigned int)item | 1);

	m_bfmeTagged = (unsigned int)item;
}

// ?bfmeSet@Gen_00897510@@QAEXPAVBfmeTaggedItem@@@Z
void Gen_00897510::bfmeSet(BfmeTaggedItem *value)
{
	BfmeTaggedItem *item = value;
	BfmeTaggedItem *previous = (BfmeTaggedItem *)(m_bfmeTagged & ~1);

	if (item)
		item->bfmeSlot0();

	if (previous)
		previous->bfmeSlot1();

	if (item == 0)
	{
		m_bfmeTagged = (unsigned int)item;
		return;
	}

	if (item->bfmeKind() == 1)
		item = (BfmeTaggedItem *)((unsigned int)item | 1);

	m_bfmeTagged = (unsigned int)item;
}

// ?bfmeSet@Gen_008992C0@@QAEXPAVBfmeTaggedItem@@@Z
void Gen_008992C0::bfmeSet(BfmeTaggedItem *value)
{
	BfmeTaggedItem *item = value;
	BfmeTaggedItem *previous = (BfmeTaggedItem *)(m_bfmeTagged & ~1);

	if (item)
		item->bfmeSlot0();

	if (previous)
		previous->bfmeSlot1();

	if (item == 0)
	{
		m_bfmeTagged = (unsigned int)item;
		return;
	}

	if (item->bfmeKind() == 1)
		item = (BfmeTaggedItem *)((unsigned int)item | 1);

	m_bfmeTagged = (unsigned int)item;
}

// ?bfmeSet@Gen_00899320@@QAEXPAVBfmeTaggedItem@@@Z
void Gen_00899320::bfmeSet(BfmeTaggedItem *value)
{
	BfmeTaggedItem *item = value;
	BfmeTaggedItem *previous = (BfmeTaggedItem *)(m_bfmeTagged & ~1);

	if (item)
		item->bfmeSlot0();

	if (previous)
		previous->bfmeSlot1();

	if (item == 0)
	{
		m_bfmeTagged = (unsigned int)item;
		return;
	}

	if (item->bfmeKind() == 1)
		item = (BfmeTaggedItem *)((unsigned int)item | 1);

	m_bfmeTagged = (unsigned int)item;
}

// ?bfmeSet@Gen_008C5EE0@@QAEXPAVBfmeTaggedItem@@@Z
void Gen_008C5EE0::bfmeSet(BfmeTaggedItem *value)
{
	BfmeTaggedItem *item = value;
	BfmeTaggedItem *previous = (BfmeTaggedItem *)(m_bfmeTagged & ~1);

	if (item)
		item->bfmeSlot0();

	if (previous)
		previous->bfmeSlot1();

	if (item == 0)
	{
		m_bfmeTagged = (unsigned int)item;
		return;
	}

	if (item->bfmeKind() == 1)
		item = (BfmeTaggedItem *)((unsigned int)item | 1);

	m_bfmeTagged = (unsigned int)item;
}
