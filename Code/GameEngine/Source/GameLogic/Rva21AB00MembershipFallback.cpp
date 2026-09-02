struct Rva21AB00Node
{
	Rva21AB00Node *next;
	Rva21AB00Node *previous;
	void *value;
};

class Rva21AB00Owner
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
	virtual int accepts(void *value) = 0;
};

class BfmeThing913D
{
public:
	bool acceptsWithFallback(void *value);
	char bfmeAdd913D(void *value);

private:
	char gap[0x99C];
	Rva21AB00Node *members;
};

bool BfmeThing913D::acceptsWithFallback(void *value)
{
	Rva21AB00Node *end = members;
	Rva21AB00Node *node = end->next;

	while (node != end) {
		if (node->value == value)
			return true;
		node = node->next;
	}

	if (bfmeAdd913D(value))
		return true;

	Rva21AB00Owner *owner = (Rva21AB00Owner *)((char *)this - 0x20);
	return owner->accepts(value) != 0;
}
