// cl: /O2 /Ob0

enum KindOfType
{
	KINDOF_DOCK = 0x18
};

enum ObjectID
{
	INVALID_ID = 0
};

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	void notifyModelConditionChanged();

	char m_lead[0x118];
	unsigned int m_flags;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

class Rva002C9B10
{
public:
	virtual void pad00();
	virtual void pad04();
	virtual void pad08();
	virtual void pad0c();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual void pad1c();
	virtual void pad20();
	virtual void pad24();
	virtual void pad28();
	virtual void pad2c();
	virtual void pad30();
	virtual void pad34();
	virtual void pad38();
	virtual void pad3c();
	virtual void pad40();
	virtual void pad44();
	virtual void pad48();
	virtual void pad4c();
	virtual void pad50();
	virtual void pad54();
	virtual void useObject(Object *obj);

	void apply(int kind);

	char m_pad[0x10];
	int m_id;
};

void Rva002C9B10::apply(int kind)
{
	switch (kind)
	{
	case 0:
		{
			Object *obj = *(Object **)((char *)this - 0x338);
			if (obj->m_flags & 0x100)
			{
				obj->m_flags &= ~0x100;
				obj->notifyModelConditionChanged();
			}
		}
		break;
	case 1:
		{
			Object *obj = *(Object **)((char *)this - 0x338);
			if (obj->m_flags & 0x100)
			{
				obj->m_flags &= ~0x100;
				obj->notifyModelConditionChanged();
			}
			Object *found = TheGameLogic->findObjectByID(m_id);
			if (found && found->isKindOf(KINDOF_DOCK))
				useObject(found);
		}
		break;
	}
}
