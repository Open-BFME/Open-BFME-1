class Object;
class Player;

class BfmeKey926C
{
public:
	Player *bfmeFind926C(void);
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *object, Player *player);
};

struct Rva222970Node
{
	Rva222970Node *next;
	Rva222970Node *previous;
	Object *object;
};

class Rva222970FilteredDispatch
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
	virtual void dispatchObject(Object *object, int mode) = 0;

	Object *findAndDispatch(Rva2225E0Filter *filter);
	BfmeKey926C *getOwner(void) const
	{
		return *(BfmeKey926C *const *)((const char *)this - 0x18);
	}

private:
	char gap[0x14];
	Rva222970Node *objects;
};

Object *Rva222970FilteredDispatch::findAndDispatch(Rva2225E0Filter *filter)
{
	Rva222970Node *node = objects->next;

	while (node != objects) {
		if (filter == 0 || filter->accepts(
			node->object,
			getOwner()->bfmeFind926C()))
		{
			Object *result = node->object;
			dispatchObject(result, 0);
			return result;
		}

		node = node->next;
	}

	return 0;
}
