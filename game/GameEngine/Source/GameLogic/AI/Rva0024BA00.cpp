// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Horde transport member cleanup, retail 0x0024BA00.

typedef bool Bool;

// Opaque AI and view types; retail calls reach 0x00227B60 (ILT 0x0002CE44),
// 0x0022E340 (ILT 0x00041E34), 0x001C9AC0 (ILT 0x000122AB), 0x00410BA0
// (ILT 0x00012E3B) and 0x00411DD0 (ILT 0x00008337), declared below as those
// ledger rows name them.
class BfmeRvaBA00AI
{
};

class BfmeRvaBA00View
{
};

class Object;

class Rva00227B60ContainDispatch
{
public:
	void dispatch(Object *object, bool value);
};

class Gen_00410BA0
{
public:
	int isDrawableEffectivelyHidden(void) const;
};

class Gen_00411DD0
{
public:
	void bfmeSet(bool value);
};

class BfmeRvaBA00Object
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
	virtual BfmeRvaBA00AI *getAI(void) = 0;

	char m_head[0x12c - 4];
	unsigned int m_status;
};

// The object this cleanup runs on is a retail Object: the status-notify
// tail call lands on ?notifyModelConditionChanged@Object@@QAEXXZ (0x0002191D).
// Only the callee's spelling is needed here, so Object carries no layout.
class Object
{
public:
	void notifyModelConditionChanged();
};

class TransportContain
{
public:
	virtual void onRemoving(Object *object);
};

class Gen001C9AC0
{
public:
	void handle(int value);
};

class Rva0024BA00
{
public:
	void cleanup(BfmeRvaBA00Object *object);
};

void Rva0024BA00::cleanup(BfmeRvaBA00Object *object)
{
	BfmeRvaBA00View *view = (BfmeRvaBA00View *)((char *)this + 0x20);
	((Rva00227B60ContainDispatch *)view)->dispatch((Object *)object, false);
	((TransportContain *)view)->TransportContain::onRemoving((Object *)object);
	((Gen001C9AC0 *)object)->handle(0x14);

	if (((unsigned char)object->m_status & 0x80) != 0)
	{
		object->m_status &= 0xffffff7f;
		reinterpret_cast<Object *>(object)->notifyModelConditionChanged();
	}

	BfmeRvaBA00AI *ai = object->getAI();
	if (ai && (unsigned char)((Gen_00410BA0 *)ai)->isDrawableEffectivelyHidden() == 1)
		((Gen_00411DD0 *)ai)->bfmeSet(false);
}
