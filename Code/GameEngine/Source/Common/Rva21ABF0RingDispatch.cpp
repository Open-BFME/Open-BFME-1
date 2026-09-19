struct Rva21ABF0Node
{
	Rva21ABF0Node *next;
	Rva21ABF0Node *previous;
	void *value;
};

struct Rva21ABF0List
{
	Rva21ABF0Node *sentinel;

	Rva21ABF0Node *begin(void) const
	{
		return sentinel->next;
	}

	Rva21ABF0Node *end(void) const
	{
		return sentinel;
	}
};

class Rva21ABF0Worker
{
public:
	void visit(void *value);
};

class Rva21ABF0RingDispatch
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void slot40(void);
	virtual void slot41(void);
	virtual void slot42(void);
	virtual void slot43(void);
	virtual void slot44(void);
	virtual void slot45(void);
	virtual void slot46(void);
	virtual void slot47(void);
	virtual void slot48(void);
	virtual void slot49(void);
	virtual void slot50(void);
	virtual void slot51(void);
	virtual void slot52(void);
	virtual void slot53(void);
	virtual void slot54(void);
	virtual void slot55(void);
	virtual void slot56(void);
	virtual void slot57(void);
	virtual void slot58(void);
	virtual void slot59(void);
	virtual void slot60(void);
	virtual void slot61(void);
	virtual void slot62(void);
	virtual void slot63(void);
	virtual void slot64(void);
	virtual Rva21ABF0List *first(void);
	virtual Rva21ABF0List *second(void);
	void dispatchAll(void);
	void finish(void);

private:
	char m_gap[0x998];
	Rva21ABF0Node *m_ring;
};

void Rva21ABF0RingDispatch::dispatchAll(void)
{
	Rva21ABF0Node *node = m_ring->next;

	while (node != m_ring) {
		void *value = node->value;
		node = node->next;
		((Rva21ABF0Worker *)((char *)this - 0x20))->visit(value);
	}

	finish();
}

void Rva21ABF0RingDispatch::finish(void)
{
	Rva21ABF0List *list;
	Rva21ABF0Node *node;
	register int pass;
	pass = 0;
	do {
		if (pass)
			list = second();
		else
			list = first();

		if (list == 0)
			continue;

		node = list->begin();
		if (node == list->end())
			continue;

		Rva21ABF0Worker *worker =
			(Rva21ABF0Worker *)((char *)this - 0x20);
		do {
			void *value = node->value;
			node = node->next;
			worker->visit(value);
		} while (node != list->end());

	} while (++pass < 2);
}
