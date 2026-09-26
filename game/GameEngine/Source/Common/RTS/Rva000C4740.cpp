// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

class Player;
class Object;

class ContainModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual Bool isTunnelContain() const = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6c() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7c() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8c() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9c() = 0;
	virtual void slota0() = 0;
	virtual void slota4() = 0;
	virtual void slota8() = 0;
	virtual void slotac() = 0;
	virtual void slotb0() = 0;
	virtual void slotb4() = 0;
	virtual void slotb8() = 0;
	virtual void slotbc() = 0;
	virtual void slotc0() = 0;
	virtual void slotc4() = 0;
	virtual void slotc8() = 0;
	virtual void slotcc() = 0;
	virtual void slotd0() = 0;
	virtual void slotd4() = 0;
	virtual void slotd8() = 0;
	virtual void slotdc() = 0;
	virtual void slote0() = 0;
	virtual void slote4() = 0;
	virtual void slote8() = 0;
	virtual void slotec() = 0;
	virtual void slotf0() = 0;
	virtual void slotf4() = 0;
	virtual void slotf8() = 0;
	virtual void slotfc() = 0;
	virtual unsigned int getContainCount(Int argument) const = 0;
};

class Object
{
public:
	virtual void slot00() = 0;
	ContainModuleInterface *getContain() const
	{
		return contain;
	}
	Player *getControllingPlayer() const;

	char padding[0x1f8];
	ContainModuleInterface *contain;
};

class Drawable
{
public:
	char padding[0xfc];
	Object *object;
};

struct DrawableListNode
{
	DrawableListNode *next;
	DrawableListNode *previous;
	Drawable *value;
};

struct DrawableList
{
	DrawableListNode *head;

	Drawable *front() const
	{
		return head->next->value;
	}
};

class InGameUI
{
public:
#define BFME_UI_UNUSED_SLOT(number) virtual void slot##number() const = 0;
	BFME_UI_UNUSED_SLOT(00)
	BFME_UI_UNUSED_SLOT(01)
	BFME_UI_UNUSED_SLOT(02)
	BFME_UI_UNUSED_SLOT(03)
	BFME_UI_UNUSED_SLOT(04)
	BFME_UI_UNUSED_SLOT(05)
	BFME_UI_UNUSED_SLOT(06)
	BFME_UI_UNUSED_SLOT(07)
	BFME_UI_UNUSED_SLOT(08)
	BFME_UI_UNUSED_SLOT(09)
	BFME_UI_UNUSED_SLOT(10)
	BFME_UI_UNUSED_SLOT(11)
	BFME_UI_UNUSED_SLOT(12)
	BFME_UI_UNUSED_SLOT(13)
	BFME_UI_UNUSED_SLOT(14)
	BFME_UI_UNUSED_SLOT(15)
	BFME_UI_UNUSED_SLOT(16)
	BFME_UI_UNUSED_SLOT(17)
	BFME_UI_UNUSED_SLOT(18)
	BFME_UI_UNUSED_SLOT(19)
	BFME_UI_UNUSED_SLOT(20)
	BFME_UI_UNUSED_SLOT(21)
	BFME_UI_UNUSED_SLOT(22)
	BFME_UI_UNUSED_SLOT(23)
	BFME_UI_UNUSED_SLOT(24)
	BFME_UI_UNUSED_SLOT(25)
	BFME_UI_UNUSED_SLOT(26)
	BFME_UI_UNUSED_SLOT(27)
	BFME_UI_UNUSED_SLOT(28)
	BFME_UI_UNUSED_SLOT(29)
	BFME_UI_UNUSED_SLOT(30)
	BFME_UI_UNUSED_SLOT(31)
	BFME_UI_UNUSED_SLOT(32)
	BFME_UI_UNUSED_SLOT(33)
	BFME_UI_UNUSED_SLOT(34)
	BFME_UI_UNUSED_SLOT(35)
	BFME_UI_UNUSED_SLOT(36)
	BFME_UI_UNUSED_SLOT(37)
	BFME_UI_UNUSED_SLOT(38)
	BFME_UI_UNUSED_SLOT(39)
	BFME_UI_UNUSED_SLOT(40)
	BFME_UI_UNUSED_SLOT(41)
	BFME_UI_UNUSED_SLOT(42)
	BFME_UI_UNUSED_SLOT(43)
	BFME_UI_UNUSED_SLOT(44)
	BFME_UI_UNUSED_SLOT(45)
	BFME_UI_UNUSED_SLOT(46)
	BFME_UI_UNUSED_SLOT(47)
	BFME_UI_UNUSED_SLOT(48)
	BFME_UI_UNUSED_SLOT(49)
	BFME_UI_UNUSED_SLOT(50)
	BFME_UI_UNUSED_SLOT(51)
	BFME_UI_UNUSED_SLOT(52)
	BFME_UI_UNUSED_SLOT(53)
	BFME_UI_UNUSED_SLOT(54)
	BFME_UI_UNUSED_SLOT(55)
	BFME_UI_UNUSED_SLOT(56)
	BFME_UI_UNUSED_SLOT(57)
	BFME_UI_UNUSED_SLOT(58)
	BFME_UI_UNUSED_SLOT(59)
	BFME_UI_UNUSED_SLOT(60)
	BFME_UI_UNUSED_SLOT(61)
	BFME_UI_UNUSED_SLOT(62)
	virtual const DrawableList *getAllSelectedDrawables() const = 0;
#undef BFME_UI_UNUSED_SLOT
};

extern InGameUI *TheInGameUI;

class Rva000C4740Owner
{
public:
	Int evaluate(const void *rawObject);
};

Int Rva000C4740Owner::evaluate(const void *rawObject)
{
	const Object *target = reinterpret_cast<const Object *>(rawObject);
	ContainModuleInterface *contain = target->getContain();
	if (contain != 0 && contain->isTunnelContain())
	{
		Drawable *selectedDrawable = TheInGameUI->getAllSelectedDrawables()->front();
		Object *selectedObject = selectedDrawable->object;
		if (target->getControllingPlayer() != selectedObject->getControllingPlayer())
		{
			if (contain->getContainCount(0) > 0)
				return 0xa2;
		}
	}
	return 0xa1;
}
