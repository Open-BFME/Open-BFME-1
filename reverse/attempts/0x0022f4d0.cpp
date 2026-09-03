// ?bfmePlace@Gen_0022F4D0@@QAEXPAVObject@@@Z
// partial score=0.7 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022F4D0. Init/clearDisabled/activate/setPosition on the
// argument, then a GameLogic-frame stamp and a virtual at this-0x20.

class Coord3D;

class Object
{
public:
	bool clearDisabled(int type);
	void activate();
	void setPosition(const Coord3D *pos);
	const Object *getFinalOverride() const;

	void *m_vtable;
	Object *m_nextOverride;
	char m_mid[0x330 - 8];
	int m_stamp;							// +0x330
	char m_mid2[0x424 - 0x334];
	int m_delay;							// +0x424
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	Overridable *m_nextOverride;
};

class GameLogic
{
public:
	char m_pad[0x3C];
	int m_frame;
};

extern GameLogic *TheGameLogic;

class BfmeXfer4D0
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
	virtual Object *virt28();
};

class BfmeOwner4D0
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
	virtual void finish();
};

class BfmeSet4D0
{
public:
	void bfmeSetVoid4D0();
};

class Gen_0022F4D0
{
public:
	void bfmeInit4D0(Object *obj);
	void bfmePlace(Object *obj);
};

// ?bfmePlace@Gen_0022F4D0@@QAEXPAVObject@@@Z
void Gen_0022F4D0::bfmePlace(Object *obj)
{
	Gen_0022F4D0 *self = this;
	self->bfmeInit4D0(obj);
	obj->clearDisabled(3);
	obj->activate();
	obj->setPosition((const Coord3D *)((char *)*(void **)((char *)self - 0x18) + 0x38));
	BfmeXfer4D0 *x = (BfmeXfer4D0 *)obj;
	if (x->virt28() == 0)
	{
		((BfmeOwner4D0 *)((char *)self - 0x20))->finish();
		return;
	}
	int frame = TheGameLogic->m_frame;
	Overridable *ovr = (Overridable *)obj;
	if (ovr->m_nextOverride != 0 && ovr->m_nextOverride->m_nextOverride != 0)
		ovr = (Overridable *)ovr->m_nextOverride->getFinalOverride();
	obj->m_stamp = ((Object *)ovr)->m_delay + frame;
	Object *p = x->virt28();
	((BfmeSet4D0 *)p)->bfmeSetVoid4D0();
	((BfmeOwner4D0 *)((char *)self - 0x20))->finish();
}
