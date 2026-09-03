// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022D960. Clear model-condition bits 0x40000/0x80000/0x100000
// on *(this-0x18) and notify after each clear.

class Object
{
public:
	void notifyModelConditionChanged();

	char m_pad[0x110];
	unsigned m_condition;
};

class Gen_0022D960
{
public:
	void bfmeNotify();
};

// ?bfmeNotify@Gen_0022D960@@QAEXXZ
void Gen_0022D960::bfmeNotify()
{
	Object *obj = *(Object **)((char *)this - 0x18);
	if ((obj->m_condition & 0x40000) != 0)
	{
		obj->m_condition &= ~0x40000u;
		obj->notifyModelConditionChanged();
	}
	if ((obj->m_condition & 0x80000) != 0)
	{
		obj->m_condition &= ~0x80000u;
		obj->notifyModelConditionChanged();
	}
	if ((obj->m_condition & 0x100000) != 0)
	{
		obj->m_condition &= ~0x100000u;
		obj->notifyModelConditionChanged();
	}
}
