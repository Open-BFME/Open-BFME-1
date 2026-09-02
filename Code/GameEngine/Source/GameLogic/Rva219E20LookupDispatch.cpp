struct Rva219E20Node
{
	Rva219E20Node *next;
	Rva219E20Node *previous;
	void *value;
};

class BfmeK1101
{
public:
	char gap[8];
	Rva219E20Node *sentinel;
};

class BfmeJ1101
{
public:
	BfmeK1101 *bfmeFind1101(int key);
};

extern BfmeJ1101 *g_bfmeJ1101;

class Rva219E20LookupDispatch
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void dispatchValue(void *value, int argument) = 0;

	void dispatchAll(int argument);

private:
	char gap[0xB8];
	int lookupKey;
};

void Rva219E20LookupDispatch::dispatchAll(int argument)
{
	BfmeK1101 *record = g_bfmeJ1101->bfmeFind1101(lookupKey);
	Rva219E20Node **list = &record->sentinel;
	Rva219E20Node *node = (*list)->next;

	while (node != *list) {
		void *value = node->value;
		node = node->next;
		dispatchValue(value, argument);
	}
}
