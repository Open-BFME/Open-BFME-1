// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022F480. getControllingPlayer on *(this-0x18), walk the
// circular list at player+0x22C+8, virtual slot 0x90 with (node+8, arg).

struct BfmeNode2F480
{
	BfmeNode2F480 *next;
	char m_mid[4];
	void *payload;
};

struct BfmeList2F480
{
	char m_pad[8];
	BfmeNode2F480 *head;
};

class Player
{
public:
	char m_pad[0x22C];
	BfmeList2F480 *m_list;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Gen_0022F480
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void visit(void *payload, void *arg);

	void bfmeVisit(void *arg);
};

// ?bfmeVisit@Gen_0022F480@@QAEXPAX@Z
void Gen_0022F480::bfmeVisit(void *arg)
{
	Gen_0022F480 *self = this;
	Object *obj = *(Object **)((char *)self - 0x18);
	Player *player = obj->getControllingPlayer();
	BfmeList2F480 *list = player->m_list;
	BfmeNode2F480 **psent = &list->head;
	BfmeNode2F480 *head = *psent;
	BfmeNode2F480 *n = head->next;
	if (n == head)
		return;
	do
	{
		void *payload = n->payload;
		n = n->next;
		self->visit(payload, arg);
	} while (n != *psent);
}
